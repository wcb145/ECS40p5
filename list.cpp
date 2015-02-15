#include <iostream>
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