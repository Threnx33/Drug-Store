#pragma once
#include "Med.h"
#include <vector>
#include <string>
#include <map>
using std::string;
using std::map;
using std::vector;

typedef Med Elem;

class Repo {
private:
	vector<Elem> meds;
public:
	Repo() = default;
	virtual ~Repo() = default;

	virtual size_t dim() = 0;
	virtual void add(const Elem& m) = 0;
	virtual Elem upd(const Elem& m) = 0;
	virtual const Elem& search(const string& denum) = 0;
	virtual Elem del(const string& denum) = 0;
	virtual vector<Elem>& get_all() = 0;
};

class RepoL: public Repo {
private:
	map<string, Elem> meds;
	vector<Elem> v;
	double p;
	double boolaneala() const;
public:
	RepoL(double _p) :p{ _p } {  };
	~RepoL() = default;

	size_t dim() noexcept  override;
	virtual void add(const Elem& m) override;
	virtual Elem upd(const Elem& m) override;
	const Elem& search(const string& denum) override;
	virtual Elem del(const string& denum) override;
	vector<Elem>& get_all() override;
};

class RepoM:public Repo {
private:
	vector<Elem> meds;
public:
	RepoM() = default;
	RepoM(const RepoM& r) = delete;
	virtual ~RepoM()=default;

	size_t dim() noexcept  override;
	virtual void add(const Elem& m) override;
	virtual Elem upd(const Elem& m) override;
	const Elem& search(const string& denum) override;
	virtual Elem del(const string& denum) override;
	vector<Elem>& get_all() noexcept override;
};

class RepoF : public RepoM {
private:
	string file;
	void load();
	void write();
public:
	RepoF() = delete;
	RepoF(const string& _file) :RepoM(), file{ _file } { load(); };
	RepoF(const RepoF& r) = delete;
	~RepoF() = default;

	void add(const Elem& m) override;
	Elem upd(const Elem& m) override;
	Elem del(const string& denum) override;
};

class RepoException {
private:
	string msg;
public:
	RepoException(const string& msg) :msg{ msg } {};
	const string& get_msg() const noexcept;
};