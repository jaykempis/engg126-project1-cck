//ENGG 126
//Project 1: Rudimentary Shell Interpreter
//by: Iris Carson, Antonio Castro, and Joshua Kempis
//--------------------------------------------------------------------
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <windows.h>
#include <stdexcept>

using namespace std;

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
  else cout <<"File does not exist"<<endl;
}

void fileWrite (string filename, string line)
{
  ofstream file(filename);
  file << line;
  file.close();
}

void getCurrDir (string &cDir)
{
  char tmp[256];
  getcwd (tmp, 256);
  //cout<<"Current working directory: "<< tmp << endl;
  cDir = tmp;
}

string exec(string command) 
{
  char buffer[128];
  string result = "";

  // Open pipe to file
  FILE* pipe = _popen(command.c_str(), "r");
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
  _pclose(pipe);
  return result;
}

void parsing(string cmd, vector <string> &comms, 
             string &c1, string &c2, int &mode)
{
  stringstream ss(cmd);
  string word;
  while (ss>>word)
  {
    comms.push_back(word); 
  }
  for (int i = 0; i < comms.size(); i++)
  {
    if (comms[i] == "|" || comms[i] == ">" || comms[i] == "<")
	{ 
      if (comms[i] == "|") mode = 1;
	  if (comms[i] == ">") mode = 2;
	  if (comms[i] == "<") mode = 3;

      for (int j=0; j < i; j++)
	  {
        c1 = c1 + comms[j] + ' ';	  
      }
      //cout<<call<<endl;
	  
	  for (int k = i+1; k < comms.size(); k++)
	  {
        c2 = c2 + comms[k] + ' ';	  
      }
      //cout<<file<<endl;
    }
	else mode = 0;
  }
}

void forkFunc()
{
  //fork();
  cout<<"Processing ID:"<<getpid()<<endl;
}

int main()
{
  string cmd, dir, command, c1, c2, content;
  vector <string> commands;
  int mode = 0;
  getCurrDir(dir);
  //cout<<dir<<endl;
  do
  {	
    cout<<"\n"<<dir<<"\n[CMD] : ";
    getline(cin, cmd);
	parsing(cmd, commands, c1, c2, mode);
	
	if (mode == 1){
      
	}
	else if (mode == 2){
      content = exec(c1);
	  //cout<< content;
	  fileWrite(c1, content);
    }
	else if (mode == 3){
      fileRead(c2, content);
	  //cout<<content;
	  //cout<<c1<<endl;
	  //cout<<c2<<endl;
	  cout<<exec(c1 +" "+ c2)<<endl;
	}
	else{
	  content = exec(cmd);
	  fileWrite("log.txt", content);
      cout << content;
    }
	/*
	for (int i = 0; i < commands.size(); i++)
    {
      cout<<commands[i]<<endl;
    }*/
	
	/*
	system(cmd.c_str());
    string command;
    cout << "> ";
    getline(cin,command);
    cout << "Command: " << command << endl;
	*/
    
  }
  while (cmd != "exit");
}
