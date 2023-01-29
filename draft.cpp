//ENGG 126
//Project 1: Rudimentary Shell Interpreter
//by: Iris Carson, Antonio Castro, and Joshua Kempis

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void helpCMD ()
{
  cout<<"\nLists of possible commands: \n"
      <<"* help            - displays the lists of commands \n"
      <<"* exit            - closes the program"<<endl;
}

int main(){

    string cmd;
    do
    {
        cout<<"\n[CMD] : ";
        getline(cin, cmd);
        if (cmd == "help")
        {
            helpCMD();
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