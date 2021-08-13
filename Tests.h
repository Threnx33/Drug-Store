#pragma once

class Teste {
private:
	void test_med();
	void test_valid();
	//void test_MyVector();
	void test_dto();
	void test_reteta();
	void test_repo();
	void test_repoF();
	void test_repoL();
	void test_undo();
	void test_srv();
public:
	void test_all();
};

/*void Teste::test_MyVector() {
	MyVector<Med> v;
	v = v;
	Med m1{ "A","B","A",5.5 };
	Med m2{ "B", "DA", "C", 9 };
	Med m3{ "D", "D", "C", 1 };
	Med m4{ "C", "C", "C", 2 };

	v.push(m1);
	v = v;
	assert(v.get_el(0).get_denum() == "A");
	v.set(0, m2);
	assert(v.get_el(0).get_denum() == "B");
	assert(v.size() == 1);

	MyVector<Med> v2(v);
	assert(v2.get_el(0).get_denum() == "B");
	MyVector<Med> v3;
	v3 = v;
	assert(v3.get_el(0).get_denum() == "B");

	v.push(m3);
	for (const auto& it : v) {
		assert(it.get_subst() == "C");
	}
	IVector<Med> it{ v.begin() };
	while (it != v.end()) {
		assert(it.elem().get_subst() == "C");
		++it;
	}
	IVector<Med> it2{ v.begin()+1 };
	assert(it2.elem().get_produc() == "D");

	v.push(m4);
	assert(v.size() == 3);
	v.erase(1);
	assert(v.size() == 2);
	v.erase(1);
	assert(v.size() == 1);
}*/