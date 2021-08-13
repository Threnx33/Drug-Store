#pragma once
#include "Med.h"


template<typename Elem>
class IVector;

template<typename Elem>
class MyVector{
private:
	int cp;
	int lg;
	Elem* elems;
	void redim();
	friend class IVector<Elem>;
public:
	MyVector()noexcept : cp{ 2 }, lg{ 0 }, elems{ new Elem[2] } {};
	MyVector(const MyVector& v);
	MyVector(MyVector&& v);
	const MyVector& operator=(const MyVector& v);
	const MyVector& operator=(MyVector&& v);
	~MyVector(){delete[] elems; };

	Elem& operator[](int poz)const;
	void push(const Elem& m);
	void erase(int poz);
	int size() const noexcept;
	Elem& get_el(int poz) const noexcept;
	void set(int poz, const Elem& m);

	IVector<Elem> begin()noexcept;
	IVector<Elem> end()noexcept;
};

/*Face o copie a vectorului
*/
template<typename Elem>
MyVector<Elem>::MyVector(const MyVector& v) {
	cp = v.cp;
	lg = v.lg;
	elems = new Elem[cp];
	for (int i = 0; i < cp; i++) {
		elems[i] = v.elems[i];
	}
}

/*Move constructor
*/
template<typename Elem>
MyVector<Elem>::MyVector(MyVector&& v) {
	cp = v.cp;
	lg = v.lg;
	elems = v.elems;
	
	v.cp = 0;
	v.lg = 0;
	v.elems = nullptr;
}

/*Operatorul assigment. Face copie la elems.
*/
template<typename Elem>
const MyVector<Elem>& MyVector<Elem>::operator=(const MyVector<Elem>& v) {
	if (this == &v) {
		return *this;
	}
	cp = v.cp;
	lg = v.lg;
	delete[] elems;
	elems = new Elem[cp];
	for (int i = 0; i < v.lg; i++) {
		elems[i] = v.elems[i];
	}
	return *this;
}

/*Move assigment.
*/
template<typename Elem>
const MyVector<Elem>& MyVector<Elem>::operator=(MyVector<Elem>&& v) {
	if (this == &v) {
		return *this;
	}
	cp = v.cp;
	lg = v.lg;
	delete[] elems;
	elems = v.elems;

	v.cp = 0;
	v.lg = 0;
	v.elems = nullptr;
	return *this;
}

/*Redimensionare
*/
template<typename Elem>
void MyVector<Elem>::redim() {
	Elem* e = new Elem[cp * 2];
	for (int i = 0; i < lg; i++) {
		e[i] = elems[i];
	}
	delete[] elems;
	elems = e;
	cp = 2 * cp;
}

/*Push_back
*/
template<typename Elem>
void MyVector<Elem>::push(const Elem& m) {
	if (cp == lg) {
		redim();
	}
	elems[lg++] = m;
}

/*Sterge element de pe pozitia poz
*/
template<typename Elem>
void MyVector<Elem>::erase(int poz) {
	for (int i = poz; i < lg - 1; i++) {
		elems[i] = elems[i + 1];
	}
	lg--;
}

/*Get lungime array
*/
template<typename Elem>
int MyVector<Elem>::size() const noexcept {
	return lg;
}

/*Get element de pe poz
*/
template<typename Elem>
Elem& MyVector<Elem>::get_el(int poz) const noexcept {
	return elems[poz];
}

/*Operatorul[] de pe pozitia poz
*/
template<typename Elem>
Elem& MyVector<Elem>::operator[](int poz) const {
	return elems[poz];
}

/*Seteaza elementul de pe pozitia poz
*/
template<typename Elem>
void MyVector<Elem>::set(int poz, const Elem& m) {
	elems[poz] = m;
}

/*Get iterator begin
*/
template<typename Elem>
IVector<Elem> MyVector<Elem>::begin() noexcept {
	return IVector<Elem>(*this);
}

/*Get iterator end
*/
template<typename Elem>
IVector<Elem> MyVector<Elem>::end() noexcept {
	return IVector<Elem>(*this, lg);
}


template<typename Elem>
class IVector {
private:
	const MyVector<Elem>& v;
	int poz;
public:
	IVector(MyVector<Elem>& ve)noexcept;
	IVector(MyVector<Elem>& ve, int poz)noexcept;
	IVector(const IVector<Elem>& i)noexcept : v{ i.v }, poz{ i.poz } {};

	Elem& elem()noexcept;
	const Elem& operator*()noexcept;
	IVector<Elem>& operator++()noexcept;
	IVector<Elem>& operator--()noexcept;
	IVector<Elem> operator+(int p);
	IVector<Elem> operator-(int p);
	bool operator==(const IVector<Elem> it2)noexcept;
	bool operator!=(const IVector<Elem> it2)noexcept;
};

/*Constructor copiere
*/
template<typename Elem>
IVector<Elem>::IVector(MyVector<Elem>& ve)noexcept : v{ ve }, poz{ 0 } {}

/*Constructor copiere de pe pozitia poz
*/
template<typename Elem>
IVector<Elem>::IVector(MyVector<Elem>& ve, int poz)noexcept : v{ ve }, poz{ poz } {}

/*Dereferentiere iterator
*/
template<typename Elem>
const Elem& IVector<Elem>::operator*()noexcept {
	return v.elems[poz];
}

/*Iteratorul urmator
*/
template<typename Elem>
IVector<Elem>& IVector<Elem>::operator++()noexcept {
	poz++;
	return *this;
}

/*Iteratorul precedent
*/
template<typename Elem>
IVector<Elem>& IVector<Elem>::operator--()noexcept {
	poz--;
	return *this;
}

/*Copie iterator de pe pozitia poz+p
*/
template<typename Elem>
IVector<Elem> IVector<Elem>::operator+(int p) {
	poz += p;
	IVector<Med> iaux{*this};
	poz -= p;
	return iaux;
}

/*Copie iterator de pe pozitia poz-p
*/
template<typename Elem>
IVector<Elem> IVector<Elem>::operator-(int p) {
	poz -= p;
	IVector<Med> iaux{ *this };
	poz += p;
	return iaux;
}

/*Operatorul de egalitate. Pentru for range
*/
template<typename Elem>
bool IVector<Elem>::operator==(const IVector<Elem> it2)noexcept {
	return poz == it2.poz;
}

/*Operatorul de inegalitate. Pentru for range
*/
template<typename Elem>
bool IVector<Elem>::operator!=(const IVector<Elem> it2) noexcept {
	return poz != it2.poz;
}

/*Elementul de pe pozitia curenta. Pentru for manul begin, end
*/
template<typename Elem>
Elem& IVector<Elem>::elem()noexcept {
	return v.elems[poz];
}