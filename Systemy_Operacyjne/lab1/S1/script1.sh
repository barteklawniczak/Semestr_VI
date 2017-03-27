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

rm $1/*.old
for nazwa in $1/*
do
         mv $nazwa $nazwa.old
done
