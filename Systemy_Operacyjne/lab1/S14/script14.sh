#!/bin/bash

if [ ! $# -eq 1 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "podany argument nie jest katalogiem"
	exit 1
fi

for plik in `ls $1`
do
	if [ -w $1/$plik ]
	then
		touch $1/$plik
	fi
done
