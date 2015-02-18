// Author: Sean Davis

#include <iostream>
#include "permissions.h"
using namespace std;

short Permissions::umask = 022;

void Permissions::setUmask(short input)
{
  if (input)
    umask = input;
} // setUmask

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
