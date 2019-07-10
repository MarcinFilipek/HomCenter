/*
 * Lista.h
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#ifndef HOME_INTERFACES_LISTA_H_
#define HOME_INTERFACES_LISTA_H_

#include "stdint.h"

template<class T>
class Lista{
private:
	T* head;
	T* tail;
public:
	Lista() {
		head = 0;
		tail = 0;
	}
	virtual ~Lista(){}
	void add()
	{
		if(!head){
			head = new T();
			tail = head;
		} else {
			T* temp = new T();
			if(!temp){
				while(1);
			}
			tail->setNext(temp);
			tail = temp;
		}
	}

	T* get(int8_t index){
		T* wskTemp = 0;
		wskTemp = head;
		for(int8_t i = 0; i < index; i++){
			if(wskTemp->getNext()){
				wskTemp = wskTemp->getNext();
			}
		}
		return wskTemp;
	}

};

#endif /* HOME_INTERFACES_LISTA_H_ */
