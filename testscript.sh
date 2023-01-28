#!/bin/bash

# File runs all tests
function printc(){
	case $1 in
		"light red")
			color="1;31"
			shift # pops first arguement off stack
		;;
		"light green")
			color="1;32"
			shift # pops first arguement off stack 
		;;
		"light cyan")
			color="1;36"
			shift # pops first arguement off stack 
		;;
		*)
			color="1;35"
		;;
	esac

	echo -ne "\e["$color"m"$@"\e[0m" #-n for no newline, -e for allowing \
}

function test(){
	testMsg=$1
	command=$2
	expectCode=$3
	expectOut=$4
	expectFile="imagesPGM/"$5

	# start test
	printc "light cyan" $testMsg", PASSED:"
	# run tested code
	actualOut=`$command` 
	# Compare actual and expected error codes
	actualCode=$? #$? is the prev bash output/returned val

	if [ $actualCode != $expectCode ]
	then
		printc "light red" " NO\n"
		return 1
	fi

	if [ "$actualOut" != "$expectOut" ]
	then
		printc "light red" " NO\n"
		return 1
	fi

	# compare expected and actual output files
	## split command str into array
	IFS=" " read -ra command_str <<< $command
	actualFile=${command_str[@]:2}

	### -w, whitespace: -q: just that they differ
	if [ $expectFile != "imagesPGM/" ]
	then 
		if [ -n "`diff -qw $actualFile $expectFile`" ] #turns the output of `diff` into a string
		then
			printc "light red" " NO\n"
			return 1
		fi
	fi

	printc "light green" " YES\n"
	return 0
}

# testing that all pgm module's errors are handled correctly
function echoTests (){
	pgmModule=$1
	successMsg=$2
	printc $pgmModule" BATCH TESTS==>\n" 
	test "Generic success" "./pgmEcho imagesPGM/1x1.pgm imagesPGM/out_1x1.pgm" 0 "ECHOED" "ex_1x1.pgm"
	test "No args" $pgmModule 1 "Usage: $pgmModule inputImage.pgm outputImage.pgm"
	test "Too few args" $pgmModule" imagesPGM/file" 1 "ERROR: Bad Argument Count"
	test "Too many args" $pgmModule" imagesPGM/file imagesPGM/file2 imagesPGM/file3" 1 "ERROR: Bad Argument Count"
	test "Bad input filename" $pgmModule" imagesPGM/FEEELS imagesPGM/file" 2 "ERROR: Bad File Name (imagesPGM/FEEELS)"
	test "Bad magic num" $pgmModule" imagesPGM/bad_mgnum.pgm imagesPGM/file" 3 "ERROR: Bad Magic Number (imagesPGM/bad_mgnum.pgm)"
	#todo: comment line errors will be dealt with later
	test "Image too small" $pgmModule" imagesPGM/tiny.pgm imagesPGM/file" 5 "ERROR: Bad Dimensions (imagesPGM/tiny.pgm)"
	test "Image too big" $pgmModule" imagesPGM/largest.pgm imagesPGM/file" 5 "ERROR: Bad Dimensions (imagesPGM/largest.pgm)"
	test "Bad gray" $pgmModule" imagesPGM/bad_gray.pgm imagesPGM/file" 6 "ERROR: Bad Max Gray Value (imagesPGM/bad_gray.pgm)"
	#todo: find out how to test image malloc
	test "Gray value too little" $pgmModule" imagesPGM/little_gray_data.pgm.pgm imagesPGM/file" 8 "ERROR: Bad Data (imagesPGM/little_gray_data.pgm)"
	test "Gray value too big" $pgmModule" imagesPGM/big_gray_data.pgm imagesPGM/file" 8 "ERROR: Bad Data (imagesPGM/big_gray_data.pgm)"
	test "Too few pixels" $pgmModule" imagesPGM/sub_dimensional.pgm imagesPGM/file" 8 "ERROR: Bad Data (imagesPGM/sub_dimensional.pgm)"
	test "Too many pixels" $pgmModule" imagesPGM/extra_dimensional.pgm imagesPGM/out_extra_dimensional.pgm" 0 $successMsg "ex_extra_dimensional.pgm"
	#todo: find out how to test output failed
	#todo: find out how to test bad layout
	#todo: find out how to test miscellaneous
	printc "<=="$pgmModule" END OF BATCH\n"
}
## Compile code
printc "---------------------------------\n"
printc "Compiling code...\n"
make all
printc "Code compiled\n"
printc "---------------------------------\n"
## Run test groups
case $1 in
	"echo")
		echoTests "./pgmEcho" "ECHOED"
	;;
	"comp")
		test "Identical Commented and uncommented" "./pgmComp imagesPGM/comment_none.pgm imagesPGM/comment_all.pgm" 0 "IDENTICAL" 
		test "Identical ASCII and Binary" "./pgmComp imagesPGM/comment_none.pgm imagesPGM/comment_none_bin.pgm" 0 "IDENTICAL"
		test "Different" "./pgmComp imagesPGM/1x1.pgm imagesPGM/comment_none.pgm" 0 "DIFFERENT"
	;;
	"bin")
		test "Bin to decimal" "./pgmb2a imagesPGM/bin_3x3.pgm imagesPGM/ascii_3x3.pgm" 0 "CONVERTED"
		test "Decimal to bin" "./pgmb2a imagesPGM/ascii_3x3.pgm imagesPGM/back_to_bin_3x3.pgm" 100 "ERROR: Miscellaneous cannot convert to ascii, .pgm already in ascii"
		test "Compare there and back" "./pgmComp imagesPGM/bin_3x3.pgm imagesPGM/back_to_bin_3x3.pgm" 0 "IDENTICAL"
	;;
	"ascii")
		test "Decimal to bin" "./pgma2b imagesPGM/ascii_2x2.pgm imagesPGM/bin_2x2.pgm" 0 "CONVERTED"
		test "Bin to decimal" "./pgma2b imagesPGM/bin_2x2.pgm imagesPGM/back_to_ascii_2x2.pgm" 100 "ERROR: Miscellaneous cannot convert to binary, .pgm already in binary"
		test "Compare there and back" "./pgmComp imagesPGM/ascii_2x2.pgm imagesPGM/back_to_ascii_2x2.pgm" 0 "IDENTICAL"
	;;
	"reduce")
		test "Big, generic reduce" "./pgmReduce imagesPGM/pre_reduce.pgm 5 imagesPGM/out_reduce.pgm" 0 "REDUCED" "ex_reduce.pgm"
		test "Reduce factor is big" "./pgmReduce imagesPGM/pre_reduce.pgm 20 imagesPGM/mini_reduce.pgm" 0 "REDUCED" "ex_mini_reduce.pgm"
		test "Reduce factor too small" "./pgmReduce imagesPGM/pre_reduce.pgm 0 imagesPGM/out_reduce.pgm" 100 "ERROR: Miscellaneous reduce factor must be greater than zero"
	;;
	# "tile")
	# 	standardTests "./pgmTile" "TILED"
	# ;;
	# "assemble")
	# 	standardTests "./pgmAssemble" "ASSEMBLED"
	# ;;
	*)
		echo "test specific modules by setting the module name as a variable e.g. pgmEcho => ./testscript.sh echo"
	;;
esac

printc "---------------------------------\n"
printc "----------ALL TESTS DONE---------\n"
printc "---------------------------------\n"
