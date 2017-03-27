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

licznik=0

for plik in `ls $1`
do
	if [ -x $1/$plik ]
	then
		licznik=$[licznik+1]
	fi
done

echo "Liczba plikow ktore maja prawo do wykonywania w katalogu $1 : $licznik"
