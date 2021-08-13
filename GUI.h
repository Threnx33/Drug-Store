#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qtablewidget.h>
#include <qbrush.h>
#include <qslider.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <string>
#include <vector>
#include "Srv.h"

using std::string;
using std::vector;

class GUI : public QWidget {
private:
	Srv& srv;
	QWidget* wr;
	int windowR;
	QSlider* slider = new QSlider(Qt::Horizontal);
	QListWidget* list = new QListWidget;
	QListWidget* listR = new QListWidget; 
	QTableWidget* tabel = new QTableWidget{ 0, 1 };
	QLineEdit* txt_denum = new QLineEdit;
	QLineEdit* txt_produc = new QLineEdit;
	QLineEdit* txt_subst = new QLineEdit;
	QLineEdit* txt_pret = new QLineEdit;
	QLineEdit* txt_denumR = new QLineEdit;
	QLineEdit* txt_nrR = new QLineEdit;
	QLineEdit* txt_fileR = new QLineEdit;
	QPushButton* b_add = new QPushButton{ "Add" };
	QPushButton* b_upd = new QPushButton{ "Upd" };
	QPushButton* b_src = new QPushButton{ "Src" };
	QPushButton* b_del = new QPushButton{ "Del" };
	QPushButton* b_flt_subst = new QPushButton{ "FltSubst" };
	QPushButton* b_flt_pret = new QPushButton{ "FltPret" };
	QPushButton* b_srt_denum = new QPushButton{ "SrtDenum" };
	QPushButton* b_srt_produc = new QPushButton{ "SrtProduc" };
	QPushButton* b_srt_subst_pret = new QPushButton{ "SrtSubstPret" };
	QPushButton* b_undo = new QPushButton{ "Undo" };
	QPushButton* b_exit = new QPushButton{"Exit"};
	QPushButton* b_openR = new QPushButton{ "OpenR" };
	QPushButton* b_addR = new QPushButton{ "Add" };
	QPushButton* b_addRRnd = new QPushButton{ "AddRnd" };
	QPushButton* b_export = new QPushButton{ "Export" };
	QPushButton* b_goleste = new QPushButton{ "Goleste" };
	QPushButton* b_exitR = new QPushButton{ "Exit" };

	void add();
	void upd();
	void src();
	void del();
	void flt_subst();
	void flt_pret();
	void srt_denum();
	void srt_produc();
	void srt_subst_pret();
	void openR();
	void undo();
	void exit();
	void select();
	void select2();
	void selectR();
	void addR();
	void addRRnd();
	void exportR();
	void goleste();
	void upd_slide();
	void exitR();
	void afis(const vector<Elem>& meds);
	void reload_list(const vector<Elem>& meds);
	void reload_list_filtrate(const vector<Elem>& meds, const vector<Elem>& filtrate);
	void reload_listR(const vector<Elem>& meds);
	void init();
	void load();
	void init_butoane();
public:
	GUI(Srv& _srv) :srv{ _srv }, windowR{ 0 } {
		init();
		load();
		init_butoane();
	}
};