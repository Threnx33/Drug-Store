#pragma once
#include <map>
#include "Undo.h"
#include "Repo.h"
#include "Reteta.h"
#include "DTO.h"
#include <functional>
using std::function;
using std::map;
using std::unique_ptr;

class Srv{
private:
	Repo& repo;
	Reteta& reteta;
	Valid& v;
	vector<unique_ptr<ActiuneUndo>>UndoActions;
public:
	Srv(Repo& r, Valid& v, Reteta& ret) noexcept :repo{ r }, v{ v }, reteta{ret} {};
	Srv(const Srv& s) = delete;

	void add(const string& denum, const string& produc, const string& subst, const double pret);
	void upd(const string& denum, const string& produc, const string& subst, const double pret);
	const Elem& search(const string& denum);
	void del(const string& denum);
	vector<Elem>& get_all();

	//void copy_daca(vector<Elem> meds, vector<Elem>& rez, function<bool(const Elem& m)> f);
	vector<Elem> filtrare_pret(double pret);
	vector<Elem> filtrare_subst(string subst);
	//void sortGen(vector<Elem>& rez, function<bool(const Elem& a, const Elem& b)> f);
	vector<Elem> sort_denum();
	vector<Elem> sort_produc();
	vector<Elem> sort_substPret();

	void goleste_ret() noexcept;
	void adauga_ret(const string& denum);
	void adauga_rnd_ret(int nr);
	void export_ret(string& fisier);
	vector<Elem>& get_allR();
	size_t get_dim_ret() noexcept;

	map<string, DTO> get_dict();

	void undo();
	size_t get_dim_undo() noexcept;
};
