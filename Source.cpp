/*
Assignment: 2 - Shell OS

Name: Tyler Desharnais, James Donaldson
Date: 8 March 2022

Creating a simple Shell program to execute a fork and execute simple linux commands. Also has various user commands such as exit, history, and !!.
*/

#include <cstring>
#include <iostream>
#include "shell.h"

using namespace std;

int main() {
  //create the shell
	shell comand;

  //while loop to execute as long as the active is set to true
	while (comand.active) {
    //char variable to accept user entry
		char entry[MAXLINE];
    //store entry into a backup and to pass to history function
    char backup [MAXLINE];
    //variable used for the parsed variable
		char* make[MAXLINE / 2 + 1];
    //cout to display to screen for command.
		cout << "osh> ";
    fflush(stdout);
    //gets entry from user and stores in entry variable
		cin.getline(entry, MAXLINE);
    //stores the entry into the backup
    strcpy(backup, entry);

    //parses the entry variable and stores it into make
		comand.parseline(entry, make);

    //if statment to check if it is a user command or a shell command.
		if (comand.isUserComm(make)){
      //goes to user command function
      comand.execCommUser(make);
    }
    else{
      //passes the backup to history and than pass make to the shell command.
      comand.storHis(backup);
      comand.ShellComm(make);
    }
	}
  return 0;
}
