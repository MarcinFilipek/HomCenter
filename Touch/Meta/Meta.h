/*
 * Meta.h
 *
 *  Created on: 27 kwi 2017
 *      Author: Uzume
 */

#ifndef META_META_H_
#define META_META_H_

struct Nil {
};

template<typename First, typename Next>
struct TypeList {
	typedef First first;
	typedef Next next;
};

template<typename T1, typename T2, bool choose1 = (sizeof(T1) > sizeof(T2))>
struct type_max {
	typedef T1 type;
};

template<typename T1, typename T2>
struct type_max<T1, T2, false> {
	typedef T2 type;
};

template<typename T> struct select_type_maxsize;

template< typename First, typename Next>
struct select_type_maxsize<TypeList<First, Next> > : public type_max<First, typename select_type_maxsize<Next>::type >{
};

template<typename First>
struct select_type_maxsize<TypeList<First, Nil> > {
	typedef First type;
};
#endif /* META_META_H_ */
