#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 -o ! -d $2 ]
then
	echo "argument(y) nie są katalogami"
	exit 1
fi

pliki=`ls $1`
echo "Pliki ktore istnieja w obu zadanych katalogach:"

for plik in $pliki
do
	if [ -e $2/$plik -a ! -d $1/$plik ]
	then
		echo "$plik"
	fi
done
