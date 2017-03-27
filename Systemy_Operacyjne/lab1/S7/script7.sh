#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 -o ! -d $2 ]
then
	echo "jeden lub oba argumenty nie sa katalogami"
	exit 1
fi

for plik in `ls $1`
do
	if [ -x $1/$plik ]
	then
		mv $1/$plik $2/$plik
	fi
done


