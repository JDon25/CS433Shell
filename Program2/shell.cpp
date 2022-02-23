#pragma warning (disable: 4996)
#include "shell.h"
#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace std;

shell::shell()
{
	active = true;
}

void shell::displayHist() {
	
	if (history.empty()) {
		cout << "The history is empty!";
	}
	else {
		int begin = 0;
		cout << history.size();
		if (history.size() > 10) {
			int size = history.size();
			begin = size - 10;
		}

		for (int i = begin; i < history.size(); i++) {
			cout << "command " << i + 0 << " is " << history[i] << endl;
		}
	}
}

void shell::parseline(char buf [], char* make []){
	int i = 0;

	char* c = strtok(buf, "(");

	while (c != NULL) {
		make[i] = c;
		c = strtok(NULL, "(");
		i++;
	}
}
void shell::execCommUser(char* make[]) {
	string comm = make[0];
	
	if (comm == "exit") {
		active = false;
		displayHist();
	}
	else if (comm == "history")
	{
		history.push_back(comm);
		displayHist();
	}
	else if (comm == "fork") {
		history.push_back(comm);
	}
}
