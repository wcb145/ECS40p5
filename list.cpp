#include <iostream>
<<<<<<< HEAD
#include "directory.h"
#include "list.h"

using namespace std;

LinkedList::LinkedList(ListNode *h) : head(h)
{

} // LinkedList constructor

LinkedList::~LinkedList()
{

} // LinkedList destructor!

LinkedList& LinkedList::operator+= (Directory* data)
{
  ListNode *ptr = head, *prev = NULL;
  
  while (ptr && ptr->data < data)
  {
    prev = ptr;
    ptr = ptr->next;    
  } // prev == NULL
  
  if (!prev)
    head = new ListNode(data, head);
  else // prev != NULL
    prev->next = new ListNode(data, ptr);
}  // operator+=

=======
#include "list.h"

ListNode::ListNode(Directory* dat, ListNode* n)
{
  data= dat;
  next= n;
}

Directory* LinkedList::operator[] (int index) const
{
  ListNode *temp;
  temp = head;
  
  for (int i = 0; i < index; i++)
    temp = temp->next;
  
  return temp->data;   
} // operator

 void LinkedList::operator+= (Directory *rhs)
 {
   ListNode *ptr = head;
   ListNode *prev = NULL;
   
   while ( ptr && ptr->data < rhs)
   {
     prev = ptr;
     ptr= ptr->next;
   }
   
   if (!prev)
     head = new ListNode(rhs, head);
   else //else
     prev->next=new ListNode(rhs, ptr);
 
 }// sorted insert
 
LinkedList::~LinkedList()
{
  ListNode* prev = head;

  while( !prev ) 
  {
    ListNode* ptr = prev->next;
    delete prev;
    prev = ptr;
  }
  head = 0;
} // destructor linkedList

LinkedList::LinkedList()
{
  head = NULL; 
} // constructor
>>>>>>> 04220860a9b0126f6d60a3eca309455a7db2701c
