#!/bin/bash

if [ ! $# -eq 2 ]
then 
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "podany argument nie jest katalogiem"
	exit 1
fi 

touch $1/plik_z_danymi

for plik in $1/*.$2
do	if [ ! -d $plik ]
	then
		echo "Nazwa pliku: $plik" >> $1/plik_z_danymi
		cat $plik >> $1/plik_z_danymi
	fi
done
