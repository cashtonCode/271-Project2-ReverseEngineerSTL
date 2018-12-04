/*
Author: Cashton Christensen
Project_2
Due 2-21-2018
*/

#include <iostream>
using namespace std;

template <class A>
class iter;
template <class A>
class list;

template <class A>
class Node
{
  friend class iter<A>;
private:
  A myItem;
  Node<A>* next;
  Node<A>* prev;

public:
  Node();                     //constructor
  Node(A, Node<A>*, Node<A>*);//parameter constructor
  A getItem();                //getter for Item
  Node<A>* getNext();         //getter for pointer
  Node<A>* getPrev();         //getter for pointer
  void setItem(A);            //setter for Item
  void setNext(Node<A>*);     //setter for pointer
  void setPrev(Node<A>*);     //setter for pointer
};

/*******************************************************************************
node Class Functions
********************************************************************************
  /***************************************************************************
                    **CONSTRUCTOR**
  *Input: Noneint i = 0;
  *Output: None
  *Description: sets the pointer to NULL
  ***************************************************************************/
  template<class A>
  Node<A>::Node(){
    next = NULL;
    prev = NULL;
  }
  /***************************************************************************
                    **PARAMETER CONSTRUCTOR **
  *Input: None
  *Output: None
  *Description: sets the 2 objects(pointer and object of type A) within the
  class equal to the parameters of the function
  template<class A>
  ***************************************************************************/
  template<class A>
  Node<A>::Node(A newItem, Node<A>* prevNode, Node<A>* nextNode){
    next = nextNode;
    prev = prevNode;
    myItem = newItem;
  }
  /***************************************************************************
                    **GETItem FUNCTION **
  *Input: None
  *Output: object of type A
  *Description: returns myItem object from within class
  ***************************************************************************/
  template<class A>
  A Node<A>::getItem(){return myItem;}
  /***************************************************************************
                    **GETNEXT FUNCTION **
  *Input: None
  *Output: pointer of templated Node class
  *Description: returns the pointer next
  ***************************************************************************/
  template<class A>
  Node<A>* Node<A>::getNext(){return next;}
  /***************************************************************************
                    **GETPrev FUNCTION **
  *Input: None
  *Output: pointer of templated Node class
  *Description: returns the pointer prev
  ***************************************************************************/
  template<class A>
  Node<A>* Node<A>::getPrev(){return prev;}
  /***************************************************************************
                    **SETItem FUNCTION **
  *Input: object of type A
  *Output: None
  *Description: sets MyItem equal to the parameter within the function
  ***************************************************************************/
  template<class A>
  void Node<A>::setItem(A newItem){myItem = newItem;}
  /***************************************************************************
                    **SETNEXT FUNCTION **
  *Input: Pointer of templated class Node
  *Output: None
  *Description: sets the pointer next equal to the parameter within the function
  ***************************************************************************/
  template<class A>
  void Node<A>::setNext(Node<A>* arg_next){next = arg_next;}
  /***************************************************************************
                    **SETPREV FUNCTION **
  *Input: Pointer of templated class Node
  *Output: None
  *Description: sets the pointer previous equal to the parameter within the function
  ***************************************************************************/
  template<class A>
  void Node<A>::setPrev(Node<A>* arg_prev){prev = arg_prev;}
/******************************************************************************/

template <class A>
class iter
{
public:
  friend class list<A>;
  Node<A>* cursor;

  iter<A> operator++();     //Prefix-Increment
  iter<A> operator++(int);  //Postfix-Increment
  iter<A> operator--();     //Prefix-Decrament
  iter<A> operator--(int);  //Postfix-Decrament
  bool operator==(const iter<A>& rhs) const;
  bool operator!=(const iter<A>& rhs) const;
  A operator*();
  Node<A>* operator=(Node<A>*); //Assignment operator
};

/*******************************************************************************
iter Class Functions - Operator Overloads
*******************************************************************************/
    template<class A>//Prefix-Increment
    iter<A> iter<A>::operator++(){
      cursor = cursor->getNext();
      return *this;
    }
    template<class A>//Postfix-Increment
    iter<A> iter<A>::operator++(int){
      Node<A>* previous = cursor;
      cursor = cursor->getNext();
      iter<A> temp;
      temp.cursor = previous;
      return temp;
    }
    template<class A>//Prefix-Decrament
    iter<A> iter<A>::operator--(){
      cursor = cursor->getPrev();
      return *this;
    }
    template<class A>//Postfix-Decrament
    iter<A> iter<A>::operator--(int){
      Node<A>* previous = cursor;
      cursor = cursor->getPrev();
      iter<A> temp;
      temp.cursor = previous;
      return temp;
    }
    template<class A>
    bool iter<A>::operator==(const iter<A>& rhs) const {
      return (cursor == rhs.cursor);
    }
    template<class A>
    bool iter<A>::operator!=(const iter<A>& rhs) const {
      return !(cursor == rhs.cursor);
    }
    template<class A>
    A iter<A>::operator*(){
      return cursor->getItem();
    }
    template<class A>
    Node<A>* iter<A>::operator=(Node<A>* rhs){
      cursor = rhs;
      return cursor;
    }
/*******************************************************************************/

template <class A>
class list
{
private:
  int count;
  Node<A>* head;
  Node<A>* tail;

public:
  list();
  list(const list<A>&);
  ~list();
  bool empty();
  int size();
  void clear();
  void push_back(A item);
  void push_front (A item);
  A pop_back();
  A pop_front();
  void erase(iter<A>); 	       //removes the item iterator indicates from the list
  iter<A> begin(); 	           //returns an iterator to the first item in the list
  iter<A> end(); 	             //returns an iterator to after the last item in the list
  A front(); 	                 //returns a reference to the first item in the list
  A back(); 	                 //returns a reference to the last item in the list
};

/*******************************************************************************
List Class Functions
*******************************************************************************/
  template<class A>
  list<A>::list(){
    head = new Node<A>();
    tail = new Node<A>();
    head->setNext(tail);
    tail->setPrev(head);
    head->setPrev(head);
    tail->setNext(tail);
  	count = 0;
  }
  /*************************************************************************
  Class list
  Function:  Copy Constructor
         Creates a linked list identical to one inputted
         allows you to do list A(B) so that you create A as a copy of B.
         This is a little involved as it is NOT just copying the values of the head pointers.
  ************************************************************************/
  template<class A>
  list<A>::list(const list<A>& original){
    head = new Node<A>();
    tail = new Node<A>();
    head->setNext(tail);
    tail->setPrev(head);
    head->setPrev(head);
    tail->setNext(tail);
  	count = 0;

    /*
        IN HERE THE COPIED LIST IS ~~SOMEHOW~~ LINKED TO THE ORIGINAL LIST SO THAT
      WHEN THE COPIED LIST CHANGES THE NEW LIST ALSO CHANGES.
        IN MY VARIED ATTEMPTS TO GET AROUND THIS ISSUE I COULD NOT FIGURE OUT
      WHAT WAS CAUSING THE COPIED LIST TO BE CONNECTED TO THE ORIGINAL LIST.
        BY ALL MEANS IT MAKES NO SENSE TO ME.
    */

    Node<A>* temp = original.head;
    for(temp = temp->getNext(); temp != original.tail; temp = temp->getNext()){
      push_back(temp->getItem());
    }
  }
  /*************************************************************************
  Class list
  Function:  Deconstructor
        removes and deletes all the nodes (including head and tail nodes)
  ************************************************************************/
  template<class A>
  list<A>::~list(){
    clear();
    delete head;
    delete tail;
  }
  /*************************************************************************
  Class list
  Function:  empty
       Checks to see if linked list is empty
      This is indicated by headNodePtr->tailNodePtr
      Returns TRUE for empty
  ************************************************************************/
  template<class A>
  bool list<A>::empty(){
    if(count == 0) return true;
    else return false;
  }
  /**************************************************************************
   Class list
   Function:  size
   Parameters: None
    Returns an integer count of the number of items in the list
  ***************************************************************************/
  template<class A>
  int list<A>::size(){return count;}
  /*************************************************************************
   Class list
   Function:  Clear
           Take a list and delete all nodes but the DUMMY head and tail nodes
   ************************************************************************/
   template<class A>
   void list<A>::clear(){
     Node<A>* cursor = head->getNext();
     cursor = cursor->getNext();
     delete cursor->getPrev();
     while( (cursor->getNext() ) != tail){
       cursor = cursor->getNext();
       delete cursor->getPrev();
     }
     delete cursor;
   }
  /**************************************************************************
  Class list
  Function:  push_back
         Inserts a new item at the end of the list
         This routing will create a Node object to contain the item to add
  Parameters: item to add to the list
  Return: void
  ***************************************************************************/
  template<class A>
  void list<A>::push_back(A item){
    Node<A>* temp = new Node<A>(item, tail->getPrev(), tail->getNext());//NEW node placed between (end) and (end - 1)
    tail->setPrev(temp);
    Node<A>* temp1 = temp->getPrev();
    temp1->setNext(temp);
    count++;
  }
  /**************************************************************************
   Class list
   Function:  push_front
          Inserts a new item at the front of the list
          This routing will create a Node object to contain the item to add
   Parameters: item to add to the list
   Return: void
  *******************************************************************************/
  template<class A>
  void list<A>::push_front (A item){
    Node<A>* temp = new Node<A>(item, head->getPrev(), head->getNext());
    head->setNext(temp);
    Node<A>* temp1 = temp->getNext();
    temp1->setPrev(temp);
    count++;
  }
  /**************************************************************************
    Class list
    Function:  pop_back;
          Deletes an item from the back of the list
          This routing will return the value of the node at the end of the list
          Removes that node from the list
    Parameters: None
    Return: value of the last node
    Exception Returned: listIsEmpty if list is empty
  *******************************************************************************/
  template<class A>
  A list<A>::pop_back(){
    if(count == 0) cout << "Nothing to Pop" << endl;
    else{
      iter<A> tempiter = end();
      --tempiter;
      A tempitem = *tempiter;
      Node<A>* temp = tempiter.cursor;
      temp->getNext()->setPrev(temp->getPrev());//temp's next's prev = temp's prev
      temp->getPrev()->setNext(temp->getNext());//temp's prev's next = temp's next
      delete temp;
      return tempitem;
    }
  }
  /**************************************************************************
   Class list
   Function:  pop_front
          Deletes anitem from the front of the list
          This routing will return the value of the node at the top of the list
          Removes that node from the list
   Parameters: none
   Return: value of the first node
   Exception Returned: listIsEmpty if list is empty
  *******************************************************************************/
  template<class A>
  A list<A>::pop_front(){
    if(count == 0) cout << "Nothing to Pop" << endl;
    else{
      iter<A> tempiter = begin();
      A tempitem = *tempiter;
      Node<A>* temp = tempiter.cursor;
      temp->getNext()->setPrev(temp->getPrev());//temp's next's prev = temp's prev
      temp->getPrev()->setNext(temp->getNext());//temp's prev's next = temp's next
      delete temp;
      return tempitem;
    }
  }
  /*************************************************************************
  Class list
  Function:  Erase
         removes the item iterator indicates from the list
  ************************************************************************/
  template<class A>
  void list<A>::erase(iter<A> cur){
    if(count == 0 ) cout << "Nothing to Erase" << endl;
    else{
      Node<A>* temp;
      temp = cur.cursor;
      cur.cursor->getNext()->setPrev(cur.cursor->getPrev());//cursor's next's prev = cur's prev
      cur.cursor->getPrev()->setNext(cur.cursor->getNext());//cursor's prev's next = cur's next
      delete temp;
      count--;
    }
  }
  /*************************************************************************
   Class list
   Function:  Begin
           returns an iterator to the first item in the list
  *************************************************************************/
  template<class A>
  iter<A> list<A>::begin(){
    iter<A> nodeF;
    nodeF.cursor = head;
    nodeF++;
    return nodeF;
  }
  /*************************************************************************
  Class list
  Function:  End
         returns an iterator to after the last item in the list
  ************************************************************************/
  template<class A>
  iter<A> list<A>::end(){
    iter<A> nodeL;
    nodeL.cursor = tail;
    nodeL++;
    return nodeL;
  }
  /*************************************************************************
  Class list
  Function:  Front
         returns a reference to the first item in the list
  ************************************************************************/
  template<class A>
  A list<A>::front(){
      iter<A> temp = begin();
      return *temp;
  }
  /*************************************************************************
  Class list
  Function:  Back
         returns a reference to the last item in the list
  ************************************************************************/
  template<class A>
  A list<A>::back(){
    iter<A> temp = end();
    --temp;
    A tempitem = *temp;
    return tempitem;
  }
/******************************************************************************/
