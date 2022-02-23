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
	void parseline(char buf [], char* make []);
	void execCommUser(char* make[]);
	void displayHist();

private:
	vector<string> history;
};