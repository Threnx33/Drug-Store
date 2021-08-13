/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/
#include "GUI.h"
#include "UI.h"
#include "Tests.h"
#include <vector>
#include <string>
using std::cin;
using std::string;
using std::vector;

//int argc, char* argv[]
int main(int argc, char* argv[])
{
	Teste t;
	t.test_all();

	Valid v;
	//RepoM repo{};
	RepoF repo{ "gintonic.txt" };
	Reteta reteta{ repo };
	Srv srv{ repo, v, reteta };
	//UI ui{ srv };
	//ui.run();

	QApplication a(argc, argv);
	GUI gui{srv};
	gui.show();
	return a.exec();

	/*{
		Valid v;
		cout << "Rulare program(0-In memory, 1-In files, 2-Cu boolaneala): ";
		int tip;
		cin >> tip;
		if (tip == 0) {
			RepoM repo{};
			Reteta reteta{ repo };
			Srv srv{ repo, v, reteta };
			UI ui{ srv };
			ui.run();
		}
		else if (tip == 1) {
			RepoF repo{ "gintonic.txt" };
			Reteta reteta{ repo };
			Srv srv{ repo, v, reteta };
			UI ui{ srv };
			ui.run();
		}
		else if (tip == 2) {
			RepoL repo{ 0.40 };
			Reteta reteta{ repo };
			Srv srv{ repo, v, reteta };
			UI ui{ srv };
			ui.run();
		}
		else {
			cout << "Valoare incorecta";
		}
	}
	_CrtDumpMemoryLeaks();*/
}