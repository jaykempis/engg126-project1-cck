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
      //cout << line << endl;
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
  /* 
  ofstream file;
  file.open(filename);
  file << line;
  file.close();
  */
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
  
  if (!pipe)
  {
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
      if (comms[i] == "|")
	  { 
        mode = 1;
      }
	  else if (comms[i] == ">") 
	  { 
        mode = 2;
      }
      else if (comms[i] == "<")  
	  { 
        mode = 3;
      }

      found = true;

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

int pipeFunc(string cmd1, string cmd2, int mode) 
{
  int fd1[2]; // first pipe
  int fd2[2]; // second pipe

  int pid;
  string temp;

  if (pipe(fd1) < 0)
  {
    cout<<"Pipe Failed"<<endl;
    return 1;
  }
  if (pipe(fd1) < 0) 
  {
    cout<<"Pipe Failed"<<endl;
    return 1;
  }

  pid = fork();

  if (mode == 3)
  {
    fileRead(cmd2, temp);
  }
  else 
  {
    temp = exec(cmd1);
  }

  char inbuf[temp.length()];
  char outbuf[temp.length()];

  if (pid < 0) 
  {
    cout<<"Fork Failed"<<endl;
    return 1;
  }
  
  //Parent Process
  else if (pid > 0)
  {
    close(fd1[0]); // Close reading end of first pipe
    // Write input string and close writing end of first pipe.
    write(fd1[1], temp.c_str(), temp.length()+1);
    close(fd1[1]);

    wait(NULL);
    read(fd2[0], outbuf, temp.length());
    if (mode == 3) fileWrite(cmd2, outbuf);
    close(fd2[0]);
  }

  //Child process
  else
  {
    // Read a string using first pipe
    read(fd1[0], inbuf, temp.length());
    inbuf[temp.length()] = '\0';

    fileWrite("log.txt", inbuf);

    if (mode == 1)
    {
      temp = exec(cmd2 + " " + "log.txt");
      cout <<temp<<endl;
      write(fd2[1], temp.c_str(), temp.length()+1);
    }
  
    else if (mode == 2)
    {
      fileWrite(cmd2, inbuf); 
      write(fd2[1], temp.c_str(), temp.length()+1);
    }
  
    else if (mode == 3)
    {
      temp = exec(cmd1 + " " + "log.txt");
      cout<<temp<<endl;
      write(fd2[1], temp.c_str(), temp.length());
    }

    //cout<<"BUF CONTENTS:\n"<<inbuf<<endl;
    close(fd1[0]);
    close(fd2[1]);
    exit(0);
  }  
  return 0;
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
    cout<<"==========================="<<endl;

    if (mode == 0)
    {
      content = exec(cmd);
      fileWrite("log.txt", content);
      cout << content;
    }

    else
    {
      pipeFunc(c1, c2, mode);
    } 
    c1.clear();
    c2.clear();
  }
  while (cmd != "exit");
}