//PROJECT 1 - Rudimentary Shell Interpreter
//by Iris Nicole Carson

#include <iostream>
#include <fstream>

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

int main (int argc, char **argv)
{
  //for checking of user input
  cout<<"No. of words in entered command: "<<argc
      <<" w/ arguments:"<<endl;
  for (int i=0; i < argc; i++)
  {
    cout << argv[i] <<endl;
  }
  
  //testing the file functions
  string line = "sample";
  fileRead("trial.txt");
  fileWrite("trial.txt", line);
  fileRead("trial.txt");

return 0;
}
