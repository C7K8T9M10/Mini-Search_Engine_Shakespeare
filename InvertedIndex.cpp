#include<iostream>
#include<iomanip>
#include<map>
#include<set>
#include <string.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include "porter2_stemmer.h"
//Here I use the porter2_stemmer function to make it work.
//Below are things that I use for storing information.
std::map<std::string,std::map<int,int>>invertedindex;
/*
   It is a map, the outer string represents the word, and
   the inner map represents the text file and the time
   They occured in the corresponding file.
*/
std::set<std::string> stopwordlist;
/*
   A set to store stop words, you can download it from the
   Internet, just like me.
*/
std::set<std::string> totalwords;
/*
   A structure to store all the words that have appeared in
    the file, easy to understand.
*/
std::vector<std::string> filename;
/*
   To store the name of each file.
*/
void getstopword() {
    std::string file = "stopword.txt";//open the file
    std::ifstream in(file);

    if (in) {
        std::string word;
        while (in >> word) {
            stopwordlist.insert(word);//insert it one by one
        }
        in.close();
        std::cout << "Stop words have been loaded." << std::endl;
    } else {
        std::cerr << "Unable to open the file: " << file << std::endl;//error control
    }
}
/*
    for the stemmer function, please open porter2_stemmer.cpp
    and its header file for more details(Thanks for the function
    , it really save some time for us.)
*/
std::string stemmer(std::string s){
    Porter2Stemmer::trim(s);
    Porter2Stemmer::stem(s);
    return s;
}
/*
    Obviously it is a function to know what are those files we are
    going to check.
*/
void readfiletitle(){
      std::string file = "titles.txt";
    std::ifstream in(file);
    if (in) {
        std::string word;
        while (in >> word) {
            filename.push_back(word);
        }
        in.close();
        std::cout << "Titles have been loaded." << std::endl;
    } else {
        std::cerr << "Unable to open the file: " << file << std::endl;
    }
}
/*
   To check whether the input is in the stop word list, a necessary
   function!
*/
bool isstopword(std::string s){
    if(stopwordlist.empty()){
        getstopword();
    }
    if(stopwordlist.find(s)==stopwordlist.end()){
        return true;
    }
    return false;
}
/*
    The function actually do two things: word counting and building
    inverted file index, save them to the map. The map make everything
    comprehensive and easy.
*/
void readfilecontent(){
    for(int i=0;i<filename.size();i++){
        std::string path="FullShakespeare//";
        std::ifstream in(path+filename[i]);
        if(in){
        std::string word;
        while(in>>word) {
          word=stemmer(word);//stem the word first
          if(isstopword(word)==false){
            continue;
          }
          if(totalwords.find(word)==totalwords.end()){
            totalwords.insert(word);
          }
          if (invertedindex.find(word)==invertedindex.end()) {
    // 如果外层键不存在，则添加一个新的内层 map
    invertedindex[word]=std::map<int, int>();
        }
    invertedindex[word][i]++;
    }
        }else{
            std::cerr << "Unable to open the file: " << filename[i] << std::endl;
        }
       
}
}
/*
   The main function, which you can think it is the search function,
    it make the search happenand deal with the users input, you can input
    g++  InvertedIndex.cpp porter2_stemmer.cpp -o main to bulid active file
    and check whether it is working properly, see more at README.

*/

int main(){
    getstopword();
    readfiletitle();
    readfilecontent();
home: //Every time a non-quit operation is over,we will be back here.
    std::cout<<"Here we read all the texts you provided, Here are ";
    std::cout<<invertedindex.size()<<" distinct words"<<std::endl;
    std::cout<<"The size of stop word list is "<<stopwordlist.size()<<std::endl;
    std::cout<<"Press S to search single word, press M to search multiple words, press Q to exit:";
    char t;
    std::cin>>t;
    if(t=='S'||t=='s'){//single word search
        std::string word;
    std::cin>>word;
    word=stemmer(word);
    if(isstopword(word)==false){
        std::cout<<"You have entered a stop word"<<std::endl;
        goto home;
    }
    if (invertedindex.find(word)!=invertedindex.end()) {
        std::map<int, int>& inner_map = invertedindex[word];
        for (const auto& pair : inner_map) {
            std::cout << " In Book: " << filename[pair.first] << ",It appears: " << pair.second << "times" <<std::endl;
        }
    } else {
        std::cout << "Word not found in inverted index."<<std::endl;
    }
        std::cout << "Press any key to back to the search"<<std::endl;
        char w;
        std::cin>>w;
        goto home;
    }else if(t=='q'||t=='Q'){//quit the program
        exit(-1);
    }else if(t=='m'||t=='M'){//multiple words search
        std::cin.ignore();
        std::string s;
        std::vector<int> appearance(filename.size(), 0);
        int i=0;
        std::getline(std::cin,s);
        std::stringstream ss(s);
        std::vector<std::string>words;
        std::string token;
        while (ss >>token) {
        stemmer(token);//To handle input correstly, stemming is also necessary.
        words.push_back(token);
        }
        while(i<words.size()){
          std::map<int, int>& inner_map = invertedindex[words[i]];  
          for (const auto& pair : inner_map){
            appearance[pair.first]++; 
             }
          i++;
        }
        int isresult=0;
        for(int k=0;k<filename.size();k++){
            if(appearance[k]==i){//This is to check whether all the words appears in the same file.
                std::cout<<"Those words all appears in "<<filename[k]<<std::endl;
                isresult=1;
        }
        }
        if(isresult==0){
            std::cout<<"No results, back to the homepage"<<std::endl;
        }
        goto home;
        }else{
        std::cout<<"Illegal Command! "<<std::endl;
        goto home;
    }
    system("Pause");
}