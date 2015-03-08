//Questo programma serve per avvisare l'avvenuta chiusura del programma

#include <stdlib.h>
#include <iostream>
#include <string.h>


void play(const char* musica){

  std::string command= "afplay ";

  command+=musica;
  system(command.c_str());

}

void say(const char* frase, const char* person="Alice"){
  char OS[100];
  fgets(OS,100,popen("uname","r"));

  if(strncmp(OS,"Darwin",6)==0){
  
    std::string command= "say ";
  
    command+= "-v ";
    command+=person;
    command+=" ";    
    command+=frase;
    system(command.c_str());

    }else{//end if for Operatin System

      std::cout<<"Non hai OSX..."<<std::endl;
      std::cout<<"Leggitelo da solo!"<<std::endl;
      std::cout<<frase<<std::endl;
    }
  
}
