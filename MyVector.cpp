#include "MyVector.h"

/*IVector::IVector(const MyVector& ve)noexcept : v{ ve }, poz{ 0 } {}
IVector::IVector(const MyVector& ve, int poz)noexcept : v{ ve }, poz{ poz } {}

const Elem& IVector::operator*()noexcept {
	return v.elems[poz];
}

IVector& IVector::operator++()noexcept {
	poz++;
	return *this;
}

bool IVector::operator==(const IVector it2)noexcept {
	return poz == it2.poz;
}

bool IVector::operator!=(const IVector it2) noexcept {
	return poz != it2.poz;
}

Elem& IVector::elem() {
	return v.elems[poz];
}

MyVector::MyVector(const MyVector& v) {
	cp = v.cp;
	lg = v.lg;
	elems = new Elem[cp];
	for (int i = 0; i < cp; i++) {
		elems[i] = v.elems[i];
	}
}

const MyVector& MyVector::operator=(const MyVector& v) {
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

void MyVector::redim() {
	Elem* e = new Elem[cp * 2];
	for (int i = 0; i < lg; i++) {
		e[i] = elems[i];
	}
	delete[] elems;
	elems = e;
	cp = 2 * cp;
}

void MyVector::push(const Elem& m) {
	if (cp == lg) {
		redim();
	}
	elems[lg++] = m;
}

void MyVector::erase(int poz) {
	for (int i = poz; i < lg - 1; i++) {
		elems[i] = elems[i + 1];
	}
	lg--;
}

int MyVector::size() const noexcept{
	return lg;
}

Elem& MyVector::get_el(int poz) const {
	return elems[poz];
}

Elem& MyVector::operator[](int poz) const {
	return elems[poz];
}

void MyVector::set(int poz, const Elem& m) {
	elems[poz] = m;
}

IVector& IVector::operator+(int p){
	this->poz += p;
	return *this;
}

IVector MyVector::begin() noexcept{
	return IVector(*this);
}

IVector MyVector::end() noexcept{
	return IVector(*this, lg);
}
*/

