#include "Undo.h"

const string& UndoException::get_msg() const noexcept {
	return msg;
}

void AddUndo::doUndo() {
	repo.del(denum);
}

void DelUndo::doUndo() {
	repo.add(med);
}

void UpdUndo::doUndo() {
	repo.upd(med);
}
