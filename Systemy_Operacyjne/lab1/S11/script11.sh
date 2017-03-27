#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo "zla liczba argumentow"
	exit 1
fi

if [ ! -d $1 -a ! -e $2 ]
then
	echo "podano zle argumenty"
	exit 1
fi

pliki=`cat $2`

echo "Lista plikow brakujacych w katalogu: "

for plik in $pliki
do
	if [ ! -e $1/$plik ]
	then
		echo "$plik"
	fi
done

echo "Lista plikow nie bedacych na liscie: "
for var in `ls $1`
do
	let "bool=1"
	for plik in $pliki
	do
		if [[ $var = $plik ]]
		then
			let "bool=0"
		fi
	done

	if [ $bool -eq 1 ]
	then
		echo "$var"
	fi
done
