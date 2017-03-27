#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 -o ! -d $2 ]
then
	echo "wpisano zle argumenty"
	exit 1
fi

for plik in `ls $1`
do
	if [ ! -d $1/$plik ]
	then
		if [ ! -d $2/$plik -a -e $2/$plik ]
		then
			rm $1/$plik
		fi
	fi
done
