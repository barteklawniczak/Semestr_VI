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

for plik in $1/*
do
	if [ ! -x $plik ]
	then
		rm $plik
	fi
done
