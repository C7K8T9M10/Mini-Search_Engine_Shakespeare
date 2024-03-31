### Mini Search Engine
We use stmr.c and stmr.h from github to do stemming.
The stop word list is from [stopword](https://countwordsfree.com/stopwords).
##### How do I get the .txt file.
First, I clone the html file, then I write a python program to convert them into text file(convertion.py). But also, I make some changes on the name and content of some files. 
##### my program
Download the repository in local, under your VSC work place, open InvertedIndex.cpp, enter the directory in powershell, and type g++  InvertedIndex.cpp porter2_stemmer.cpp -o main to build active file, then it can work properly.
There is also a readable report.