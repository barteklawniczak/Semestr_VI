#!/bin/bash

if [ ! $# -eq 1 ]
then
	echo "zla liczba parametrow"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "zadany argument nie jest katalogiem"
	exit 1
fi

for dir in `ls $1`
do
	if [ -d $1/$dir ]
	then
		mv $1/$dir/* $1/
		rmdir $1/$dir
	fi
done
