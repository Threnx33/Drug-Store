#pragma once
#include "GUI.h"
using std::to_string;

void GUI::reload_list(const vector<Elem>& meds) {
	list->clear();
	tabel->clear();
	tabel->setRowCount((int)meds.size());
	int linie = 0;
	for (const Elem& med : meds) {
		/*auto* item = new QListWidgetItem(QString::fromStdString(med.get_denum()));
		item->setData(Qt::UserRole, QString::fromStdString(med.get_produc()));
		list->addItem(QString::fromStdString(med.get_denum()));
		tabel->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(med.get_denum())));*/
		auto item = new QListWidgetItem(QString::fromStdString(med.get_denum()));
		auto item2 = new QTableWidgetItem(QString::fromStdString(med.get_denum()));
		list->addItem(item);
		tabel->setItem(linie, 0, item2);
		linie++;
	}
}

void GUI::reload_list_filtrate(const vector<Elem>& meds, const vector<Elem>& filtrate) {
	list->clear();
	tabel->clear();
	tabel->setRowCount((int)meds.size());
	int linie = 0;
	for (const Elem& med : meds) {
		auto item = new QListWidgetItem(QString::fromStdString(med.get_denum()));
		auto item2 = new QTableWidgetItem(QString::fromStdString(med.get_denum()));
		for (const auto& med2 : filtrate) {
			if (med2.get_denum() == med.get_denum()) {
				item->setData(Qt::BackgroundRole, QBrush{ Qt::green });
				item2->setData(Qt::BackgroundRole, QBrush{ Qt::green });
				break;
			}
		}
		list->addItem(item);
		tabel->setItem(linie, 0, item2);
		linie++;
	}
}

void GUI::reload_listR(const vector<Elem>& meds) {
	listR->clear();
	for (const Elem& med : meds) {
		listR->addItem(QString::fromStdString(med.get_denum()));
	}
}

void GUI::add() {
	try {
		srv.add(txt_denum->text().toStdString(), txt_produc->text().toStdString(), txt_subst->text().toStdString(), txt_pret->text().toDouble());
		reload_list(srv.get_all());
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "RepoError", QString::fromStdString(re.get_msg()));
	}
	catch (const ValidException& ve) {
		QMessageBox::warning(this, "ValidError", QString::fromStdString(ve.get_msg()));
	}
}

void GUI::upd() {
	try {
		srv.upd(txt_denum->text().toStdString(), txt_produc->text().toStdString(), txt_subst->text().toStdString(), txt_pret->text().toDouble());
		reload_list(srv.get_all());
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "RepoError", QString::fromStdString(re.get_msg()));
	}
	catch (const ValidException& ve) {
		QMessageBox::warning(this, "ValidError", QString::fromStdString(ve.get_msg()));
	}
}

void GUI::src() {
	try {
		auto med = srv.search(txt_denum->text().toStdString());
		QMessageBox::information(this, "Medicament gasit", QString::fromStdString(med.stringify()));
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "RepoError", QString::fromStdString(re.get_msg()));
	}
	catch (const ValidException& ve) {
		QMessageBox::warning(this, "ValidError", QString::fromStdString(ve.get_msg()));
	}
}

void GUI::exit() {
	//QMessageBox::information(nullptr, "Info", "Ai iesit");
	close();
}

void GUI::select() {
	auto sel = list->selectedItems();
	if (sel.isEmpty()) {
		txt_denum->setText("");
		txt_produc->setText("");
		txt_subst->setText("");
		txt_pret->setText("");
	}
	else {
		const auto& denum = sel.at(0)->text().toStdString();
		auto& med = srv.search(denum);
		txt_denum->setText(QString::fromStdString(med.get_denum()));
		txt_produc->setText(QString::fromStdString(med.get_produc()));
		txt_subst->setText(QString::fromStdString(med.get_subst()));
		txt_pret->setText(QString::fromStdString(to_string(med.get_pret())));
	}
}

void GUI::select2() {
	auto sel = tabel->selectedItems();
	if (sel.isEmpty()) {
		txt_denum->setText("");
		txt_produc->setText("");
		txt_subst->setText("");
		txt_pret->setText("");
	}
	else {
		const auto& denum = sel.at(0)->text().toStdString();
		auto& med = srv.search(denum);
		txt_denum->setText(QString::fromStdString(med.get_denum()));
		txt_produc->setText(QString::fromStdString(med.get_produc()));
		txt_subst->setText(QString::fromStdString(med.get_subst()));
		txt_pret->setText(QString::fromStdString(to_string(med.get_pret())));
	}
}

void GUI::selectR() {
	auto sel = listR->selectedItems();
	if (sel.isEmpty()) {
		txt_denumR->setText("");
	}
	else {
		const auto& denum = sel.at(0)->text().toStdString();
		txt_denumR->setText(QString::fromStdString(denum));
	}
}

void GUI::afis(const vector<Elem>& meds) {
	string s;
	for (const auto& med : meds) {
		s += med.stringify() + '\n';
	}
	if (s.empty()) {
		QMessageBox::information(this, "Medicamente", "Niciun medicament");
	}
	else {
		s.pop_back();
		QMessageBox::information(this, "Medicamente", QString::fromStdString(s));
	}
}

void GUI::flt_subst(){
	const auto& meds = srv.filtrare_subst(txt_subst->text().toStdString());
	reload_list_filtrate(srv.get_all(), meds);
	afis(meds);
}

void GUI::flt_pret() {
	const auto& meds = srv.filtrare_pret(txt_pret->text().toDouble());
	afis(meds);
}

void GUI::del() {
	try {
		srv.del(txt_denum->text().toStdString());
		reload_list(srv.get_all());
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "RepoError", QString::fromStdString(re.get_msg()));
	}
	catch (const ValidException& ve) {
		QMessageBox::warning(this, "ValidError", QString::fromStdString(ve.get_msg()));
	}
}

void GUI::srt_denum() {
	const auto& meds = srv.sort_denum();
	afis(meds);
}

void GUI::srt_produc() {
	const auto& meds = srv.sort_produc();
	afis(meds);
}

void GUI::srt_subst_pret() {
	const auto& meds = srv.sort_substPret();
	afis(meds);
}

void GUI::undo() {
	try {
		srv.undo();
		reload_list(srv.get_all());
	}
	catch (const UndoException& ue) {
		QMessageBox::warning(this,"UndoException",QString::fromStdString(ue.get_msg()));
	}
}

void GUI::openR() {
	if (windowR == 1) {
		QMessageBox::information(this, "Window", "Window deschis deja!");
		return;
	}
	windowR = 1;
	wr->show();
}

void GUI::exitR() {
	windowR = 0;
	//QMessageBox::information(nullptr, "Info", "Ai inchis");
	wr->close();
}

void GUI::addR() {
	try {
		srv.adauga_ret(txt_denumR->text().toStdString());
		reload_listR(srv.get_allR());
	}
	catch (const RepoException& re) {
		QMessageBox::warning(wr, "RepoError", QString::fromStdString(re.get_msg()));
	}
	catch (const ValidException& ve) {
		QMessageBox::warning(wr, "ValidError", QString::fromStdString(ve.get_msg()));
	}
}

void GUI::addRRnd() {
	try {
		srv.adauga_rnd_ret(txt_nrR->text().toDouble());
		reload_listR(srv.get_allR());
	}
	catch (const RepoException& re) {
		QMessageBox::warning(wr, "RepoError", QString::fromStdString(re.get_msg()));
	}
}

void GUI::exportR() {
	auto file = txt_fileR->text().toStdString();
	srv.export_ret(file);
}

void GUI::goleste() {
	srv.goleste_ret();
	reload_listR(srv.get_allR());
}

void GUI::upd_slide() {
	txt_pret->setText(QString::fromStdString(to_string(slider->value())));
}

void GUI::init_butoane() {
	QObject::connect(b_exit, &QPushButton::clicked, this, &GUI::exit);
	QObject::connect(b_add, &QPushButton::clicked, this, &GUI::add);
	QObject::connect(b_upd, &QPushButton::clicked, this, &GUI::upd);
	QObject::connect(b_src, &QPushButton::clicked, this, &GUI::src);
	QObject::connect(b_del, &QPushButton::clicked, this, &GUI::del);
	QObject::connect(b_undo, &QPushButton::clicked, this, &GUI::undo);
	QObject::connect(b_flt_subst, &QPushButton::clicked, this, &GUI::flt_subst);
	QObject::connect(b_flt_pret, &QPushButton::clicked, this, &GUI::flt_pret);
	QObject::connect(b_srt_denum, &QPushButton::clicked, this, &GUI::srt_denum);
	QObject::connect(b_srt_produc, &QPushButton::clicked, this, &GUI::srt_produc);
	QObject::connect(b_srt_subst_pret, &QPushButton::clicked, this, &GUI::srt_subst_pret);
	QObject::connect(list, &QListWidget::itemSelectionChanged, this, &GUI::select);
	QObject::connect(tabel, &QTableWidget::itemSelectionChanged, this, &GUI::select2);
	QObject::connect(listR, &QListWidget::itemSelectionChanged, this, &GUI::selectR);
	QObject::connect(b_openR, &QPushButton::clicked, this, &GUI::openR);
	QObject::connect(b_exitR, &QPushButton::clicked, this, &GUI::exitR);
	QObject::connect(b_addR, &QPushButton::clicked, this, &GUI::addR);
	QObject::connect(b_addRRnd, &QPushButton::clicked, this, &GUI::addRRnd);
	QObject::connect(b_export, &QPushButton::clicked, this, &GUI::exportR);
	QObject::connect(b_goleste, &QPushButton::clicked, this, &GUI::goleste);
	QObject::connect(slider, &QSlider::valueChanged, this, &GUI::upd_slide);
}

void GUI::load() {
	const auto meds = srv.get_all();
	auto linie = 0;
	for (const auto& med : meds) {
		list->addItem(QString::fromStdString(med.get_denum()));
		tabel->setRowCount(tabel->rowCount() + 1);
		tabel->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(med.get_denum())));
		linie++;
	}
}

void GUI::init() {
	QHBoxLayout* laymain = new QHBoxLayout;
	setLayout(laymain);

	QVBoxLayout* lay_st = new QVBoxLayout;
	lay_st->addWidget(list);
	QHBoxLayout* lay_st_jos = new QHBoxLayout;
	lay_st_jos->addWidget(b_srt_denum);
	lay_st_jos->addWidget(b_srt_produc);
	lay_st_jos->addWidget(b_srt_subst_pret);
	lay_st->addLayout(lay_st_jos);
	laymain->addLayout(lay_st);

	//formular
	QVBoxLayout* lay_dr = new QVBoxLayout;
	auto* formly = new QFormLayout;
	formly->addRow("Denum: ", txt_denum);
	formly->addRow("Produc: ", txt_produc);
	formly->addRow("Subst: ", txt_subst);
	formly->addRow("Pret: ", txt_pret);
	lay_dr->addLayout(formly);

	//slider
	//QHBoxLayout* lay_slider = new QHBoxLayout;
	slider->setMinimum(0);
	slider->setMaximum(9999);
	lay_dr->addWidget(slider);
	//lay_slider->addWidget(slider);
	lay_dr->addStretch();

	//Open reteta
	auto layOpen = new QHBoxLayout;
	lay_dr->addLayout(layOpen);
	layOpen->addStretch();
	layOpen->addWidget(b_openR);

	//Butoane
	auto lb = new QHBoxLayout{};
	lb->addWidget(b_add);
	lb->addWidget(b_upd);
	lb->addWidget(b_src);
	lb->addWidget(b_del);
	lb->addWidget(b_undo);
	lay_dr->addLayout(lb);

	auto lb2 = new QHBoxLayout{};
	lb2->addWidget(b_flt_subst);
	lb2->addWidget(b_flt_pret);
	lb2->addWidget(b_exit);
	lay_dr->addLayout(lb2);

	laymain->addLayout(lay_dr);
	laymain->addWidget(tabel);


	//Widget reteta
	wr = new QWidget;
	QHBoxLayout* rLay_main = new QHBoxLayout;
	wr->setLayout(rLay_main);
	
	rLay_main->addWidget(listR);
	QVBoxLayout* rLay_dr = new QVBoxLayout;
	QHBoxLayout* rLay_dr1 = new QHBoxLayout;
	QHBoxLayout* rLay_dr2 = new QHBoxLayout;
	QHBoxLayout* rLay_dr3 = new QHBoxLayout;
	QHBoxLayout* rLay_dr4 = new QHBoxLayout;
	rLay_main->addLayout(rLay_dr);
	rLay_dr->addLayout(rLay_dr1);
	rLay_dr->addLayout(rLay_dr2);
	rLay_dr->addLayout(rLay_dr3);
	rLay_dr->addLayout(rLay_dr4);

	auto formlyR1 = new QFormLayout;
	formlyR1->addRow("Denum: ", txt_denumR);
	rLay_dr1->addLayout(formlyR1);
	rLay_dr1->addWidget(b_addR);
	auto formlyR2 = new QFormLayout;
	formlyR2->addRow("Nr: ", txt_nrR);
	rLay_dr2->addLayout(formlyR2);
	rLay_dr2->addWidget(b_addRRnd);
	auto formlyR3 = new QFormLayout;
	formlyR3->addRow("File: ", txt_fileR);
	rLay_dr3->addLayout(formlyR3);
	rLay_dr3->addWidget(b_export);
	rLay_dr4->addWidget(b_goleste);
	rLay_dr4->addWidget(b_exitR);
}