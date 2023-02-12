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

using namespace std;

void fileRead (string filename)
{
  string line;
  ifstream file (filename);

  if (file.is_open())
  {
    while (getline (file, line))
    {
	  cout << line << endl;
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
  _pclose(pipe);
  return result;
}

void parsing(string cmd, vector <string> &comms, 
             string call, string file, int mode)
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
        call = call + comms[j] + ' ';	  
      }
      //cout<<call<<endl;
	  
	  for (int k = i+1; k < comms.size(); k++)
	  {
        file = file + comms[k] + ' ';	  
      }
      //cout<<file<<endl;
    }
  }
}

int main()
{
  string cmd, dir;
  vector <string> commands;
  getCurrDir(dir);
  //cout<<dir<<endl;
  do
  {	
    cout<<"\n"<<dir<<"\n[CMD] : ";
    getline(cin, cmd);
	parsing(cmd, commands);
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
    string content = exec(command);
    cout << content; */
  }
  while (cmd != "exit");
}
