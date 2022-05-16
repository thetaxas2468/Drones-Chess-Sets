/*
 * Node_code.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef TREE_CODE_H_
#define TREE_CODE_H_
#include "Tree.h"
#include <iostream>
#include "Drone.h"
#include "Hybrid.h"
#include "SingleRotor.h"
#include "FixedWing.h"
#include "MultiRotor.h"
template<typename T>
void Tree<T>::remove(T& node) {
	if(head==0){
		return;
	}
	removeR(node,head);
}
template<typename T>
Node<T>* Tree<T>::removeR(T& node,Node<T>* rootie){
	if(rootie==0){
		return 0;
	}
	if(*rootie->getData()<node){
		rootie->setRight(removeR(node,rootie->getRight()));
	}
	else if(*rootie->getData()>node){
		rootie->setLeft(removeR(node,rootie->getLeft()));
	}
	else{
		if(rootie->getRight()==0&&rootie->getLeft()==0){
			delete rootie;
			rootie=0;
		}
		else if(rootie->getLeft()!=0){
			Node<T>* temp=successor(rootie);
			rootie->setData(*temp->getData());
			rootie->setLeft(removeR(*rootie->getData(),rootie->getLeft()));
		}
		else{
			Node<T>* temp=successor(rootie);
			rootie->setData(*temp->getData());
			rootie->setRight(removeR(*rootie->getData(),rootie->getRight()));
		}
	}
	return rootie;
}
template<typename T>
Node<T>* Tree<T>::searchByInt(int x) {
	if(head==0){
		return 0;
	}
	return searchByIntR(x,head);
}
template<typename T>
Node<T>* Tree<T>::searchByIntR(int place,Node<T>* head) {
	if(head==0){
//		cout<<"Doesnt exist"<<endl;
		return 0;
	}
	if(*head->getData()>place){
		return searchByIntR(place,head->getLeft());
	}
	else if(*head->getData()<place){
//		cout<<*head->getData()<<endl;
		return searchByIntR(place,head->getRight());
	}
	else{
//		cout<<"Found   "<<place<<endl;
		return head;
	}
}
template<typename T>
Node<T>* Tree<T>::search(T& node) {
	if(head==0){
		return 0;
	}
	return searchR(node,head);
}
template<typename T>
Node<T>* Tree<T>::searchR(T& node,Node<T>* head) {
	if(head==0){
//		cout<<"Doesnt exist"<<endl;
		return 0;
	}
	if(*head->getData()>node){
		return searchR(node,head->getLeft());
	}
	else if(*head->getData()<node){
//		cout<<*head->getData()<<endl;
		return searchR(node,head->getRight());
	}
	else{
//		cout<<"Found   "<<node<<endl;
		return head;
	}
}

template<typename T>
void Tree<T>::print() {
	printR(head);
}
template<typename T>
void Tree<T>::printR(Node<T>* head) {
	if(head==0){
		return;
	}
	printR(head->getLeft());
	cout<<*head->getData();
	printR(head->getRight());
}

template<typename T>
void Tree<T>::insert(T *node) {
	if(head==0){
		head=new Node<T>(node,0,0);
		return;
	}
	else{
		insertR(node,head);
		return;
	}
}
template<typename T>
void Tree<T>::insertR(T* node,Node<T>* head) {
	if(*node==*head->getData()){
		head->setData2(node);
		return;
	}
	if(*node>*head->getData()){
		if(head->getRight()==0){
			head->setRight(new Node<T>(node,0,0));
			return;
		}
		else{
			insertR(node,head->getRight());
		}
	}
	else{
		if(head->getLeft()==0){
			head->setLeft(new Node<T>(node,0,0));
			return;
		}
		else{
			insertR(node,head->getLeft());
		}
	}
}

template<typename T>
Node<T>* Tree<T>::min() {
	return minR(head);
}
template<typename T>
Node<T>* Tree<T>::minR(Node<T>* head) {
	if(head==0){
		return 0;
	}
	while(head->getLeft()!=0){
		head=head->getLeft();
	}
	return head;
}
template<typename T>
Node<T>* Tree<T>::max() {
	return maxR(head);
}
template<typename T>
Node<T>* Tree<T>::maxR(Node<T>* head) {
	if(head==0){
		return 0;
	}
	while(head->getRight()!=0){
		head=head->getRight();
	}
	return head;
}
#endif /* TREE_CODE_H_ */
