#pragma once
#include "Repo.h"
#include <string>
using std::string;

typedef Med TElem;

class Reteta{
private:
	Repo& repo;
	vector<TElem> reteta;
public:
	Reteta(Repo& r) noexcept: repo{ r } {};
	void goleste_ret() noexcept;
	void adauga_ret(const string& denum);
	void adauga_rnd_ret(int nr);
	void export_ret(string& fisier);
	vector<Elem>& get_allR();
	size_t get_dim_ret() noexcept;
};
