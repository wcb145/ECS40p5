#ifndef FUNIX_H
  #define FUNIX_H

#include "directory.h"

const int COMMAND_LENGTH = 80;
const int NUM_COMMANDS = 7;
const int MAX_ARGUMENTS = 40;

class Funix
{
  Directory *currentDirectory;
  int eXit(int argCount, const char *arguments[]);
    // checks "exit" command, returns 0 on proper exit
  void getCommand(char *command);  
    // writes prompt and reads command
  int processCommand(char *command);  // returns 0 on proper exit
  void writePrompt() const;  // shows path and '#'
public:
  Funix(); 
  ~Funix();
  void run();  
    // reads and processes commands in a loop until proper exit
    // creates currentDirectory, and sets tempmask 
   friend ostream& operator<< (ostream &os, const Funix &rhs);
   friend istream& operator>> (istream &is, Funix &rhs);
 
};  // class Funix
#endif

