#ifndef LIST_H
#define	LIST_H

using namespace std;

class Directory;
class List;
class ListNode
{
  Directory *data;
  ListNode *next;
  ~ListNode();
  ListNode(Directory *d, ListNode *n);
  friend class List;    
};  // class ListNode

class List
{
  ListNode *head;
public:
  List();
  List(const List& newHead);
  ~List();
  void operator+= (Directory* data);
  const Directory* operator[] (int index)const;
  Directory* operator[] (int index);
}; // list class
#endif	// LIST_H

