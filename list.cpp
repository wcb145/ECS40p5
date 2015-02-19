#include <iostream>
#include "directory.h"
#include "list.h"

using namespace std;

ListNode::ListNode(Directory *d, ListNode *n) : data(d), next(n)
{

} // ListNode constructor

ListNode::~ListNode()
{
  delete data; //delete the directory
} // Destructor

List::List()
{
  head = NULL;
} // List constructor

List::List(const List& newList)
{

} // List copy constructor

List::~List()
{
  ListNode* prev = head;
  ListNode* ptr;
  
  while (prev) 
  {
    ptr = prev->next;
    delete prev;
    prev = ptr;
  } // while()
  
  head = 0;
} // List destructor!

void List::operator+= (Directory* data)
{
  ListNode *ptr = head, *prev = NULL;
  
  while (ptr && *ptr->data < *data)
  {
    prev = ptr;
    ptr = ptr->next;    
  } // prev == NULL
  
  if (!prev)
    head = new ListNode(data, head);
  else // prev != NULL
    prev->next = new ListNode(data, ptr);
}  // operator+=

const Directory* List::operator[] (int index)const
{
  ListNode *temp;
  temp = head;
  
  for (int i = 0; i < index; i++)
    temp = temp->next;
  
  return temp->data;   
} // const [] operator

Directory* List::operator[] (int index)
{
  ListNode *temp;
  temp = head;
  
  for (int i = 0; i < index; i++)
    temp = temp->next;
  
  return temp->data;   
} // non-const [] operator