#ifndef LIST_H
#define	LIST_H

using namespace std;

class Directory;
class LinkedList;
class ListNode
{
  Directory *data;
  ListNode *next;
  ~ListNode();
  ListNode(Directory *d, ListNode *n);
  friend class LinkedList;    
};  // class ListNode

class LinkedList
{
  ListNode *head;
public:
  LinkedList();
  ~LinkedList();
  void operator+= (Directory* data);
  Directory* operator[] (int index) const;
  Directory* operator[] (int index);
};
#endif	// LIST_H

