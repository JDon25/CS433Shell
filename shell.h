#pragma once
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXLINE = 80;

class shell {

public:
	shell();
  bool active;
  bool amper;
  void displayHist();
	void parseline(char buf [], char* make []);
	void execCommUser(char* make[]);
  void ShellComm(char* make[]);
  bool isUserComm (char* make[]);
private:
	vector<string> history;
};
