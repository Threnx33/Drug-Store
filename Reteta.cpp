#include "Reteta.h"
#include <random>
#include <fstream>
using std::mt19937;
using std::ofstream;
using std::uniform_int_distribution;
using std::random_device;

void Reteta::goleste_ret() noexcept {
	while (!reteta.empty()) {
		reteta.pop_back();
	}
}

void Reteta::adauga_ret(const string& denum) {
	const Elem& med = repo.search(denum);
	reteta.push_back(med);
}

void Reteta::adauga_rnd_ret(int nr) {
	if (repo.dim() == 0) {
		throw RepoException("Nu exista medicamente de adaugat in reteta!\n");
	}
	auto& meds = repo.get_all();
	mt19937 generator{ random_device{}() };
	const uniform_int_distribution<size_t> dist(0, repo.dim() - 1);
	for (; nr > 0; nr--) {
		const size_t rndNr = dist(generator);
		reteta.push_back(meds[rndNr]);
	}
}

void Reteta::export_ret(string& fisier) {
	fisier += ".csv";
	ofstream fout(fisier);
	for (auto& med : reteta) {
		fout << med.stringify() << '\n';
	}
}

size_t Reteta::get_dim_ret() noexcept {
	return reteta.size();
}

vector<Elem>& Reteta::get_allR() {
	return reteta;
}