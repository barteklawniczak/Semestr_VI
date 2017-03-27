#!/bin/bash

if [ ! $# -eq 1 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -e $1 ]
then
	echo "taki plik nie istnieje"
	exit 1
fi

pliki=`cat $1`
echo -n > $1

for plik in $pliki
do
	echo "Plik o nazwie: $plik" >> $1
	cat $plik >> $1
done
