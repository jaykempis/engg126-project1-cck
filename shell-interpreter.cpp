//ENGG 126
//Project 1: Rudimentary Shell Interpreter
//by: Iris Carson, Antonio Castro, and Joshua Kempis

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <windows.h>
/*
#include <vector>
#include <direct.h>
*/
using namespace std;
//using namespace std::filesystem;

void helpCMD ()
{
  cout<<"\nLists of possible commands: \n"
      <<"* help            - displays the lists of commands \n"
      <<"* ls              - list all files and directories in the present working directory\n"
      <<"* exit            - closes the program"<<endl;
}

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
  cout<<"Current working directory: "<< tmp << endl;
  cDir = tmp;
}

int main()
{
  string cmd, dir;
  getCurrDir(dir);
  //cout<<dir<<endl;
  /*
  for (const auto & entry : std::filesystem::directory_iterator(dir))
    std::cout << entry.dir() << endl;
  */
  do
  {	
    cout<<"\n"<<dir<<"\n[CMD] : ";
    getline(cin, cmd);
    if (cmd == "help")
    {
      helpCMD();
    }
    else if (cmd == "ls")
    {
      cout<<"still working on this function"<<endl;
    }
    else if (cmd == "exit")
    {
      cout << "Exiting..." << endl;
    }
    else cout<<"Invalid Command. " <<
      "Type 'help' for a list of commands."<<endl;
  }
  while (cmd != "exit");
}
