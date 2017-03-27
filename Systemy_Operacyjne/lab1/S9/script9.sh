#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 -o ! -f $2 ]
then
	echo "zle wpisane argumenty"
	exit 1
fi

for plik in `ls $1`
do
	if [ ! -s $1/$plik ]
	then
		echo "$plik" >> $2
		rm $1/$plik
	fi
done

