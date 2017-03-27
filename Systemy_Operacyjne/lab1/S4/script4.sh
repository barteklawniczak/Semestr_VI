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

dane=`ls -S $1`
i=1

for plik in $dane
do
	if [ ! -x $1/$plik -a ! -d $1/$plik ]
	then
		mv $1/$plik $1/$plik.$i
		i=$[i+1]
	fi
done
