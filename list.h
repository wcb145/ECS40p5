#ifndef LIST_H
#define	LIST_H

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

