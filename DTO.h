#pragma once
#include <string>
using std::string;

class DTO {
private:
	string produc;
	int nr;
public:
	DTO() = default;
	DTO(const string& p) :produc{ p }, nr{ 1 } {};
	const string& get_produc() noexcept;
	int get_nr() noexcept;
	void incr() noexcept;
};
