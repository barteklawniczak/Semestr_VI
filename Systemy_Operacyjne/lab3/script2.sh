#!/bin/bash

rm -Rf muzyka obrazy teksty inne
mkdir kat1 kat2 muzyka obrazy teksty inne
mkdir kat2/kat3 kat2/kat4

for i in {1..300}
do
	if let "$i%3 == 0"
	then
		touch kat1/tekstkat1_$i.txt
		touch kat2/kat3/tekstkat2kat3_$i.txt
	elif let "i%5 == 0"
	then
		touch kat1/obrazkat1_$i.jpg
		touch kat2/kat4/obrazkat2kat4_$i.jpg
	elif let "i%7 == 0"
	then
		touch kat2/kat3/muzykakat2kat3_$i.mp3
		touch kat2/kat4/muzykakat2kat4_$i.mp3
	else
		touch kat1/plikkat1_$i.dat
		touch kat1/plikkat1_$i.test
	fi
done

find kat1 kat2 -type f -name "*.mp3" | xargs cp -t muzyka
find kat1 kat2 -type f -name "*.jpg" | xargs cp -t obrazy
find kat1 kat2 -type f -name "*.txt" | xargs cp -t teksty
find kat1 kat2 -type f -name "*.dat" -o -name "*.test" | xargs cp -t inne
#^dzialalo u mnie bez nawiasow

rm -Rf kat1 kat2

#################################################################################################
#Zadanie 2: Tworzymy katalogi
#kat1
#kat2/kat3
#kat2/kat4tes
#teksty obrazy muzyka inne
#generujemy 300 plikow w petli w nastepujacy sposob:
#jeżeli i%3 == 0
#tekst.txt -> kat1, tekst.txt -> kat2/kat3
#jeżeli i%5 == 0
#obraz.jpg -> kat1, obraz.jpg -> kat2/kat4
#jeżeli i%7 == 0
#muzyka.mp3 -> kat2/kat3, muzyka.mp3 -> kat2/kat4
#else
#plik.dat -> kat1, plik.test -> kat1
#
#Następnie przenosimy poleceniem cp pliki .txt do teksty, .jpg do obrazy itd, a kat1 i kat2 usuwamy
#################################################################################################