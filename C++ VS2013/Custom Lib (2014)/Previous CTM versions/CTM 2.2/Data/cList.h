#ifndef LIST_H
#define LIST_H

#include "../Base/Base.h"
#include "cHeapAllocator.h"

namespace ctm
{

//////////////////////////
//Node class
template<class type>
class node
{
	template<class type> friend class iterator;
	template<class type> friend class list;
public:
	node();
private:
	type *data; //Data
	node<type> *next; //Pointer to next node
	node<type> *previous; //Pointer to previous node
};

//Constructor
template<class type> node<type>::node():
data(0),
next(0),
previous(0)
{}
//////////////////////////

//////////////////////////
//Iterator class
template<class type>
class iterator
{
	template<class type> friend class list;
	template<class type> friend inline bool operator==(const iterator<type> &lhs, const iterator<type> &rhs);
	template<class type> friend inline bool operator!=(const iterator<type> &lhs, const iterator<type> &rhs);
public:
	iterator();
	iterator<type> operator++(); //Operator ++ (Prefix)
	iterator<type> operator--(); //Operator -- (Prefix)
	iterator<type> operator++(int); //Operator ++ (Postfix)
	iterator<type> operator--(int); //Operator -- (Postfix)
	type& operator*(); //Operator *
	type* operator->(); //Operator ->
private:
	node<type> *current;
};

//Constructor
template<class type> iterator<type>::iterator():
current(0)
{}

//Operator ==
template<class type> inline bool operator==(const iterator<type> &lhs, const iterator<type> &rhs)
{
	if(lhs.current == rhs.current)
		return true;
	else
		return false;
}

//Operator !=
template<class type> inline bool operator!=(const iterator<type> &lhs, const iterator<type> &rhs)
{
	return !operator==(lhs,rhs);
}

//Operator ++ (Prefix)
template<class type> iterator<type> iterator<type>::operator++()
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(current->next == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cList - Failed to increment iterator! Next node does not exist!\n",true);
			assert(0);
		}
	#endif
	current = current->next;
	return *this;
}

//Operator -- (Prefix)
template<class type> iterator<type> iterator<type>::operator--()
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(current->previous == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cList - Failed to decrement iterator! Previous node does not exist!\n",true);
			assert(0);
		}
	#endif
	current = current->previous;
	return *this;
}

//Operator ++ (Postfix)
template<class type> iterator<type> iterator<type>::operator++(int)
{
	iterator<type> temp = *this;
	++*this;
	return temp;
}

//Operator -- (Postfix)
template<class type> iterator<type> iterator<type>::operator--(int)
{
	iterator<type> temp = *this;
	--*this;
	return temp;
}

//Operator *
template<class type> type& iterator<type>::operator*()
{
	return *current->data;
}

//Operator ->
template<class type> type* iterator<type>::operator->()
{
	return current->data;
}
//////////////////////////

//////////////////////////
//Linked list class
template<class type>
class list
{
public:
	//System
		list();
		list(list<type> &rhs);
		~list();
		list<type> &operator=(list<type> &rhs);
	//Iteration
		iterator<type> get_head() { iterator<type> iter; iter.current = head; return iter; } //Returns the head node
		iterator<type> get_tail() { iterator<type> iter; iter.current = tail; return iter; } //Returns the tail node
		iterator<type> get_start() { iterator<type> iter; iter.current = head->next; return iter; } //Returns the node following the head
		iterator<type> get_end() { iterator<type> iter; iter.current = tail->previous; return iter; } //Returns the node preceding the tail
	//Data
		void clear(); //Clears the list
		void insert(iterator<type> iter, type nElement); //Inserts an element after a node
		void erase(iterator<type> iter); //Erases an element
		void push_front(type nElement); //Inserts an element after the head
		void pop_front(); //Erases an element after the head
		void push_back(type nElement); //Inserts an element before the tail
		void pop_back(); //Erases an element before the tail
		UINT32 get_size() { return size; }
private:
	node<type> *head; //Pointer to head node
	node<type> *tail; //Pointer to tail node
	UINT32 size; //Amount of nodes
};

//Constructor
template<class type> list<type>::list():
head(0),
tail(0),
size(0)
{
	head = new node<type>; //Allocate head
	tail = new node<type>; //Allocate tail
	head->next = tail; //Link head to tail
	tail->previous = head; //Link tail to head
}

//Copy constructor
template<class type> list<type>::list(list<type> &rhs):
head(0),
tail(0),
size(rhs.size)
{
	head = new node<type>; //Allocate head
	tail = new node<type>; //Allocate tail
	head->next = tail; //Link head to tail
	tail->previous = head; //Link tail to head

	//Copy nodes
	for(iterator<type> iter = rhs.get_start(); iter != rhs.get_tail(); ++iter)
	{
		push_back(*iter);
	}
}

//Destructor
template<class type> list<type>::~list()
{
	clear(); //Clear list
	delete head; //Deallocate head
	head = 0;
	delete tail; //Deallocate tail
	tail = 0;
}

//Operator =
template<class type> list<type> &list<type>::operator=(list<type> &rhs)
{
	head = 0;
	tail = 0;
	size = rhs.size;

	head = new node<type>; //Allocate head
	tail = new node<type>; //Allocate tail
	head->next = tail; //Link head to tail
	tail->previous = head; //Link tail to head

	//Copy nodes
	for(iterator<type> iter = rhs.get_start(); iter != rhs.get_tail(); ++iter)
	{
		push_back(*iter);
	}
	return *this;
}

//Clear
template<class type> void list<type>::clear()
{
	iterator<type> iter = get_start();
	while(iter != get_tail())
	{	
		erase(iter++);
	}
}

//Insert
template<class type> void list<type>::insert(iterator<type> iter, type nElement)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
		if(iter == get_tail())
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cList - Cannot insert nodes after tail!\n",true);
			assert(0);
		}
	#endif

	node<type> *newnode = new node<type>; //Allocate new node
	newnode->data = new type(nElement); //Allocate node data
	newnode->previous = iter.current; //Link new node to previous node
	newnode->next = iter.current->next; //Link new node to next node
	newnode->previous->next = newnode; //Link previous node to new node
	newnode->next->previous = newnode; //Link next node to new node
	++size; //Update size
}

//Erase
template<class type> void list<type>::erase(iterator<type> iter)
{
	#ifdef CUSTOMLIB_DEBUG_FATAL
	if(iter == get_head())
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cList - Failed to erase element! Cannot erase head!\n",true);
		assert(0);
	}
	if(iter == get_tail())
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cList - Failed to erase element! Cannot erase tail!",true);
		assert(0);
	}
	#endif

	iter.current->previous->next = iter.current->next; //Link previous node to node after target
	iter.current->next->previous = iter.current->previous; //Link next node to node before target
	delete iter.current->data; //Deallocate data of target node
	delete iter.current; //Delete target node
	--size; //Update size
}

//Push front
template<class type> void list<type>::push_front(type nElement)
{
	insert(get_head(),nElement);
}

//Pop front
template<class type> void list<type>::pop_front()
{
	erase(get_start());
}

//Push back
template<class type> void list<type>::push_back(type nElement)
{
	insert(get_end(),nElement);
}

//Pop back
template<class type> void list<type>::pop_back()
{
	erase(get_end());
}
//////////////////////////

}

#endif