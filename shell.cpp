#pragma warning (disable: 4996)
#include "shell.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>


using namespace std;

shell::shell()
{
	active = true;
  amper = false;
}

void shell::displayHist() {
	
	if (history.empty()) {
		cout << "The history is empty!";
	}
	else {
		int begin = 0;

		if (history.size() > 10)
			int begin = history.size() - 10;

		for (int i = begin; i < history.size(); i++) {
			cout << "command " << i + 0 << " is " << history[i] << endl;
		}
	}
}

void shell::parseline(char buf [], char* make []){
  
	char* c = strtok(buf, " ");

  int i = 0;
  
	while (c != NULL) {
		make[i] = c;
		c = strtok(NULL, " ");
		i++;
	}
  
  if(strcmp(make[i-1],"&") == 0){
    make[i-1]= NULL;
    amper = true;
  }
  else{
    amper = false;
  }
}


void shell::execCommUser(char* make[]) {
	string comm(make[0]);
	
	if (comm == "exit") {
		active = false;
		displayHist();
	}
	else if (comm == "history")
	{
		history.push_back(comm);
		displayHist();
	}
  else if (comm[0] == '!'){
    char code[MAXLINE];
    char* make[MAXLINE / 2+1];
    int his = history.size();
    if(history.empty()){
      cout<<"Nothing left in the history!"<< endl;      
    }
    else{
      strcpy(code, history[his-1].c_str());
      history.push_back(code);
      parseline(code, make);
      if(isUserComm(make))
        execCommUser(make);
      else
        ShellComm(make);
      
    }
      
  }
}


bool shell::isUserComm(char* make[]){
  string comm(make[0]);
  bool user = false;
  if(comm == "exit" || comm == "history" || comm == "!"){
    user = true;
  }
  return user;
}


void shell::ShellComm(char* make[]){
  history.push_back(make[0]);
  
  pid_t pid = fork();

  if(pid == 0){
    
    execvp(make[0], make);
    cout << "Child "<< endl;
    cout << "no execvp command found!" << endl;
    exit(1);
  }
  else if (pid > 0){
    if(amper == false){
      cout << "waiting"<< endl;
      wait(NULL);
    }
    else{
      cout << "parent"<< endl;
    }
  }
  else{
    cout << "The fork has faild" << endl;
    exit(1);
    
  }
  
  
}
