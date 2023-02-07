//ENGG 126
//Project 1: Rudimentary Shell Interpreter
//by: Iris Carson, Antonio Castro, and Joshua Kempis

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void helpCMD ()
{
  cout<<"\nLists of possible commands: \n"
      <<"* help            - displays the lists of commands \n"
      <<"* debug           - turn debugging mode on \n"
      <<"* pwd             - displays the current directory \n"
      <<"* cd <dirname>    - changes directory \n"
      <<"* exit            - closes the program"<<endl;
}
string setDirectory(string location)
{
    stringstream pathname(location);
    string endloc, strout = "user-student", space = " ";
    while(getline(pathname, endloc,'/'))
    {
        //cout << endloc << '/';
    }
    if(strout == endloc) strout = strout + " ~";
    else strout = strout + space + endloc;
    
    return strout;
}

int main(){

    string cmdline, cmd;
    const int ARG_MAXX = 8;
    string home = "Users/user-student";
    string loc = home;
    string dir, filler = "<!NUL|ERR01>";
    string parameter[ARG_MAXX];
    bool debug = false;

    for (size_t i = 0; i < ARG_MAXX; i++)
    {
        parameter[i] = filler;
    }
    
    do
    {
        dir = setDirectory(loc);
        cout<<"\n"<<dir<<" $ ";
        
        //PARSING PROCESS (reads lines up to ARG_MAXX arguments)
        //parameters are identified after every -space- character
        getline(cin, cmdline);
        stringstream cmdpipe(cmdline);
        cmdpipe >> cmd;
        for (int i = 0; i < ARG_MAXX; i++)
        {
            cmdpipe >> parameter[i];
        }
        

        if (cmd == "help")
        {
            helpCMD();
        }
        else if (cmd == "exit")
        {
            cout << "\n\n\nExiting..." << endl;
        }
        else if (cmd == "debug")
        {
            debug = !debug;
        }
        else if (cmd == "pwd")
        {
            cout << loc << endl;
        }
        else if (cmd == "cd")
        {
            if(parameter[0] != filler)
            {
                loc = loc +"/"+parameter[0];
                if(debug) cout << loc << endl;
            }
            else loc = home;
            parameter[0] = filler;
        }
        else cout<<"Invalid Command. " <<  
        "Type 'help' for a list of commands."<< 
        endl;

        if (debug)
        {
            cout << "DEBUG MODE ON\n";
            for (size_t i = 0; i < ARG_MAXX; i++)
            {
                cout << parameter[i] << endl;
            }
        }
        

    }
    while (cmd != "exit");
}