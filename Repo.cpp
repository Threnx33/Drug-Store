#include "Med.h"
#include "Repo.h"
#include "MyVector.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
using std::mt19937;
using std::pair;
using std::uniform_int_distribution;
using std::random_device;
using std::cout;
using std::find_if;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::to_string;


/*Returneaza stringul exceptiei repo
*/
const string& RepoException::get_msg() const noexcept {
	return msg; 
}

/*Adauga un medicament. Arunca exceptie daca medicamentul exista deja.
*/
void RepoM::add(const Elem& m) {
	for (const auto& elem : meds) {
		if (elem.get_denum() == m.get_denum()) {
			throw RepoException{"Medicament existent!\n"};
		}
	}
	meds.push_back(m);
}

/*Updateaza un medicament. Arunca exceptie daca medicamentul nu exista.
*/
Elem RepoM::upd(const Elem& m){
	int i = 0;
	for (auto& elem : meds) {
		if (elem.get_denum() == m.get_denum()) {
			Elem rez = elem;
			elem = m;
			return rez;
		}
		i++;
	}
	throw RepoException{ "Medicament inexistent!\n" };
}

/*Cauta un medicament. Arunca exceptie daca medicamentul nu exista.
for (const auto& elem : meds) {
	if (elem.get_denum() == denum) {
		return elem;
	}
}
*/
const Elem& RepoM::search(const string& denum) {
	const auto& it = find_if(meds.begin(), meds.end(), [&denum](const Elem& med) {
		return med.get_denum() == denum;
	});
	if (it == meds.end()) {
		throw RepoException{ "Medicament inexistent!\n" };
	}
	return *it;
}

/*Sterge un medicament. Arunca exceptie daca medicamentul nu exista.
*/
Elem RepoM::del(const string& denum){
	int i = 0;
	for (auto& elem : meds) {
		if (elem.get_denum() == denum) {
			Elem rez = elem;
			meds.erase(meds.begin()+i);
			return rez;
		}
		i++;
	}
	throw RepoException{ "Medicament inexistent!\n" };
}

/*Returneaza referinta spre lista de medicamente
*/
vector<Elem>& RepoM::get_all() noexcept {
	return meds;
}

size_t RepoM::dim() noexcept {
	return meds.size();
}

void RepoF::load() {
	ifstream fin(file);
	char line[50]{};
	char* strmax = nullptr;
	vector<string>v;
	while (fin.getline(line, 50, '\n')) {
		for (char* p = strtok_s(line, ",", &strmax); p != nullptr; p = strtok_s(nullptr, ",", &strmax)) {
			v.push_back(p);
		}
		RepoM::add( Elem{ v[0], v[1], v[2], stof(v[3]) });
		v.clear();
	}
}

void RepoF::write() {
	ofstream fout(file);
	for (const auto& med : RepoM::get_all()) {
		fout << med.get_denum() << ',' << med.get_produc() << ',' << med.get_subst() << ',' << med.get_pret() << '\n';
	}
}

void RepoF::add(const Elem& m) {
	RepoM::add(m);
	write();
}

Elem RepoF::upd(const Elem& m) {
	auto med = RepoM::upd(m);
	write();
	return med;
}

Elem RepoF::del(const string& denum) {
	auto med = RepoM::del(denum);
	write();
	return med;
}

size_t RepoL::dim() noexcept {
	return meds.size();
}


double RepoL::boolaneala() const {
	mt19937 generator{ random_device{}() };
	const uniform_int_distribution<int> dist(0, 100);
	const int rndNr = dist(generator);
	return rndNr / 100.0;
}

/*Adauga un medicament. Arunca exceptie daca medicamentul exista deja.
*/
void RepoL::add(const Elem& m) {
	const double prob = boolaneala();
	if (prob <= p) {
		throw RepoException("Probabilitate prea mica\n");
	}
	for (const auto& elem : meds) {
		if (elem.second.get_denum() == m.get_denum()) {
			throw RepoException{ "Medicament existent!\n" };
		}
	}
	meds[m.get_denum()] = m;
}

/*Updateaza un medicament. Arunca exceptie daca medicamentul nu exista.
*/
Elem RepoL::upd(const Elem& m) {
	const double prob = boolaneala();
	if (prob <= p) {
		throw RepoException("Probabilitate prea mica\n");
	}
	int i = 0;
	for (auto& elem : meds) {
		if (elem.second.get_denum() == m.get_denum()) {
			Elem rez = elem.second;
			elem.second.set_denum(m.get_denum());
			elem.second.set_produc(m.get_produc());
			elem.second.set_subst(m.get_subst());
			elem.second.set_pret(m.get_pret());
			return rez;
		}
		i++;
	}
	throw RepoException{ "Medicament inexistent!\n" };
}

/*Cauta un medicament. Arunca exceptie daca medicamentul nu exista.
for (const auto& elem : meds) {
	if (elem.get_denum() == denum) {
		return elem;
	}
}
*/
const Elem& RepoL::search(const string& denum) {
	const double prob = boolaneala();
	if (prob <= p) {
		throw RepoException("Probabilitate prea mica\n");
	}
	const auto& it = find_if(meds.begin(), meds.end(), [&denum](pair<const string, const Elem> med) {
		return med.second.get_denum() == denum;
		});
	if (it == meds.end()) {
		throw RepoException{ "Medicament inexistent!\n" };
	}
	return it->second;
}

/*Sterge un medicament. Arunca exceptie daca medicamentul nu exista.
*/
Elem RepoL::del(const string& denum) {
	const double prob = boolaneala();
	if (prob <= p) {
		throw RepoException("Probabilitate prea mica\n");
	}
	int i = 0;
	for (auto& elem : meds) {
		if (elem.second.get_denum() == denum) {
			Elem rez = elem.second;
			meds.erase(denum);
			return rez;
		}
		i++;
	}
	throw RepoException{ "Medicament inexistent!\n" };
}

/*Returneaza referinta spre lista de medicamente
*/
vector<Elem>& RepoL::get_all() {
	v.clear();
	for (auto& elem : meds) {
		v.push_back(elem.second);
	}
	return v;
}