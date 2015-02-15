#include <iostream>
#include "directory.h"
#include "list.h"

using namespace std;

ListNode::ListNode(Directory *d, ListNode *n) : data(d), next(n)
{

} // ListNode constructor

LinkedList::LinkedList()
{
  head = NULL;
} // LinkedList constructor

LinkedList::~LinkedList()
{
  ListNode* prev = head;

  while (!prev) 
  {
    ListNode* ptr = prev->next;
    delete prev;
    prev = ptr;
  } // while()
  
  head = 0;
} // LinkedList destructor!

void LinkedList::operator+= (Directory* data)
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

Directory* LinkedList::operator[] (int index) const
{
  ListNode *temp;
  temp = head;
  
  for (int i = 0; i < index; i++)
    temp = temp->next;
  
  return temp->data;   
} // operator

