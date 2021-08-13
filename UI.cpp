#include "UI.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::string;

/*Afiseaza comenzile
*/
void UI::comenzi() {
	cout << "1-Add medicament\n2-Update medicament\n3-Search medicament\n"
		"4-Delete medicament\n5-Filtreaza\n6-Sortare\n9-Afisare medicamente\n"
		"10-Adauga medicament in reteta\n11-Adauga medicament aleatoriu\n"
		"12-Export\n13-Goleste reteta\n20-Dictionar\n30-Undo\n0-Exit\n";
}

/*afiseaza un MyVector
*/
void UI::afis(vector<Elem>& meds){
	if (meds.size() == 0) {
		cout << "Nu exista nici un medicament!\n";
		return;
	}
	for (auto& elem : meds) {
		cout << elem.stringify();
	}
}

/*Adauga un medicament
*/
void UI::add() {
	cout << "Adauga medicament\n";
	string denum, produc, subst;
	double pret;
	cout << "Denumire: ";
	cin >> denum;
	cout << "Producator: ";
	cin >> produc;
	cout << "Substanta: ";
	cin >> subst;
	cout << "Pret: ";
	cin >> pret;
	try {
		srv.add(denum, produc, subst, pret);
		cout << "Adaugare reusita!\n";
	}
	catch (const RepoException& re) {
		cout << re.get_msg();
	}
	catch (const ValidException& ve) {
		cout << ve.get_msg();
	}
}

/*Updateaza un medicament
*/
void UI::upd() {
	cout << "Updateaza medicament\n";
	string denum, produc, subst;
	double pret;
	cout << "Denumire: ";
	cin >> denum;
	cout << "Producator: ";
	cin >> produc;
	cout << "Substanta: ";
	cin >> subst;
	cout << "Pret: ";
	cin >> pret;
	try {
		srv.upd(denum, produc, subst, pret);
		cout << "Update reusit!\n";
	}
	catch (const RepoException& re) {
		cout << re.get_msg();
	}
	catch (const ValidException& ve) {
		cout << ve.get_msg();
	}
}

/*Cauta un medicament
*/
void UI::search() {
	cout << "Search medicament\n";
	Elem Elem;
	string denum;
	cout << "Denumire: ";
	cin >> denum;
	try {
		Elem = srv.search(denum);
		cout << "Medicament gastit! " << "Denumire: " << Elem.get_denum() << ", Producator: " << Elem.get_produc()
			<< ", Substanta: " << Elem.get_subst() << ", Pret: " << Elem.get_pret() << '\n'; ;
	}
	catch (const RepoException& re) {
		cout << re.get_msg();
	}
	catch (const ValidException& ve) {
		cout << ve.get_msg();
	}
}

/*Sterge un medicament
*/
void UI::del() {
	cout << "Delete medicament\n";
	string denum;
	cout << "Denumire: ";
	cin >> denum;
	try {
		srv.del(denum);
		cout << "Element sters!\n";
	}
	catch (const RepoException& re) {
		cout << re.get_msg();
	}
	catch (const ValidException& ve) {
		cout << ve.get_msg();
	}
}

/*filtreaza medicamente
*/
void UI::filter() {
	cout << "Filtreaza(0-Pret,1-Substanta): ";
	int cmd;
	cin >> cmd;
	vector<Elem> meds;
	if (cmd == 0) {
		double pret;
		cout << "Pret: ";
		cin >> pret;
		meds = srv.filtrare_pret(pret);
	}
	else if (cmd == 1) {
		string subst;
		cout << "Substanta: ";
		cin >> subst;
		meds = srv.filtrare_subst(subst);
	}
	else {
		cout << "Comanda invalida!\n";
		return;
	}
	afis(meds);
}

/*Sorteaza medicamente
*/
void UI::sortare() {
	cout << "Sorteaza(0-Denumire, 1-Producator, 2-Substanta+Pret): ";
	int caz;
	cin >> caz;
	bool rev;
	cout << "Reversed(0-False, 1-True): ";
	cin >> rev;
	vector<Elem>rez;
	if (caz == 0) {
		rez = srv.sort_denum();
	}
	else if (caz == 1) {
		rez = srv.sort_produc();
	}
	else if (caz == 2) {
		rez = srv.sort_substPret();
	}
	else {
		cout << "Comanda invalida!\n";
		return;
	}
	afis(rez);
}

void UI::goleste_ret() {
	srv.goleste_ret();
	cout << "Reteta golita";
}

void UI::adauga_ret() {
	cout << "Adauga medicament in reteta\n";
	string denum;
	cout << "Denumire: ";
	cin >> denum;
	try {
		srv.adauga_ret(denum);
		cout << "Medicament adaugat!\n";
		cout<<"Dimensiune noua: " << srv.get_dim_ret() <<'\n';
	}
	catch (const RepoException& re) {
		cout << re.get_msg();
	}
	catch (const ValidException& ve) {
		cout << ve.get_msg();
	}
}

void UI::adauga_rnd_ret() {
	cout << "Adauga medicamente aleatorii in reteta\n";
	int nr;
	cout << "Nr: ";
	cin >> nr;
	try {
		srv.adauga_rnd_ret(nr);
		cout << "Dimensiune noua: " << srv.get_dim_ret();
	}
	catch(const RepoException& re){
		cout << re.get_msg();
	}
}

void UI::export_ret() {
	cout << "Export\n";
	string fisier;
	cout << "Fisier: ";
	cin >> fisier;
	srv.export_ret(fisier);
}

void UI::dict() {
	auto dict = srv.get_dict();
	for (auto& el : dict) {
		cout << "Key: " << el.first << " Produc: " << el.second.get_produc() << " Nr: "<< el.second.get_nr() << '\n';
	}
}

void UI::undo() {
	try {
		srv.undo();
		cout << "Undo realizat cu succes!\n";
	}
	catch (const UndoException& ue) {
		cout << ue.get_msg();
	}
}


void UI::run() {
	int cmd = 0;
	comenzi();
	while (true) {
		cout << ">>>";
		cin >> cmd;
		switch (cmd) {
		case 0:
			cout << "Iesit\n";
			return;
		case 1:
			add();
			break;
		case 2:
			upd();
			break;
		case 3:
			search();
			break;
		case 4:
			del();
			break;
		case 5:
			filter();
			break;
		case 6:
			sortare();
			break;
		case 9:
			afis(srv.get_all());
			break;
		case 10:
			adauga_ret();
			break;
		case 11:
			adauga_rnd_ret();
			break;
		case 12:
			export_ret();
			break;
		case 13:
			goleste_ret();
			break;
		case 20:
			dict();
			break;
		case 30:
			undo();
			break;
		default:
			cout << "Comanda invalida";
		}
	}
}
