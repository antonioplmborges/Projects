#include "tsh.h"

using namespace std;

int main(){
	char cmd[81];
	char *cmdTokens[25];
	simple_shell *shell = new simple_shell();

	while (true){
		cout << "tsh> ";
		fgets(cmd, sizeof(cmd), stdin);
		//if(strlen(cmd) == 0) continue;
		//cmd[strlen(cmd) - 1] = '\0'; //added line
		if (cmd[0] == '\n') continue;
		//if (cmd[0] == '\0') continue;
    //istringstream s(cmd);
	//	cout<<"abc"<<endl;
	 	//getline(s >> ws, line);
/*		int i = 0;
		bool isEmpty = true;
		while(i != int(strlen(cmd)-1)){
			if(isblank(cmd[i])){
				i++;
				continue;
			}else{
				isEmpty = false;
				break;
			}
		}
		if(isEmpty == true) continue;
		string line = strtok(cmd, " ");
		//cout<<strlen(line.c_str())<<endl;
		if(line.empty()) {cout<<"abc"<<endl;continue;}
		else {
			char *cstr = new char[81];
			strcpy(cstr, line.c_str());
			strcpy(cmd,cstr);
		}*/
		//if (cmd[0] == ' ') continue;
		shell->parse_command(cmd, cmdTokens);
		//std::cout << *cmdTokens << '\n';
		if (shell->isQuit(*cmdTokens)){
			exit(0);
		}
		else{
			shell->exec_command(cmdTokens);
		}

	}
	exit(1);
}
