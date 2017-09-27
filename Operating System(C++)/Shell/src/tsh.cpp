#include "tsh.h"

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
  // TODO: tokenize the command string into arguments
  //cout<<*cmd<<endl;
  //cout<<**cmdTokens<<endl;
/* *cmdTokens = strtok(cmd," ");
 while (*cmdTokens != NULL)
  {
    cout<<*cmdTokens<<'\n';
    *cmdTokens = strtok (NULL, " ");
  }
  cout<<*cmdTokens<<endl;*/
/*
  int i = 0;
  char * temparg = strtok(cmd, " ");
      while ( temparg ) {

          if (i >= 25) break;
          cmdTokens[i] = strdup(temparg);
          ++i;
          temparg = strtok(NULL, " ");
  }
*/


  ///std::cout << "/* message */" << '\n';
  int n = 0;

  for (char * p = strtok(cmd, " \n"); n <= 25 && p !=NULL; p = strtok(NULL, " \n"))
  {
    //if () break; // maximum number of storable tokens exceeded

    cmdTokens[n] = new char[25];
    strcpy(cmdTokens[n],p);
    n++;
  }

  cmdTokens[n]= NULL;



/*
for (int i = 0; i != n; ++i)
    cout<<cmdTokens[i]<<endl;
*/
}

void simple_shell::exec_command(char **argv)
{
  // TODO: fork a child process to execute the command.
  // parent process should wait for the child process to complete and reap it

 int rc = fork();
 if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child: redirect standard output to a file

    execvp(argv[0], argv);
    if (execvp(argv[0], argv) < 0)
{
      //cout << "./";
    exit(EXIT_FAILURE);
}
    exit(0);
 } else { // parent
   //cout << argv[0]<<endl;
    wait(&rc);
 }

}

bool simple_shell::isQuit(char *cmd){
  // TODO: check for the command "quit" that terminates the shell
  if( strcmp(cmd, "quit") == 0) return true;

  return false;
}
