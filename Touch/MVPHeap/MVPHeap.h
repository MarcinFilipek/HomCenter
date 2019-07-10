/*
 * MVPHeap.h
 *
 *  Created on: 28 kwi 2017
 *      Author: Uzume
 */

#ifndef MVPHEAP_MVPHEAP_H_
#define MVPHEAP_MVPHEAP_H_

class AbstractPartition;
class MVPApplication;

class MVPHeap {
public:
	MVPHeap(AbstractPartition& pres, AbstractPartition& scr,
			MVPApplication& app) :
			presenterStorage(pres), screenStorage(scr), frontendApplication(app) {

	}
	virtual ~MVPHeap() {

	}

	AbstractPartition& presenterStorage;
	AbstractPartition& screenStorage;
	MVPApplication& frontendApplication;
};

#endif /* MVPHEAP_MVPHEAP_H_ */
