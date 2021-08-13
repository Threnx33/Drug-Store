#pragma once
#include "Repo.h"
#include <string>
using std::string;


class ActiuneUndo{
private:
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class AddUndo: public ActiuneUndo {
private:
	Repo& repo;
	string denum;
public:
	AddUndo(Repo& _repo, const string& _denum) :repo{ _repo }, denum{ _denum }{};
	void doUndo() override;
};

class DelUndo : public ActiuneUndo {
private:
	Repo& repo;
	Elem med;
public:
	DelUndo(Repo& _repo, const Elem& _med) :repo{ _repo }, med{ _med }{};
	void doUndo() override;
};

class UpdUndo : public ActiuneUndo {
private:
	Repo& repo;
	Elem med;
public:
	UpdUndo(Repo& _repo, const Elem& _med) :repo{ _repo }, med{ _med }{};
	void doUndo() override;
};

class UndoException {
private:
	string msg;
public:
	UndoException(const string& msg) :msg{ msg } {};
	const string& get_msg() const noexcept;
};


