#include <iostream>
#include <fstream>
#include <string>
#include "CPU.h"

enum Tokens{

};


class lexer{
public:
  void lex(std::string assembly){
    std::ifstream file(assembly);
    for(int i = 0; i < assembly.size(); i++){
      CurrentWord += assembly[i];
      if(!isspace(assembly[i])){
        CurrentWord = assembly[i];
      }
    }
  }
  void PrintCurrentWord(){
    std::cout << CurrentWord << std::endl;
  }
private:
  char CurrentWord;
};