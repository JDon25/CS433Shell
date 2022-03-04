/*
Assignment: 2 - Shell OS

Name: Tyler Desharnais, James Donaldson
Date: 8 March 2022
  */
#pragma once
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXLINE = 80;
//H-file to establish all the functions in shell.cpp
class shell {

public:
	shell();
  //variable for active and ampersand
  bool active;
  bool amper;
  //function to display history
  void displayHist();
  //function to parse the string to get the command
	void parseline(char buf [], char* make []);
  //function to execute the user command
	void execCommUser(char* make[]);
  //function to execute to the shell command 
  void ShellComm(char* make[]);
  //function to check if entered command is a user command
  bool isUserComm (char* make[]);
  //function to store into history
  void storHis (char comm[]);
private:
  //vector for the history function of the shell
	vector<string> history;
};
