#!/bin/bash

rm -Rf lab2
mkdir lab2
mkdir lab2/kat1 lab2/kat2 lab2/kat4
touch lab2/kat1/plik1 lab2/kat1/plik2 lab2/kat1/plik3
echo "To jest plik1" > lab2/kat1/plik1
echo "To jest plik2" > lab2/kat1/plik2
echo "To jest plik3" > lab2/kat1/plik3
ln -s ../kat1/plik1 lab2/kat2/link1
ln -s ../kat1/plik2 lab2/kat2/link2
ln -s `realpath lab2/kat1/plik3` lab2/kat2/link3
ln -s kat2 lab2/kat3
cp -d lab2/kat2/link1 lab2/kat4/link1_copy
cp -d lab2/kat2/link2 lab2/kat4/link2_copy
cp -d lab2/kat2/link3 lab2/kat4/link3_copy

####################################################################################
#Zadanie 1: Utworzenie katalogu lab2, w nim utworzenie 4 katalogów, 
#w pierwszym należało stworzyć 3 pliki (wypełnione), 
#w drugim katalogu trzeba było utworzyć dowiązania symboliczne do plików z katalogu 
#pierwszego (do pliku 1 i 2 ze ścieżką względną, do 3 ze ścieżką bezwzględną), 
#trzeci katalog miał zawierać dowiązanie do katalogu 2, w katalogu czwartym miały 
#znaleźć się skopiowane dowiązania z katalogu drugiego. Na początku skryptu należało 
#usunąć katalog lab2- jeżeli istniał.
####################################################################################
