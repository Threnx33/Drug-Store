#pragma once
#include "Tests.h"
#include "Srv.h"
#include <assert.h>
#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::vector;

void Teste::test_all(){
	test_med();
	test_valid();
	//test_MyVector();
	test_dto();
	test_reteta();
	test_repo();
	test_repoF();
	test_repoL();
	test_undo();
	test_srv();
}

void Teste::test_med() {
	Med m1{ "A","B","C",5.5 };
	Med m2;

	assert(m1.get_denum() == "A");
	assert(m1.get_produc() == "B");
	assert(m1.get_subst() == "C");
	assert(fabs(m1.get_pret() - 5.5) < 0.0001);
	m2 = m1;
	assert(m2.get_denum() == "A");
	assert(m1.stringify() == "Denumire: A, Producator: B, Substanta: C, Pret: 5.500000");
	m1.set_denum("A1");
	m1.set_produc("B1");
	m1.set_subst("C1");
	m1.set_pret(6);
	assert(m1.stringify() == "Denumire: A1, Producator: B1, Substanta: C1, Pret: 6.000000");
}

void Teste::test_valid() {
	Med m1{ "A","B","C",5.5 };
	Med m2{ "", "", "", -2.5 };
	Valid v;
	v.valid_med(m1);
	try {
		v.valid_med(m2);}
	catch (const ValidException& ve) { // hai noroc
		assert(ve.get_msg() == "Denumire incorecta!Producator incorect!Substanta incorecta!Pret incorect!\n");
	}
	v.valid_denum("A");
	try {
		v.valid_denum("");}
	catch (const ValidException& ve) { // hai noroc
		assert(ve.get_msg() == "Denumire incorecta!\n");
	}
}

void Teste::test_dto() {
	DTO dto{ "DA" };
	assert(dto.get_produc() == "DA");
	assert(dto.get_nr() == 1);
	dto.incr();
	assert(dto.get_nr() == 2);
}

void Teste::test_reteta() {
	RepoM repo;
	Reteta reteta{ repo };
	Med m1{ "A", "A", "A", 5.5 };
	Med m2{ "B", "DA", "B", 9 };
	Med m3{ "D", "D", "D", 1 };

	//test adauga_ret
	repo.add(m1);
	repo.add(m2);
	repo.add(m3);

	reteta.adauga_ret(m1.get_denum());
	assert(reteta.get_dim_ret() == 1);
	reteta.adauga_ret(m1.get_denum());
	assert(reteta.get_dim_ret() == 2);
	assert(reteta.get_allR().size() == 2);

	//test adauga_rnd_ret
	reteta.adauga_rnd_ret(4);
	assert(reteta.get_dim_ret() == 6);
	string fisier{ "test_export" };
	reteta.export_ret(fisier);
	reteta.goleste_ret();
	assert(reteta.get_dim_ret() == 0);
	repo.del("A");
	repo.del("B");
	repo.del("D");
	assert(repo.dim() == 0);
	try {
		reteta.adauga_rnd_ret(2);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Nu exista medicamente de adaugat in reteta!\n");
	}
}

void Teste::test_repoL() {
	RepoL repo{-1};
	Med m1{ "A", "A", "A", 5.5 };
	Med m2{ "B", "DA", "B", 9 };
	Med m3{ "D", "D", "D", 1 };
	Med m4{ "C", "C", "C", 2 };
	Med m5{ "A", "Z", "Z", 420 };

	repo.add(m1);
	assert(repo.dim() == 1);
	assert(repo.get_all().size() == 1);
	try {
		repo.add(m1);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament existent!\n");
	}
	assert(repo.get_all().size() == 1);
	repo.add(m2);
	assert(repo.get_all().size() == 2);

	repo.upd(m5);
	assert(repo.get_all().size() == 2);
	assert(repo.get_all()[0].get_produc() == "Z");
	try {
		repo.upd(m4);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test search
	assert(repo.search("B").get_produc() == "DA");
	try {
		repo.search("Gresit");
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test delete
	repo.del("B");
	assert(repo.get_all().size() == 1);
	try {
		repo.del("B");
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}
	assert(repo.get_all().size() == 1);
	repo.del("A");
	assert(repo.get_all().size() == 0);

	RepoL repo2{ 2 };
	try {
		repo2.add(m1);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Probabilitate prea mica\n");
	}
	try {
		repo2.upd(m5);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Probabilitate prea mica\n");
	}
	try {
		repo2.search(m1.get_denum());
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Probabilitate prea mica\n");
	}
	try {
		repo2.del(m1.get_denum());
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Probabilitate prea mica\n");
	}
}

void Teste::test_repo() {
	RepoM repo;
	Med m1{ "A", "A", "A", 5.5 };
	Med m2{ "B", "DA", "B", 9 };
	Med m3{ "D", "D", "D", 1 };
	Med m4{ "C", "C", "C", 2 };
	Med m5{ "A", "Z", "Z", 420 };

	//test add
	repo.add(m1);
	assert(repo.get_all().size() == 1);
	try {
		repo.add(m1);}
	catch(const RepoException& re){
		assert(re.get_msg() == "Medicament existent!\n");
	}
	assert(repo.get_all().size() == 1);
	repo.add(m2);
	assert(repo.get_all().size() == 2);

	//test update
	repo.upd(m5);
	assert(repo.get_all().size() == 2);
	assert(repo.get_all()[0].get_produc() == "Z");
	try {
		repo.upd(m4);}
	catch(const RepoException& re){
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test search
	assert(repo.search("B").get_produc() == "DA");
	try {
		repo.search("Gresit");}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test delete
	repo.del("B");
	assert(repo.get_all().size() == 1);
	try {
		repo.del("B");}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}
	assert(repo.get_all().size() == 1);
	repo.del("A");
	assert(repo.get_all().size() == 0);
}

void Teste::test_repoF() {
	RepoF repoF{"test.in"};
	Med m1{ "A", "A", "A", 5.5 };
	Med m2{ "B", "DA", "B", 9 };
	Med m3{ "D", "D", "D", 1 };
	Med m4{ "C", "C", "C", 2 };
	Med m5{ "A", "Z", "Z", 420 };
	//test add
	repoF.add(m1);
	assert(repoF.get_all().size() == 1);
	try {
		repoF.add(m1);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament existent!\n");
	}
	assert(repoF.get_all().size() == 1);
	repoF.add(m2);
	assert(repoF.get_all().size() == 2);

	//test load
	RepoF repoF_load{ "test.in" };
	assert(repoF_load.get_all().size() == 2);

	//test update
	repoF.upd(m5);
	assert(repoF.get_all().size() == 2);
	assert(repoF.get_all()[0].get_produc() == "Z");
	try {
		repoF.upd(m4);
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test search
	assert(repoF.search("B").get_produc() == "DA");
	try {
		repoF.search("Gresit");
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test delete
	repoF.del("B");
	assert(repoF.get_all().size() == 1);
	try {
		repoF.del("B");
	}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}
	assert(repoF.get_all().size() == 1);
	repoF.del("A");
	assert(repoF.get_all().size() == 0);

	RepoF repoF_load2{ "test.in" };
	assert(repoF_load2.get_all().size() == 0);
}

void Teste::test_undo() {
	RepoM repo;
	Med m1{ "A", "A", "A", 5.5 };
	Med m2{ "B", "DA", "B", 9 };
	Med m5{ "A", "Z", "Z", 420 };

	repo.add(m1);
	repo.add(m2);
	assert(repo.get_all().size() == 2);
	AddUndo au{ repo, m2.get_denum() };
	au.doUndo();
	assert(repo.get_all().size() == 1);
	DelUndo du{ repo, m2 };
	du.doUndo();
	assert(repo.get_all().size() == 2);
	UpdUndo uu{ repo, m5 };
	uu.doUndo();
	assert(repo.get_all()[0].get_produc() == "Z");
}

void Teste::test_srv() {
	Valid v;
	RepoM repo;
	Reteta reteta{ repo };
	Srv srv(repo, v, reteta);
	Med m1{ "A", "A", "A", 5.5 };
	Med m2{ "B", "DA", "B", 9 };
	Med m3{ "D", "DA", "D", 1 };

	//test add
	srv.add("A", "A", "A", 5.5);
	assert(srv.get_dim_undo() == 1);
	assert(srv.get_all().size() == 1);
	try {
		srv.add("A", "A", "A", 5.5);}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament existent!\n");
	}
	assert(srv.get_all().size() == 1);
	srv.add("B", "DA", "B", 9);
	assert(srv.get_all().size() == 2);

	//test filtru
	vector<Elem> meds = srv.filtrare_pret(5.6);
	assert(meds.size() == 1);
	meds = srv.filtrare_pret(9.1);
	assert(meds.size() == 2);
	meds = srv.filtrare_subst("B");
	assert(meds.size() == 1);

	//test sort
	srv.add("C", "D", "B", 2);
	meds = srv.sort_denum();
	assert(meds.size() == 3);
	assert(meds[0].get_denum() == "A" && meds[1].get_denum() == "B");
	meds = srv.sort_produc();
	assert(meds[0].get_denum() == "A" && meds[1].get_denum() == "C");
	meds = srv.sort_substPret();
	assert(meds[0].get_denum() == "A" && meds[1].get_denum() == "C");
	srv.del("C");

	//test update
	srv.upd("A", "Z", "Z", 420);
	assert(srv.get_all().size() == 2);
	assert(srv.get_all()[0].get_produc() == "Z");
	try {
		srv.upd("Gresit", "C", "C", 24);}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test search
	assert(srv.search("B").get_produc() == "DA");
	try {
		srv.search("Gresit");}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}

	//test delete
	srv.del("B");
	assert(srv.get_all().size() == 1);
	try {
		srv.del("B");}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Medicament inexistent!\n");
	}
	assert(srv.get_all().size() == 1);

	//test adauga_ret
	srv.add("B", "DA", "B", 9);
	srv.add("D", "DA", "D", 1);

	srv.adauga_ret(m1.get_denum());
	assert(srv.get_dim_ret() == 1);
	srv.adauga_ret(m1.get_denum());
	assert(srv.get_dim_ret() == 2);
	assert(srv.get_allR().size() == 2);

	//test adauga_rnd_ret
	srv.adauga_rnd_ret(4);
	assert(srv.get_dim_ret() == 6);
	string fisier{ "test_export" };
	srv.export_ret(fisier);
	srv.goleste_ret();
	assert(srv.get_dim_ret() == 0);
	srv.del("A");
	srv.del("B");
	srv.del("D");
	assert(repo.dim() == 0);
	try {
		srv.adauga_rnd_ret(2);}
	catch (const RepoException& re) {
		assert(re.get_msg() == "Nu exista medicamente de adaugat in reteta!\n");
	}
	
	//test get_dict
	srv.add("A", "A", "A", 5.5);
	srv.add("B", "DA", "B", 9);
	srv.add("D", "DA", "D", 1);
	auto dict = srv.get_dict();
	assert(dict.find("DA")->second.get_nr() == 2);
	assert(dict.find("A")->second.get_nr() == 1);
	srv.del(m1.get_denum());
	srv.del(m2.get_denum());
	srv.del(m3.get_denum());

	//test undo
	srv.add("A", "A", "A", 5.5);
	srv.add("B", "DA", "B", 9);
	assert(repo.get_all().size() == 2);
	srv.undo();
	assert(repo.get_all().size() == 1);
	srv.upd("A", "Z", "Z", 420);
	srv.undo();
	assert(repo.get_all()[0].get_pret() == 5.5);
	srv.del("A");
	srv.undo();
	assert(repo.get_all().size() == 1);

	while (srv.get_dim_undo() >= 1) {
		srv.undo();
	}
	try {
		srv.undo();}
	catch (const UndoException& ue){
		assert(ue.get_msg() == "Nu se poate da undo!\n");
	}
}