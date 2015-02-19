// Author: Sean Davis

#include <iostream>
#include "permissions.h"
#include <cstring>
using namespace std;

short Permissions::umask = 022;

void Permissions::putUmask(short input)
{
  if (input)
    umask = input;
} // putUmask


void Permissions::setUmask(int argCount, const char *arguments[])
  // checks "umask" command and executes it if it is proper
{
  short umask = getUmask();
  short newUmask = 0;
  
  if (argCount == 1)
  {
    cout << oct << umask << dec << endl;
    return;
  }  // if only "umask" on commandline
  
  if (argCount != 2)
  {
    cout << "umask: Too many arguments.\n";
    return;
  }  // if more than 2 arguments
  
  
  if (strlen(arguments[1]) > 3)
  {
    cout << "umask: Improper mask.\n";
    return;
  }  // if umask value too long.
  
  for (int i = 0; arguments[1][i] != '\0'; i++ )
  {
    if (arguments[1][i] < '0' || arguments[1][i] > '7')
    {
      cout << "umask: Improper mask.\n";
      return;
    }  // if incorrect octal
    else  // valid octal digit
      newUmask = newUmask * 8 + arguments[1][i] - '0';
  }   // for each digit in argument
  
  putUmask(newUmask);
}  // umask()

short Permissions::getUmask()
{
  return umask;
} // getUmask()

void Permissions::chmod(short newPerm)
{
  permissions = newPerm;
} // chmod()

bool Permissions::isPermitted(short testedPermission) const
{
  return ((permissions  >> 6) & testedPermission) == testedPermission;
}  // isPermitted()


void Permissions::set(short originalPermissions, short umask)
{
  permissions = originalPermissions & ~umask;
}  // set())

short Permissions::checkOctals(const char *octals)
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

void Permissions::print() const
{
  for (int i = 6; i >= 0 ; i -= 3)
  {
    if ((permissions >> i) & 4)
      cout << "r";
    else  // no read permissions
      cout << "-";

    if ((permissions >> i) & 2)
      cout << "w";
    else  // no write permissions
      cout << "-";

    if ((permissions >> i) & 1)
      cout << "x";
    else  // no execute permissions
      cout << "-";
  }  // for each set of rwx permissions
}  // print()


ostream& operator<< (ostream &os, const Permissions &permissions)
{
  os << permissions.permissions;
  return os;
}  // operator<<


istream& operator>> (istream &is, Permissions &permissions)
{
  is >> permissions.permissions;
  return is;
}  // operator>>
