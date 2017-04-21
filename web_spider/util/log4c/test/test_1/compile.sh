#!/bin/sh

if [ $# -eq 0 ]; then
	# complile target
	g++ -g -L../.. test.cpp -o test -llog4c 
elif [ $# -eq 1 ] && [ "x$1" = "xclean" ]; then
	# clean target
	rm -vf test core
else
	# echo usage
	echo "$0 [clean]"
fi

