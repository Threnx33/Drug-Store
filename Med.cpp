#include "Med.h"
#include <iostream>
using std::cout;
using std::to_string;

const string Med::get_denum() const  {
	return denum;
}

const string& Med::get_produc() const noexcept {
	return produc;
}

const string Med::get_subst() const {
	return subst;
}

const double Med::get_pret() const noexcept{
	return pret;
}

void Med::set_denum(const string& _denum) {
	denum = _denum;
}

void Med::set_produc(const string& _produc) {
	produc = _produc;
}

void Med::set_subst(const string& _subst) {
	subst = _subst;
}

void Med::set_pret(const double _pret) noexcept{
	pret = _pret;
}

Med& Med::operator=(const Med& m) {
	denum = m.get_denum();
	produc = m.get_produc();
	subst = m.get_subst();
	pret = m.get_pret();
	return (*this);
}

const string Med::stringify() const{
	return "Denumire: " + denum + ", Producator: " + produc +
		", Substanta: " + subst + ", Pret: " + to_string(pret);
}

/*Returneaza mesajul de ValidException
*/
const string& ValidException::get_msg() const noexcept {
	return msg;
}

/*Valideaza medicament
*/
void Valid::valid_med(const Med& m) {
	string err{ "" };
	if (m.get_denum() == "")
		err += "Denumire incorecta!";
	if (m.get_produc() == "")
		err += "Producator incorect!";
	if (m.get_subst() == "")
		err += "Substanta incorecta!";
	if (m.get_pret() <= 0)
		err += "Pret incorect!";
	if (err != "") {
		err += "\n";
		throw ValidException(err);
	}
}

/*Valideaza denumire
*/
void Valid::valid_denum(const string& denum) {
	if (denum == "") {
		throw ValidException("Denumire incorecta!\n");
	}
}