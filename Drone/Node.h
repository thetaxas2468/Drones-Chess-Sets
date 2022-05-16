/*
 * Node.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
using namespace std;
template<typename T>
class Node{
private:
	Node<T>* left;
	Node<T>* right;
	T* data;
public:
//	Node():left(0),right(0),data(new T){}
//	Node(T* t):left(0),right(0){data=new T;*data=*t;}
	Node(T* t,Node<T> *left,Node<T> *right):left(left),right(right),data(t){}//*data=*t;}
	~Node(){delete left;delete right;delete data;}
	Node<T>* getRight(){return right;}
	void setRight(Node<T> *node){right=node;}
	void setLeft(Node<T> *node){left=node;}
	Node<T>* getLeft(){return left;}
	T* getData(){return data;}
	void setData(T& data){*this->data=data;}
	void setData2(T* data){this->data=data;}
};
#endif /* NODE_H_ */
