#include <cstring>
#include <iostream>
#include "shell.h"

using namespace std;

int main() {
	shell comand;

	while (comand.active) {
		char entry[MAXLINE];
		char* make[MAXLINE / 2 + 1];

		cout << "command?";
    
		cin.getline(entry, MAXLINE);

		comand.parseline(entry, make);

		if (comand.isUserComm(make)){
      comand.execCommUser(make);
    }
    else{
      comand.ShellComm(make);
    }
	}
}
