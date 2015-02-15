#ifndef LIST_H
#define	LIST_H

using namespace std;

class Directory;
class LinkedList;
class ListNode
{
  Directory *data;
  ListNode *next;
  ListNode(Directory *d, ListNode *n) : data(d), next(n){}
  friend class LinkedList;    
};  // class ListNode

class LinkedList
{
  ListNode *head;
public:
  LinkedList(ListNode *h);
  ~LinkedList();
  LinkedList& operator+= (Directory* data);
};
#endif	// LIST_H

