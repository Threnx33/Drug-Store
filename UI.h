#pragma once
#include "Srv.h"

class UI{
private:
	Srv& srv;
	void comenzi();
public:
	UI(Srv& s) noexcept : srv{ s } {};
	UI(const UI& u) = delete;

	void run();
	void afis(vector<Elem>& meds);
	void add();
	void upd();
	void search();
	void filter();
	void sortare();
	void del();
	void goleste_ret();
	void adauga_ret();
	void adauga_rnd_ret();
	void export_ret();
	void dict();
	void undo();
};

