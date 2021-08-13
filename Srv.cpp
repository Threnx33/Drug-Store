#include "Srv.h"
#include <algorithm>
using std::swap;
using std::copy_if;
using std::function;
using std::sort;
using std::vector;
using std::reverse;
using std::make_unique;
using std::move;

/*Adauga un medicament. Arunca exceptie daca medicament nu e valid. 
* Arunca exceptie daca medicamentul exista deja.
*/
void Srv::add(const string& denum, const string& produc, const string& subst, const double pret) {
	Elem m{ denum, produc, subst, pret };
	v.valid_med(m);
	repo.add(m);
	UndoActions.push_back( make_unique<AddUndo>(repo, m.get_denum()) );
}

/*Updateaza un medicament. Arunca exceptie daca medicament nu e valid.
* Arunca exceptie daca medicamentul nu exista.
*/
void Srv::upd(const string& denum, const string& produc, const string& subst, const double pret) {
	Elem m{ denum, produc, subst, pret };
	v.valid_med(m);
	auto med = repo.upd(m);
	UndoActions.push_back(make_unique<UpdUndo>(repo, med));
}

/*Cauta un medicament. Arunca exceptie daca denumirea medicamentului nu e valid.
* Arunca exceptie daca medicamentul nu exista.
*/
const Elem& Srv::search(const string& denum) {
	v.valid_denum(denum);
	return repo.search(denum);
}

/*Sterge un medicament. Arunca exceptie daca denumirea medicamentului nu e valid.
* Arunca exceptie daca medicamentul nu exista.
*/
void Srv::del(const string& denum) {
	v.valid_denum(denum);
	auto med = repo.del(denum);
	UndoActions.push_back(make_unique<DelUndo>(repo, med));
}

/*Returneaza referinta la lista de medicamente
*/
vector<Elem>& Srv::get_all(){
	return repo.get_all();
}

/*Filtreaza medicamentele care respecta functia lambda f
void Srv::copy_daca(vector<Elem> meds, vector<Elem>& rez, function<bool(const Elem& m)> f) {
	for (const auto& it : meds) {
		if (f(it)) {
			rez.push_back(it);
		}
	}
}*/

/*Filtreaza dupa pret
*/
vector<Elem> Srv::filtrare_pret(double pret) {
	vector<Elem> meds{repo.get_all()}, rez;
	copy_if(meds.begin(), meds.end(), back_inserter(rez),[&pret](const Elem& a) noexcept { return a.get_pret() < pret; });
	return rez;
}

/*Filtreaza dupa substanta
*/
vector<Elem> Srv::filtrare_subst(string subst) {
	vector<Elem> meds{repo.get_all()}, rez;
	copy_if(meds.begin(), meds.end(), back_inserter(rez), [&subst](const Elem& a) { return a.get_subst() == subst; });
	return rez;
}

/*Sorteaza secvential dupa o functie de comparare f
void Srv::sortGen(vector<Elem>& rez, function<bool(const Elem& a, const Elem& b)> f) {
	for(auto& it: rez){
		for (auto& it2:rez) {
			if ( !f(it, it2) ) {
				swap(it, it2);
			}
		}
	}
}*/

/*Sorteaza dupa denumire
*/
vector<Elem> Srv::sort_denum() {
	auto rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Elem& a, const Elem& b) {
		if (a.get_denum() < b.get_denum()) return 1;
		return 0;
	});
	return rez;
}

/*if (a.get_produc() == b.get_produc()) return 1;
else if (a.get_produc() < b.get_produc()) return (1 ^ rev);
return (0 ^ rev);*/
vector<Elem> Srv::sort_produc() {
	auto rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Elem& a, const Elem& b) noexcept {
		if (a.get_produc() < b.get_produc()) return 1;
		return 0;
		});
	return rez;
}

/*Sorteaza dupa substanta si pret
*/
vector<Elem> Srv::sort_substPret() {
	auto rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Elem& a, const Elem& b) {
		if (a.get_subst() < b.get_subst() || (a.get_subst() == b.get_subst() && a.get_pret() < b.get_pret()) ) return 1;
		return 0;
		});
	return rez;
}

void Srv::goleste_ret() noexcept {
	reteta.goleste_ret();
}

void Srv::adauga_ret(const string& denum) {
	v.valid_denum(denum);
	reteta.adauga_ret(denum);
}

void Srv::adauga_rnd_ret(int nr) {
	reteta.adauga_rnd_ret(nr);
}

void Srv::export_ret(string& fisier) {
	reteta.export_ret(fisier);
}

size_t Srv::get_dim_ret() noexcept {
	return reteta.get_dim_ret();
}

map<string, DTO> Srv::get_dict() {
	map<string, DTO> dict;
	auto& meds = repo.get_all();
	for (const auto& med : meds) {
		auto it = dict.find(med.get_produc());
		if (it == dict.end()) {
			dict[med.get_produc()] = DTO{ med.get_produc() };
		}
		else {
			it->second.incr();
		}
	}
	return dict;
}

void Srv::undo() {
	if (UndoActions.size() < 1) {
		throw UndoException("Nu se poate da undo!\n");
	}
	UndoActions.back()->doUndo();
	UndoActions.pop_back();
}

size_t Srv::get_dim_undo() noexcept {
	return UndoActions.size();
}

vector<Elem>& Srv::get_allR() {
	return reteta.get_allR();
}