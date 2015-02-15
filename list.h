#ifndef LIST_H
#define	LIST_H

<<<<<<< HEAD
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
=======
class Directory;

class ListNode
{
    Directory *data;
    ListNode *next;
    ListNode (Directory *dat, ListNode *n); // constructor
    friend class LinkedList;
}; // class listnod

class LinkedList
{
public:
    ListNode *head;
    LinkedList(); //constructor
   // LinkedList(const &LinkedList);//
    ~LinkedList(); 
    void operator+= (Directory *rhs);
    Directory* operator[] (int index) const;//
};

#endif	/* LIST_H */
>>>>>>> 04220860a9b0126f6d60a3eca309455a7db2701c

