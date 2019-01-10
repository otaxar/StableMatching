//============================================================================
// Name        : Deque.cpp
// Author      : Otakar Valek
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Deque implementation
//	The class should implement the following public methods:
//	- Deque()						- Construct an empty deque.
//	- Deque(const Deque&) 			- Construct a deep copy of its constant Deque reference parameter.
//	- ~Deque()						- Deallocate dynamic memory allocated by the deque.
//	- Deque& operator=(const Deque&)- Copy (deeply) the constant Deque reference parameter into the target object
//									    and returns a reference to the target after de-allocating any dynamic memory
//									    associated with the original contents of the target.
//  								    If the target is the same as the parameter (the source)
//										the operator should have no effect.
//	- void insert_front(int)		- Insert its parameter at the front of the deque;
//										must run in constant (O(1)) time.
//	- void insert_back(int)			- Insert its parameter at the back of the deque;
//										must run in constant (O(1)) time.
//	- void int remove_front()		- Remove and return the value at the front of the deque;
//									    if the deque is empty throw a runtime_error
//									    (this error class is defined in the stdexcept library file);
//										must run in constant (O(1)) time.
//	- void int remove_back()		- Remove and return the value at the back of the deque;
//										if the deque is empty throw a runtime_error;
//									    must run in linear (O(n)) time.
//	- int peek_front() const		- Return the value at the front of the deque
//									    without removing it; if the deque is empty throw a runtime_error;
//									    must run in constant (O(1)) time.
//	- int peek_back() const			- Return the value at the back of the deque without removing it;
//										if the deque is empty throw a runtime_error;
//									    must run in constant (O(1)) time.
//	- bool empty() const			- Return true if the deque is empty, false otherwise.
//	- int size() const				- Return the number of items stored in the deque.
//============================================================================

#include "Deque.h"

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

//-----------------------------------------------------------------------------
// PRE:		N/A
// POST:	Creates empty Deque
// PARAM:	N/A
Deque::Deque():head{nullptr}, tail{nullptr}, node_ct{0} {
}


//-----------------------------------------------------------------------------
// PRE:		N/A
// POST:	New Deque created. If param Deque Nodes > 0, deep copy the Nodes
// PARAM:	srcDeq = source Deque to be copied
Deque::Deque(const Deque &srcDeq):head{nullptr}, tail{nullptr}, node_ct{0}{

	if ( srcDeq.head == nullptr ){			// if source deque is empty, leave new deque empty
		return;
	}

	Node *curr = srcDeq.head;

	while ( curr != nullptr ){					// loop thru the source and deep copy nodes to the new deque
		this->insert_back(curr->data);
		curr = curr->next_node;
	}
}


//-----------------------------------------------------------------------------
// POST:	All dynamic memory associated with object deallocated
Deque::~Deque(){
	clear();
}


//-----------------------------------------------------------------------------
// PRE:		target Deque != source Deque
// POST:	target Deque is cleared, Nodes from source Deque are deep copied to target.
// PARAM:	srcDeque = Deque to be deep copied
Deque& Deque::operator= (const Deque& srcDeq){

	if ( this != &srcDeq ){			// Only proceed if the src & target are NOT the same Deq instance

		this->clear();								// clear target

		if ( srcDeq.head != nullptr ){				// if src NOT empty

			Node *curr = srcDeq.head;

			while ( curr != nullptr ){				//
				this->insert_back(curr->data);		// just being lazy to implement more efficient deep_copy
				curr = curr->next_node;
			}
		}
	}

	return *this;
}


//-----------------------------------------------------------------------------
// PRE:		N/A
// POST:	int value inserted to the front of Deque. Node counter is incremented.
// PARAM:	val = integer value to be inserted to the Deque.
void Deque::insert_front(int val){

	// if list is empty
	if ( head == nullptr ){

		head = tail = new Node(val);	// create 1st node and point head and tail to it
	}
	else{
		Node *node = new Node(val);		// create new node in the front of the list
		node->next_node = head;			// update the pointers
		head = node;
	}
	node_ct++;
}


//-----------------------------------------------------------------------------
// PRE:		N/A
// POST:	New Node (with int value) added to the front of Deque. Node counter is incremented.
// PARAM:	val = integer value to be stored in new Node.
void Deque::insert_back(int val){

	// if list is empty
	if ( head == nullptr ){
		head = tail = new Node(val);	// add 1st node to the list and point head and tail to it
	}
	else{
		tail->next_node = new Node(val);	// append new node to tail
		tail = tail->next_node;			// update pointer
	}
	node_ct++;
}


//-----------------------------------------------------------------------------
// POST:	Node value returned, Node removed from the front of Deque.
//			Node counter is decremented.
int Deque::remove_front(){

	if ( head == nullptr ){
		throw std::runtime_error ("Unable to remove_front(), Deque is empty");
	}

	int val = head->data;					// get the data to be returned

	Node *del = head;						// delete the front node
	
	if ( head == tail )
		head = tail = nullptr;
	else
		head = del->next_node;

	delete del;									//
	node_ct--;

	return val;
}


//-----------------------------------------------------------------------------
// POST:	Node value returned, Node removed from the back of Deque.
//			Node counter is decremented.
int Deque::remove_back(){

	if ( tail == nullptr ){
		throw std::runtime_error ("Unable to remove_back(), Deque is empty");
	}

	int val = tail->data;					// get the data to be returned

	Node *del = tail;						//

	if (head == tail){					// If this is the only node in the list
		head = tail = nullptr;
	}
	else{
		Node *prev = head;					//

		while ( prev->next_node != tail ){	// traverse the list to find the previous node
			prev = prev->next_node;				// before the last one
		}

		tail = prev;						// update tail pointer
		tail->next_node = nullptr;			//
	}
	delete del;
	node_ct--;

	return val;
}


//-----------------------------------------------------------------------------
// PRE:		Deque NOT empty
// POST:	Value from the front Node returned.
int Deque::peek_front(){

	if ( head == nullptr ){
		throw std::runtime_error ("Unable to peek_front(), Deque is empty");
	}
	return head->data;
}

//-----------------------------------------------------------------------------
// PRE:		Deque NOT empty
// POST:	Value from the back Node returned.
int Deque::peek_back(){

	if ( tail == nullptr ){
		throw std::runtime_error ("Unable to peek_back(), Deque is empty");
	}
	return tail->data;
}


//-----------------------------------------------------------------------------
// POST:	If Deque is empty, true is returned
bool Deque::empty(){

	if ( head == nullptr && tail == nullptr )
		return true;
	else
		return false;

}

//-----------------------------------------------------------------------------
// POST:	Number of Nodes in the Deque is returned.
int Deque::size(){
	return node_ct;
}


// ======= HELPER FNS.

// ----------------------------------------------------------------------------
// POST:	All Nodes from the Deque are removed. Pointers and Nodes counter are reset.
void Deque::clear(){
	Node *del = head;

	while ( del != nullptr ){				// loop thru the list and delete nodes
		head = head->next_node;
		delete del;
		del = head;
	}

	node_ct = 0;
	head = tail = nullptr;
}

void Deque::printDeque(){
	if ( empty() ){
		cout << "deque is empty" << endl;
	}else{
		Node *prt = head;

		while (prt != nullptr){
			if( prt->next_node != nullptr )
				cout << prt->data << ", ";
			else
				cout << prt->data;
			prt = prt->next_node;
		}
	}
}



