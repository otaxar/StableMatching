// Name        : Deque.cpp
// Author      : Otakar Valek
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Deque implementation    Author: otakar

#ifndef DEQUE_H_
#define DEQUE_H_

//=============================================================================
class Node{

	friend class Deque;

	private:
		int data;
		Node *next_node;

	public:
		Node(): data(), next_node(nullptr){}
		Node(int val): data(val), next_node(nullptr) {}				// only this one gets used for now
		Node(int val, Node* next): data(val), next_node(next){}
};

//=============================================================================
class Deque{
	private:
		Node *head;
		Node *tail;
		int node_ct;

	public:
		Deque();
		Deque(const Deque&);
		~Deque();

		Deque& operator= (const Deque&);

		void insert_front(int);
		void insert_back (int);

		int remove_front();
		int remove_back();

		int peek_front();
		int peek_back();

		bool empty();
		int size();

		// helper functions
		void clear();
		void printDeque();
};


#endif /* DEQUE_H_ */
