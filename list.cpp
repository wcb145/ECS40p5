#include <iostream>
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

