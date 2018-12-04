#include <cstddef>
#include <iostream>
using namespace std;

/*******************************************************************************
          LIST FUNCTIONS
constructor 	          Create the list.  You will probably want head and tail nodes and pointers.
copy constructor 	      allows you to do List A(B) so that you create A as a copy of B.  This is a little involved as it is NOT just copying the values of the head pointers.
destructor 	            removes and deletes all the nodes (including head an tail nodes)
bool empty() 	          true if there are no values in the list
int size() 	            returns the number of values in the list
void clear() 	          removes all items from the list
void push_back(value) 	insert value at the end
void push_front(value) 	insert value at the beginning
void pop_front() 	      removes the first value in the list
void pop_back() 	      removes the last value in the list
iter begin() 	          returns an iterator to the first item in the list
iter end() 	            returns an iterator to after the last item in the list
          Overload
operator = 	            Copies one linked list into another (requires creating a new set of nodes)
********************************************************************************
          ITERATOR FUNCTIONS
Type front() 	          returns a reference to the first item in the list
Type back() 	          returns a reference to the last item in the list
void erase(iter) 	      removes the item iterator indicates from the list
          Overload
++iter 	                move iterator to the next and return the modified value of the iterator
iter++ 	                move iterator to the next and returns the original value of the iterator
iter--, --iter 	        move iterator to the previous, post and pre.
*iter 	                return the value in the node pointed to by the iterator
iter == iter and
iter != iter 	          return true or false based on iterator comparison.
*******************************************************************************/
template <class A>
class Node;
template <class A>
class List;
template <class A>
class iter;

template <class A>
class Node
{
private:
  A myItem;
  Node* next;
  Node* prev;

public:
  Node();               //constructor
  Node(A, Node*);       //parameter constructor
  A getItem();          //getter for Item
  Node* getNext();      //getter for pointer
  Node* getPrev();      //getter for pointer
  void setItem(A);      //setter for Item
  void setNext(Node*);  //setter for pointer
  void setPrev(Node*);  //setter for pointer
};

template <class A>
class List
{
private:
  int count;
  Node<A>* headNodePtr;
  Node<A>* tailNodePtr;

public:
  List();
  //copy constructor 	      allows you to do List A(B) so that you create A as a copy of B.  This is a little involved as it is NOT just copying the values of the head pointers.
  List(const List<A>&);
  ~List();
  bool empty();
  int size();
  //void clear() 	          removes all items from the list
  void push_back(A item);
  void push_front (A item);
  A pop_front();
  A pop_back();
  void print_all();
  void insert_in_order(A item);// - inserts item in its proper order in the linked list
  iter<A> begin(); 	             //returns an iterator to the first item in the list
  iter<A> end(); 	               //returns an iterator to after the last item in the list

  static const int ItemNotFound = 8001;
	static const int IndexOutOfBoundsException = 8002;
	static const int ListIsEmpty = 8003;
};

template <class A>
class iter
{
private:
  Node<A>* Cursor;

public:
  A front(); 	              //returns a reference to the first item in the list
  A back(); 	              //returns a reference to the last item in the list
  void erase(iter); 	      //removes the item iterator indicates from the list

  iter<A> operator++();     //Pre-Increment
  iter<A> operator++(int);  //Post-Increment
  bool operator==(const iter<A>& rhs) const;
  bool operator!=(const iter<A>& rhs) const;

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
  Node<A>::Node(A newItem, Node<A>* newNode){
    next = newNode;
    prev = NULL;
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
                    **SETItem FUNCTION **
  *Input: object of type A
  *Output: None
  *Description: sets MyItem equal to the parameter within the function
  ***************************************************************************/
  template<class A>
  void Node<A>::setItem(A newItem){myItem = newItem;}
  /***************************************************************************
                    **GETNEXT FUNCTION **
  *Input: None
  *Output: pointer of templated Node class
  *Description: returns the pointer next
  ***************************************************************************/
  template<class A>
  Node<A>* Node<A>::getNext(){return next;}
  /***************************************************************************
                    **GETNEXT FUNCTION **
  *Input: None
  *Output: pointer of templated Node class
  *Description: returns the pointer next
  ***************************************************************************/
  template<class A>
  Node<A>* Node<A>::getPrev(){return prev;}
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

/**************************************************************************************************************************************************************************/
/*******************************************************************************
List Class Functions
*******************************************************************************/
    /*************************************************************************
     Class List
     Function:  Constructor
             Create am empty linked list
            This is indicated by a null pointer in the start of list (headNodePtr)
     ************************************************************************/
    template<class A>
    List<A>::List(){
      headNodePtr = new Node<A>();
      tailNodePtr = new Node<A>();
      headNodePtr->setNext(tailNodePtr);
      tailNodePtr->setPrev(headNodePtr);
      tailNodePtr->setNext(tailNodePtr);
    	count = 0;
    }
    /*************************************************************************
    Class List
    Function:  Copy Constructor
           Creates a linked list identical to one inputted
           allows you to do List A(B) so that you create A as a copy of B.
           This is a little involved as it is NOT just copying the values of the head pointers.
    ************************************************************************/
    template<class A>
    List<A>::List(const List<A>& original){
      headNodePtr = new Node<A>();
      tailNodePtr = new Node<A>();
      headNodePtr->setNext(tailNodePtr);
      tailNodePtr->setPrev(headNodePtr);
      tailNodePtr->setNext(tailNodePtr);


      //Node<A>* cur = original.headNodePtr->getNext(), *end = original.tailNodePtr->getPrev();
      iter<A> cur = begin(), end = end();
      while(cur != end){
        //push_back(cur->getItem());
        //cur->setNext(cur->getNext());
        ////cur++;
        cout << "t ";
      }
    }
    /*************************************************************************
    Class List
    Function:  Deconstructor
          removes and deletes all the nodes (including head and tail nodes)
    ************************************************************************/
    template<class A>
    List<A>::~List(){
      //DELETE ALL NODES SOMEHOW

    }
    /*************************************************************************
    Class List
    Function:  empty
         Checks to see if linked list is empty
        This is indicated by headNodePtr->tailNodePtr
        Returns TRUE for empty
    ************************************************************************/
    template<class A>
    bool List<A>::empty(){
      if(size()==0)return true;
      else return false;

    }
    /***************************************************************************
     Class List
     Function:  size
     Parameters: None
      Returns an integer count of the number of items in the list
    ***************************************************************************/
    template<class A>
    int List<A>::size()
    {
      return count;//CHECK INTO CHANGING B/C STL WORKS WEIRD!!!!!!!!!!!!!!!!!!!
    }
    /*************************************************************************
     Class List
     Function:  Clear
             Take a list and delete all nodes but the DUMMY head and tail nodes
     ************************************************************************/


    /***************************************************************************
    Class List
    Function:  push_back
           Inserts a new item at the end of the list
           This routing will create a Node object to contain the item to add
    Parameters: item to add to the list
    Return: void
    ***************************************************************************/
    template<class A>
    void List<A>::push_back(A item){
     Node<A>* temp = new Node<A>(item, NULL);
     Node<A>* p = headNodePtr;
     if(count==0)
     {
       headNodePtr = temp;
       count++;
       return;
     }
     for (int i = 0; i < (count-1); i++)
     {
       p = p -> getNext();
     }
     p -> setNext(temp);
     count++;
    }
    /***************************************************************************
     Class List
     Function:  push_front
            Inserts a new item at the front of the list
            This routing will create a Node object to contain the item to add
     Parameters: item to add to the list
     Return: void
    *******************************************************************************/
    template<class A>
    void List<A>::push_front (A item){
      Node<A>* newnode = new Node<A>(item, headNodePtr);
      headNodePtr = newnode;
      count++;
    }
    /***************************************************************************
     Class List
     Function:  pop_front
            Deletes anitem from the front of the list
            This routing will return the value of the node at the top of the list
            Removes that node from the list
     Parameters: none
     Return: value of the first node
     Exception Returned: ListIsEmpty if list is empty
    *******************************************************************************/
    template<class A>
    A List<A>::pop_front(){
      if(count==0)throw ListIsEmpty;

      Node<A>* newPtr = new Node<A>;
      int item;
      newPtr = headNodePtr->getNext();
      item = newPtr -> getItem();
      headNodePtr->setNext(newPtr->getNext());// = headNodePtr -> getNext();
      delete [] newPtr;
      count--;
      return item;
    }
    /***************************************************************************
      Class List
      Function:  pop_back;
            Deletes an item from the back of the list
            This routing will return the value of the node at the end of the list
            Removes that node from the list
      Parameters: None
      Return: value of the last node
      Exception Returned: ListIsEmpty if list is empty
    *******************************************************************************/
    template<class A>
    A List<A>::pop_back(){
      cout << "in function, count: " << count << endl;
      if(empty())throw ListIsEmpty;

      Node<A>* p = headNodePtr;
      Node<A>* prevPtr = NULL;

      for (int i = 0; i < (count-1); i++)
      {
        prevPtr = p;
        p = p -> getNext();
      }
      cout << "at end of list" << endl;
      int item = p -> getItem();
      delete [] p;
      count--;
      cout << "deleted node, count: " << count << endl;

      if(empty()){
        headNodePtr->setNext(tailNodePtr);
        tailNodePtr->setPrev(headNodePtr);
        tailNodePtr->setNext(tailNodePtr);
        return item;
      }
      prevPtr->setNext(tailNodePtr);
      cout << "set prevPtr to tailNodePtr" << endl;
      return item;

    }
    /***************************************************************************
     Class List
     Function:  printList
            Walks through the list looking for a node at the position passed.
            The position starts counting at 1. That is the first node in the list
            is at position 1.
            If that node is found, it removes the node from the list
            and returns the value.

            If the node is not found, signal an  exception: NodeAtPositionNotFound

     Parameters:  None
     Result:  List of item values is sent to the standard output device
     Return: Void
    *******************************************************************************/
    template<class A>
    void List<A>::print_all(){
      Node<A>* p;
      if(empty())return;
      for (p = headNodePtr; p != NULL; p = p->getNext())
      {
        cout << p -> getItem() << endl;//CHANGE FOR USE W/O COUT !!!!!!!!!!!!!!!
      }
    }
    /***************************************************************************
      Class List
      Function:  insert_in_order
              Insert an item in the list IN ORDER. That is, it is inserted after all
              integers that are smaller than it and before integers that are larger than it
      Note: be sure to explicitly hand the situation when the new node
            is added to the front of the list
      Parameters: item to add.
      Return: Void
     ******************************************************************************/
    template<class A>
    void List<A>::insert_in_order(A item)// - inserts item in its proper order in the linked list
    {
      Node<A>* newPtr = new Node<A>(item, NULL);
      Node<A>* prevPtr = NULL;
      Node<A>* currPtr = headNodePtr;
      //condition if stack is empty
      if(count==0)
      {
        headNodePtr = newPtr;
        count++;
        return;
      }

      //inserting at the top of list
      //headNodePtr equal to currPtr -> getItem()
      if(item < currPtr -> getItem())
      {
        newPtr -> setNext(headNodePtr);
        headNodePtr = newPtr;
        count++;
        return;
      }

      //loops through while parameter item is greater than currPtr item
      while((currPtr != NULL)&&(item >= currPtr -> getItem()))
      {
        prevPtr = currPtr;
        currPtr = currPtr -> getNext();
      }// while loop returns most current prevPtr and currPtr
      //puts newPtr between prevPtr and currPtr
      prevPtr -> setNext(newPtr);
      newPtr -> setNext(currPtr);
      count++;
    }
    /*************************************************************************
     Class iter
     Function:  Begin
             returns an iterator to the first item in the list
    *************************************************************************/
    template<class A>
    iter<A> List<A>::begin(){
      iter<A> nodeF;
      nodeF.Cursor = headNodePtr->getNext();
      return nodeF;
    }
    /*************************************************************************
    Class iter
    Function:  End
           returns an iterator to after the last item in the list
    ************************************************************************/
    template<class A>
    iter<A> List<A>::end(){
      iter<A> nodeL;
      nodeL.Cursor = tailNodePtr->getPrev();
      return nodeL;
    }
/******************************************************************************************************************************************************************************/
/*******************************************************************************
iter Class Functions
*******************************************************************************/
    /*************************************************************************
    Class iter
    Function:  Front
           returns a reference to the first item in the list
    ************************************************************************/
    template<class A>
    A iter<A>::front(){

    }
    /*************************************************************************
    Class iter
    Function:  Back
           returns a reference to the last item in the list
    ************************************************************************/
    template<class A>
    A iter<A>::back(){

    }
    /*************************************************************************
    Class iter
    Function:  Erase
           removes the item iterator indicates from the list
    ************************************************************************/
    template<class A>
    void iter<A>::erase(iter){

    }
/*******************************************************************************
********************************************************************************
*******************************************************************************/
/*******************************************************************************
Operator Overloads
*******************************************************************************/
//  https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421729#4421729
//  https://codereview.stackexchange.com/questions/74609/custom-iterator-for-a-linked-list-class

    template<class A>
    iter<A> iter<A>::operator++(){

    }
    template<class A>
    iter<A> operator++(int){

    }
    template<class A>
    bool iter<A>::operator==(const iter<A>& rhs) const {

    }
    template<class A>
    bool iter<A>::operator!=(const iter<A>& rhs) const {

    }
/*******************************************************************************
********************************************************************************
*******************************************************************************/
