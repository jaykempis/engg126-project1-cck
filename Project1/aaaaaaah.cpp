//ENGG 126
//Project 1: Rudimentary Shell Interpreter
//by: Iris Carson, Antonio Castro, and Joshua Kempis
//--------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>

using namespace std;

void getCurrDir (string &cDir)
{
  char tmp[256];
  getcwd (tmp, 256);
  //cout<<"Current working directory: "<< tmp << endl;
  cDir = tmp;
}

void fileRead (string filename, string &contents)
{
  string line;
  ifstream file (filename);

  if (file.is_open())
  {
    while (getline (file, line))
    {
	  cout << line << endl;
	  contents = contents + line + "\n";
    }
	file.close();
  }
  else 
  {
    cout <<"File does not exist"<<endl;
  }
}

void fileWrite (string filename, string line)
{
  ofstream file(filename);
  file << line;
  file.close();
}

string exec(string command) 
{
  char buffer[128];
  string result = "";

  // Open pipe to file
  FILE* pipe = popen(command.c_str(), "r");
  if (!pipe) {
    return "popen failed!";
  }
  // read till end of process:
  while (!feof(pipe))
  {
    // use buffer to read and add to result
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }
  pclose(pipe);
  return result;
}

void parsing(string cmd, vector <string> &comms, 
             string &c1, string &c2, int &mode)
{
  stringstream ss(cmd);
  string word;
  comms.clear();
  while (ss>>word)
  {
    comms.push_back(word); 
  }
  bool found = false;
  for (int i = 0; i < comms.size(); i++)
  {	
    if (comms[i] == "|" || comms[i] == ">" || comms[i] == "<")
	{ 
      if (comms[i] == "|") mode = 1;
	  else if (comms[i] == ">") mode = 2;
	  else if (comms[i] == "<") mode = 3;
	  
	  found = true;
      
	  cout<<"found symbol:"<<comms[i]<<endl;
      for (int j=0; j < i; j++)
	  {
        c1 = c1 + comms[j] + ' ';	  
      }
      //cout<<c1<<endl;
	  
	  for (int k = i+1; k < comms.size(); k++)
	  {
        c2 = c2 + comms[k] + ' ';	  
      }
      //cout<<c2<<endl;
    }
	if (found == false) mode = 0;
  }
}

void pipeCommand(char** cmd1, char** cmd2) {
  int fds[2];
  pipe(fds);
  if (fork() == 0) {
        // Reassign stdin to fds[0] end of pipe.
        dup2(fds[1], STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);
        execvp(cmd1[0], cmd1);
    }
    // child process #2
    if (fork() == 0) {
        // Reassign stdout to fds[1] end of pipe.
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        close(fds[1]);
        execvp(cmd2[1], cmd2);
    }
    close(fds[0]);
    close(fds[1]);
    wait(NULL);
}


int main()
{
  string cmd, dir, command, c1, c2, content;
  vector <string> commands;
  int mode;
  getCurrDir(dir);
  //cout<<dir<<endl;
  do
  {	
    cout<<"\n"<<dir<<"\n[CMD] : ";
    getline(cin, cmd);
	  parsing(cmd, commands, c1, c2, mode);
	  cout<<"MODE:"<<mode<<endl;
	
    if (mode == 1)
    {
      cout<<"Entered mode 1"<<endl;
      cout << "C1: " << c1 << endl;
      cout << "C2: " << c2 << endl;
      char * C1 = c1.data();
      char * C2 = c2.data();

      char *cmd1[] = {C1, NULL};
      char *cmd2[] = {C2, NULL};

      pipeCommand(cmd1,cmd2);
    }

    else if (mode == 2)
    {
      cout<<"Entered mode 2"<<endl;
      content = exec(c1);
      fileWrite(c2, content);
      cout << "C1: " << c1 << endl;
      cout << "C2: " << c2 << endl;
    }

	  else if (mode == 3)
    {
	    cout<<"Entered mode 3"<<endl;
      cout << "C1: " << c1 << endl;
      cout << "C2: " << c2 << endl;
      fileRead(c2, content);
      cout << "Content: " << content << endl;
	    cout<< exec(c1 + " " + content) <<endl;
	  }

    else
    {
      cout<<"Entered mode 0"<<endl;
      content = exec(cmd);
      //fileWrite("log.txt", content);
      cout << content;
      cout << "C1: " << c1 << endl;
      cout << "C2: " << c2 << endl;
    } 
    c1.clear();
    c2.clear();
  }
  while (cmd != "exit");
}
