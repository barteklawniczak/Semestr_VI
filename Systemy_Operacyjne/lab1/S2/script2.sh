#!/bin/bash

if [ ! $# -eq 2 ]
then 
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "pierwszy podany argument nie jest katalogiem"
	exit 1
fi 

if [ ! -f $2 ]
then
	echo "drugi podany argument nie jest plikiem"
	exit 1
fi

dane=`cat $2`
for plik in $dane
do
	touch $1/$plik
done

