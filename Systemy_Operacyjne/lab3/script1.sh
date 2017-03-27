#!/bin/bash

rm -Rf kat
mkdir kat
mkdir kat/kat1.txt kat/kat2
touch kat/plik1.txt kat/plik2.txt kat/plik3 kat/plik4.mp3 kat/plik5.mp3 kat/plik6.txt kat/plik7 kat/plik8.mp3 kat/plik9.txt 
chmod u+x kat/plik2.txt
chmod u-r kat/plik2.txt
chmod u+x kat/plik1.txt
chmod u+x kat/plik9.txt
chmod u-r kat/plik9.txt
chmod u-r kat/plik6.txt
chmod u+x kat/plik5.mp3
chmod u-r kat/plik5.mp3
echo "To jest zdanie w plik1" > kat/plik1.txt
echo "To jest zdanie w plik2" > kat/plik2.txt
echo "To jest zdanie w plik3" > kat/plik3
echo "To jest zdanie w plik5" > kat/plik5.mp3
echo "To jest zdanie w plik8" > kat/plik8.mp3
echo "Find 1"
find kat -type f -name "*.txt" -perm -u+x -a ! -perm -u+r -print

echo "Find 2"
find kat -type f \( -name "*.txt" -o -name "*.mp3" \) -a -size +0 -print

#################################################################################################
#Zadanie1: Struktura plików do utworzenia w skrypcie.
#Należy znaleźć pliki o rozszerzeniu txt do których właściciel ma prawo wykonywania, ale nie czytania
#Znaleźć pliki txt lub mp3 których rozmiar jest większy od zera (a nie różny od zera) i które są plikami
#################################################################################################