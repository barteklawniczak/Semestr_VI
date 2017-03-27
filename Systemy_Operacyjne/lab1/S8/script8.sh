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

function pokaz_zawartosc
{
	zawartosc=`ls $1`
	for plik in $zawartosc
	do
		if [ ! -d $1/$plik ]
		then
			echo "$1/$plik"
		else
			if [ $glebokosc -gt 0 ]
			then
				glebokosc=$[glebokosc-1]
				echo "$1/$plik" #czy wypisywac nazwy katalogów?
				pokaz_zawartosc $1/$plik
				glebokosc=$[glebokosc+1]
			fi
		fi
	done
	licznik=$[licznik+1]
}

glebokosc=2
pokaz_zawartosc $1
