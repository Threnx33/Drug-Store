#include "DTO.h"

const string& DTO::get_produc() noexcept {
	return produc;
}

int DTO::get_nr() noexcept {
	return nr;
}

void DTO::incr() noexcept {
	nr++;
}