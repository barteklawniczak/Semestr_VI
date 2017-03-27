#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 -a ! -d $2 ]
then
	echo "podane argumenty nie sa katalogami"
	exit 1
fi

for plik in `ls $1`
do
	if [ -f $1/$plik -a ! -h $1/$plik ]
	then
		ln -s `realpath $1/$plik` $2/linkdo$plik
	fi
done

for plik in `ls $2`
do
	if [ -f $2/$plik -a ! -h $2/$plik ]
	then
		ln -s `realpath $2/$plik` $1/linkdo$plik
	fi
done

####################################################################################
#Zadanie 3: Skrypt tworzący dwa dodatkowe katalogi (5 i 6, jako parametry), 
#dodający do nich pliki, a następnie tworzący w katalogu 5 dowiązania do plików z 
#katalogu 6 i odwrotnie. 
####################################################################################