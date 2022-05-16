/*
 * Tree.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef TREE_H_
#define TREE_H_
#include <iostream>
#include "Node.h"
using namespace std;

template<typename T>
class Tree{
private:
	Node<T>* head;
//maybe we need int counter;
	Node<T>* removeR(T& node,Node<T>* head);
	void insertR(T* node,Node<T>* head);
	Node<T>* searchR(T& node,Node<T>* head);
	void printR(Node<T>* head);
	Node<T>* minR(Node<T>* head);
	Node<T>* maxR(Node<T>* head);
	Node<T>* successor(Node<T>* head){
		Node<T>* temp=minR(head->getRight());
		return temp;
	}
	Node<T>* searchByIntR(int x,Node<T>* head);
public:
	Tree():head(0){}
	~Tree(){delete head;head=0;}
	Node<T>* getHead(){return head;}
	void remove(T& node);//int place);
	void clear(){head=0;}
	void insert(T* node);
	Node<T>* search(T& node);
	Node<T>* min();
	Node<T>* max();
	void print();
	Node<T>* searchByInt(int x);
};
#include "Tree_code.h"

#endif /* TREE_H_ */
