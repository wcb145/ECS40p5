#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include "iostream"
#include "permissions.h"
#include "Time.h"
#include "list.h"
using namespace std;

class Directory
{
  char *name;
  Time time;
  //Directory **subDirectories;
  LinkedList subDirectories;  // wills addition
  int subDirectoryCount;
  Directory *parent;
  Permissions permissions;
  //void addDirectory(const char *nam, short umask);
  short checkOctals(const char *octals) const;
public:
  Directory(const char *nam, short umask = 0, Directory *paren = NULL);
  //Directory(const Directory& rhs);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[]);
  void cp(int argCount, const char *argument[]);
  void chmod(int argCount, const char *arguments[]);
    // changes the permissions of the arguments
  void ls(int argCount, const char *arguments[]) const;
  void mkdir(int argCount, const char *arguments[], short umask);
  void showPath() const;
  bool operator== (const Directory &rhs) const;
  bool operator< (const Directory &rhs) const; // wills addition
  friend ostream& operator<< (ostream &os, Directory const &rhs);
  friend istream& operator>> (istream &is, Directory &rhs);
};  // class Directory
#endif  // DIRECTORY_H

