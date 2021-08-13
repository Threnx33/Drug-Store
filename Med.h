#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;

class Med{
private:
	string denum;
	string produc;
	string subst;
	double pret = 0;
public:
	Med() = default;
	Med(const string& denum, const string& produc, const string& subst, const double pr) : denum{ denum }, produc{ produc }, subst{ subst }, pret{ pr } {};
	Med(const Med& m) : denum{ m.get_denum() }, produc{ m.get_produc() }, subst{ m.get_subst() }, pret{ m.get_pret() } {};

	Med& operator=(const Med& m);
	const string get_denum() const ;
	const string& get_produc() const noexcept;
	const string get_subst() const ;
	const double get_pret() const noexcept;
	void set_denum(const string& _denum);
	void set_produc(const string& _produc);
	void set_subst(const string& _subst);
	void set_pret(const double _pret) noexcept;
	const string stringify() const;
};

class ValidException {
private:
	string msg;
public:
	ValidException(const string& mes) :msg{ mes } {};
	const string& get_msg() const noexcept;
};

class Valid {
private:
public:
	void valid_med(const Med& m);
	void valid_denum(const string& denum);
};