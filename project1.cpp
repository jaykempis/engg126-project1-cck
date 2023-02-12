//ENGG 126
//Project 1: Rudimentary Shell Interpreter
//by: Iris Carson, Antonio Castro, and Joshua Kempis

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include<stdlib.h>

using namespace std;

//function to run a command using string 
string exec(string command) {
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {
      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

int main() {
   
   string command;
   cout << "$ ";
   getline(cin,command);

   cout << "Command: " << command << endl;

   string content = exec(command);
   cout << content;

}