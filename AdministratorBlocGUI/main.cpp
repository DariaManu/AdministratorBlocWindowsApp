/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/
#include <QtWidgets/QApplication>
#include <qcombobox.h>

#include "Teste.h"
#include "RepoLocatari.h"
#include "ServiceLocatari.h"
#include "ListaDeNotificare.h"
#include "UI.h"
#include "VectorDinamic.h"
#include "Locatar.h"
#include "FileRepoLocatari.h"
#include "RepoLab.h"
#include "GUI.h"
#include "FakeRepository.h"

//adauga cativa locatari in lista (optional)
void adauga_niste_locatari(ServiceLocatari &service_locatari)
{
	service_locatari.service_adauga_locatar(12, "b", 1000, "airbnb");
	service_locatari.service_adauga_locatar(13, "d", 1001, "sky");
	service_locatari.service_adauga_locatar(10, "c", 1001, "penthouse");
	service_locatari.service_adauga_locatar(11, "a", 1000, "penthouse");
}


int main(int argc, char* argv[])
{
	//ruleaza_toate_testele();

	{
		QApplication app(argc, argv);

		FileRepoLocatari file_repo_locatari("locatari.txt");
		ListaDeNotificare lista_de_notificare{ file_repo_locatari };
		Validare validator;
		ServiceLocatari service_locatari{ file_repo_locatari, validator, lista_de_notificare };


		GUI gui{ service_locatari, lista_de_notificare };
		gui.show();

		return app.exec();
	}

}