#include <cstring>
#include <iostream>
#include "directory.h"
using namespace std;

Directory::Directory(const char *nam, short umask, Directory *paren)
  : subDirectoryCount(0), parent(paren) 
 {
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777, umask);
 }  // Directory()

Directory::Directory(const Directory& rhs) 
  : subDirectoryCount(rhs.subDirectoryCount), parent(rhs.parent),
  permissions(rhs.permissions)
{
  
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  
  for (int i = 0; i < subDirectoryCount; i++)
  {
    Directory *temp = rhs.subDirectories[i]; 
    Directory *tempDir = new Directory(*temp);
    tempDir->parent = this;
    subDirectories += tempDir;
  } // for
} // copy constructor

Directory::~Directory()
{
  delete [] name;

}  // ~Directory()

Directory* Directory::cd(int argCount, const char *arguments[])
{
  if (argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  }  // if two many arguments

  if (strcmp(arguments[1], "..") == 0)
  {
    if (parent)
      return parent;
    else  // this is root
      return this;
  }  // if cd ..

  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (*subDirectories[i] == Directory(arguments[1]))
    {
      if (subDirectories[i]->permissions.isPermitted(EXECUTE_PERMISSIONS))
        return subDirectories[i];
      else  // subdirectory doesn't have execute permissions
      {
        cout << arguments[1] << ": Permission denied.\n";
        return this;
      }   // else no execute permissions for the specified directory
    }  // if found the named directory 
  }  // for each subdirectory
 
  cout << "cd: " << arguments[1] << ": No such file or directory\n";
  return this;
}  // cd()

bool Directory::showcpWarnings(int argCount, const char *arguments[])
{
  
  if (argCount == 1)
  {
    cout << "cp: missing operand\n";
    cout << "Try 'cp --help' for more information.\n";
    return 1;
  }  // if only "cp"
  
  if (argCount == 2)
  {
    cout << "cp: missing operand after ‘" << arguments[1] << "’\n";
    cout << "Try 'cp --help' for more information.\n";
    return 1;
  } // if no destination 
  
  if (argCount > 3)
  {
    cout << "Too many operands" << endl;
    cout << "Try 'cp --help' for more information." << endl;
    return 1;
  } // if too many arguments
  
  if (strcmp(arguments[1], arguments[2]) == 0)
  {
    cout << "cp: ‘" << arguments[1] << "’ and "
      << "‘" << arguments[2] << "’ are the same file" << endl;
    return 1;
  } // the source and destination are the same
  
  return 0;
} // show warnings


void Directory::cp(int argCount, const char *arguments[])
{
  int match = 0, j;
  
  if (showcpWarnings(argCount, arguments))
    return;
    
  for (int i = 0; i < subDirectoryCount; i++)
    if(*subDirectories[i] == Directory(arguments[1]))
    {
      j = i;
      match = 1; 
    } // if
  if (!match)
  {
    cout << "cp: cannot stat ‘" << arguments[1] <<
      "’: No such file or directory" << endl << 
      "Try 'cp --help' for more information." << endl;
    return;
  } // if no match found
  
  if(!(permissions.isPermitted(READ_PERMISSIONS)))
  {
    cout << "cp: cannot open ‘" << arguments[1] << "’ for reading: " <<
      "Permission denied" << endl;
    return;
  } // if not permitted
  Directory *copy = new Directory(*subDirectories[j]);
  delete copy->name;
  copy->name = new char[strlen(arguments[2]) + 1];
  copy->name = strcpy(copy->name, arguments[2]);
  subDirectories += copy;
  subDirectoryCount++;
} // cd command; this is exactly 30 lines!

short Directory::checkOctals(const char *octals) const
{
  short newPermissions = 0;
  
  if (strlen(octals) > 4)
  {
     cout << "chmod: invalid mode: ‘" << octals << "’\n";
     cout << "Try 'chmod --help' for more information.\n";
    return -1;
  }  // if umask value too long.
  
  for (int i = 0; octals[i] != '\0'; i++ )
    if (octals[i] < '0' || octals[i] > '7')
    {
      cout << "chmod: invalid mode: ‘" << octals << "’\n";
      cout << "Try 'chmod --help' for more information.\n";
      return -1;
    }  // if incorrect octal
    else  // valid octal digit
      newPermissions = newPermissions * 8 + octals[i] - '0';
  
  return newPermissions;
}  // checkOctals())


void Directory::chmod(int argCount, const char *arguments[])
 // changes the permissions of the arguments
{
  int j;
  
  if (argCount == 1)
  {
    cout << "chmod: missing operand\n";
    cout << "Try 'chmod --help' for more information.\n";
    return;
  }  // if only "chmod"
  
  if (argCount == 2)
  {
    cout << "chmod: missing operand after ‘" << arguments[1] << "’\n";
    cout << "Try 'chmod --help' for more information.\n";
    return;
  }   // if only "chmod octals"
  
  short newPermissions = checkOctals(arguments[1]);
  
  if (newPermissions < 0)
    return;
  
  for (int i = 2; i < argCount; i++)
  {
    for (j = 0; j < subDirectoryCount; j++)
      if (Directory(arguments[i]) == *subDirectories[j])
      {
        subDirectories[j]->permissions.set(newPermissions, 0);
        break;
      }  // if matched name of directory with argument
    
    if (j == subDirectoryCount)
      cout << "chmod: cannot access ‘" << arguments[i] 
           << "’: No such file or directory\n";
  }  // for each filename
}  // chmod())


void Directory::ls(int argCount, const char *arguments[])const
{
  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))
    cout << "usage: ls [-l]\n";
  else  // correct number of arguments
  {
    if (permissions.isPermitted(READ_PERMISSIONS))
    {
      if (argCount == 1)  // simple ls
      {
        for (int i = 0; i < subDirectoryCount; i++)
          cout << subDirectories[i]->name << " ";

        cout << "\n";
      }  // if simple ls
      else  // must be ls -l
      {
        for (int i = 0; i < subDirectoryCount; i++)
        {
          subDirectories[i]->permissions.print();
          cout << ' ';
          subDirectories[i]->time.print();
          cout << subDirectories[i]->name << endl;
        }  // for each subdirectory
      }  // else is ls -l
    }  // if have read permissions
    else // don't have read permissions
      cout << "ls: cannot open directory .: Permission denied\n";
  }  // else correct arguments
}  // ls()


void Directory::mkdir(int argCount, const char *arguments[], short umask)
{
  int i;
  
  if (argCount == 1)
  {
    cout << "mkdir: missing operand\n";
    cout << "Try 'mkdir --help' for more information.\n";
    return;
  }  // if too many arguments
   
  for (int argPos = 1; argPos < argCount; argPos++)
  {
    for (i = 0; i < subDirectoryCount; i++)
      if (*subDirectories[i] == Directory(arguments[argPos]))
      {
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             << "’: File exists\n"; 
        break;
      }  // if subdirectory already exists.
    
    if (i == subDirectoryCount)
    {
      if (permissions.isPermitted(WRITE_PERMISSIONS))
      {
        //addDirectory(arguments[argPos] , umask);
        subDirectories+= new Directory(arguments[argPos], umask, this);
        time.update();
        subDirectoryCount++;
      }  // if there are write permissions
      else // no write permissions
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             <<  "’: Permission denied\n";
    }  // if name not found
  }  // for each filename
}  // mkdir()


void Directory::showPath() const
{
  if (parent == NULL)
  {
    cout << "/";
    return;
  }  // at root
  
  parent->showPath();
  cout << name << "/";
}  // showPath())


bool Directory::operator== (const Directory &rhs) const
{
  return strcmp(name, rhs.name) == 0;
}  // operator==


ostream& operator<< (ostream &os, Directory const &rhs)
{
  os << rhs.name << ' ' << rhs.time << ' ' << ' '
     << rhs.subDirectoryCount << rhs.permissions << endl;
  
  for (int i = 0; i < rhs.subDirectoryCount; i++)
    os << *rhs.subDirectories[i];
  return os;
}  // operator<<

istream& operator>> (istream &is, Directory &rhs)
{
  is >> rhs.name >> rhs.time >> rhs.subDirectoryCount >> rhs.permissions;
  is.ignore(10, '\n');
  
  for (int i = 0; i < rhs.subDirectoryCount; i++)
  {
    rhs.subDirectories += new Directory("Dummy", 0, &rhs);
    is >> *rhs.subDirectories[i];
  }  // for each subdirectory
  
  return is;
}  // operator>>

bool Directory::operator< (const Directory &rhs) const
{
  if (strcmp(name, rhs.name) < 0)
    return 1;
  
  if (strcmp(name, rhs.name) > 0)
    return 0;

  return 0;
} // bool directory
