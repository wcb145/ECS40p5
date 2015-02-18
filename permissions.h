#ifndef PERMISSIONS_H
  #define PERMISSIONS_H

#include <iostream>
using namespace std;

const int EXECUTE_PERMISSIONS = 1;
const int READ_PERMISSIONS = 4;
const int WRITE_PERMISSIONS = 2;

class Permissions 
{
  static short umask;
  short permissions;
public:
  bool isPermitted(short testedPermission) const;
  void set(short originalPermissions, short umask);
  void print() const;
  void chmod(short newPerm);
  static void setUmask (short newUmask);
  static short getUmask ();
  friend ostream& operator<< (ostream &os, const Permissions &permissions);
  friend istream& operator>> (istream &is, Permissions &permissions);
};  // class Permissions;
#endif  // PERMISSIONS_H

