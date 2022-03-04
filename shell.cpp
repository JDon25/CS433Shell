/*
Assignment: 2 - Shell OS

Name: Tyler Desharnais, James Donaldson
Date: 8 March 2022
  */
#include "shell.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>


using namespace std;
//Default constructor to make the shell.
shell::shell()
{
	active = true;
  amper = false;
}
//purpose - function to display the most recent 10 commands
void shell::displayHist() {
	//if statment to check if the history is empty
	if (history.empty()) {
		cout << "The history is empty!";
	}
  //drops into the else if history is not empty
	else {
    //stores the history size and creats a begin variable
    int size = history.size();
    int begin = 0;
    
    //if the size is larger than 10 will set begin to size - 10
		if (size > 10){	begin = size - 10;}
    //for loop to display the history
   for (int i = begin; i < size; i++) {
			cout << "Command " << i + 1 << "  " << history[i] << endl;
		}
	}
}

//purpose - to parse out the buf argument into the make pointer variable
void shell::parseline(char buf [], char* make []){
  // token the buf to parse through
	char* c = strtok(buf, " ");
  //i variable to save the last spot
  int i = 0;

  //while loop to store into the make variable
	while (c != NULL) {
		make[i] = c;
		c = strtok(NULL, " ");
		i++;
	}
  //if statment to check if the end has an ampersand to flag for the parent
  if(strcmp(make[i-1],"&") == 0){
    make[i-1]= NULL;
    amper = true;
  }
}

//purpose - function to execute user entries
void shell::execCommUser(char* make[]) {
  //stores in a string to compare for users statments
	string comm(make[0]);
  
	//command for the program to end
	if (comm == "exit") {
		active = false;
		displayHist();
	}

  //command to display the history
	else if (comm == "history")
	{
		storHis(make[0]);
		displayHist();
	}
  //command to trigger the previous command  
  else if (comm == "!!"){
    char code[MAXLINE];
    char* make[MAXLINE / 2+1];
    int his = history.size();
    
    if(history.empty()){
      cout<<"Nothing left in the history!"<< endl;      
    }
    else{
      //coppy command form the history into code
      strcpy(code, history[his-1].c_str());
      //store the code back into history
      storHis(code);
      //parse the code out for passing to user or shell
      parseline(code, make);
      //if to pass to user or and else to pass to shell
      if(isUserComm(make)){
        execCommUser(make);}
      else{
        ShellComm(make);}
      
    }
      
  }
}

//purpose - checks the make to determine if the make is a user command or not.
bool shell::isUserComm(char* make[]){
  //stores make variable into comm for comparison
  string comm(make[0]);
  //establish the bool variable to return
  bool user = false;
  //if statment to identify a user command and change the bool to true
  if(comm == "exit" || comm == "history" || comm == "!!"){
    user = true;
  }
  //return bool statment
  return user;
}
//simple function to pass to history
void shell::storHis(char comm[]){
  history.push_back(comm);
}
//purpose - function to execute a the shell command
void shell::ShellComm(char* make[]){

  //establish the fork
  pid_t pid = fork();

  //if statment to move to the child or skip to the parent.
  if(pid == 0){
    //execute the child command
    execvp(make[0], make);
    //print statment if a proper command isn't entered
    cout << "no execvp command found!" << endl;
    exit(1);
    
  }
  //drops into parent to conduct the command.
  else if (pid > 0){
    //if ampersand variable is false parent will move to wait
    if(amper == false){
      wait(NULL);
    }
  }
  //if both parent and child don't trigger the fork has failed
  else{
    cout << "This fork has faild" << endl;
    exit(1);
    
  }
  
  
}
