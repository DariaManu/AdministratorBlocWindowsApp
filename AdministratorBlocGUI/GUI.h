#pragma once
#include "GUIListaNotificare.h"
#include "GUIListaNotificareReadOnly.h"
#include "ServiceLocatari.h"
#include "ListaDeNotificare.h"
#include "Locatar.h"
#include <vector>
#include <QtWidgets/QWidget>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qspinbox.h>
#include <qtablewidget.h>
#include <qlistview.h>
#include <qtableview.h>
#include "MyListModel.h"
#include "MyTableModel.h"
#include <qcombobox.h>

class GUI : public QWidget
{
private:
	ServiceLocatari& service_locatari;
	ListaDeNotificare& lista_de_notificare;
	
	//QListWidget* lista = new QListWidget;
	QListView* lista = new QListView;
	MyListModel* model_lista = new MyListModel{ service_locatari.service_get_lista_locatari() };

	QTableView* tabel = new QTableView;
	MyTableModel* model_tabel = new MyTableModel{ service_locatari.service_get_lista_locatari() };
	
	QPushButton* buton_sorteaza_nume = new QPushButton("Sorteaza dupa nume");
	QPushButton* buton_sorteaza_suprafata = new QPushButton("Sorteaza dupa suprafata");
	QPushButton* buton_sorteaza_tip_suprafata = new QPushButton("Sorteaza dupa tip si suprafata");

	QPushButton* buton_filtreaza_tip = new QPushButton("Filtreaza dupa tip apartament");
	QPushButton* buton_filtreaza_suprafata = new QPushButton("Filtreaza dupa suprafata");
	QLineEdit* text_tip_apartament_filtrare = new QLineEdit;
	QSpinBox* spin_suprafata_filtrare = new QSpinBox;
	QListWidget* lista_filtrare = new QListWidget;

	QSpinBox* spin_numar_apartament_adauga = new QSpinBox;
	QLineEdit* text_nume_adauga = new QLineEdit;
	QSpinBox* spin_suprafata_adauga = new QSpinBox;
	QLineEdit* text_tip_apartament_adauga = new QLineEdit;
	QPushButton* buton_adauga = new QPushButton("Adauga");

	QSpinBox* spin_numar_apartament_modifica_nume = new QSpinBox;
	QLineEdit* text_nume_modifica_nume = new QLineEdit;
	QPushButton* buton_modifica_nume = new QPushButton("Modifica");

	QSpinBox* spin_numar_apartament_modifica_suprafata = new QSpinBox;
	QSpinBox* spin_suprafata_modifica_suprafata = new QSpinBox;
	QPushButton* buton_modifica_suprafata = new QPushButton("Modifica");

	QSpinBox* spin_numar_apartament_modifica_tip_apartament = new QSpinBox;
	QLineEdit* text_tip_apartament_modifica_tip_apartament = new QLineEdit;
	QPushButton* buton_modifica_tip_apartament = new QPushButton("Modifica");

	QSpinBox* spin_numar_aparatament_sterge = new QSpinBox;
	QPushButton* buton_sterge = new QPushButton("Sterge");

	QPushButton* buton_undo = new QPushButton("Undo");

	QPushButton* buton_frecvente = new QPushButton("Frecvente suprafete");
	QListWidget* lista_frecvente = new QListWidget;

	QPushButton* buton_adauga_lista_notificare = new QPushButton("Adauga lista notificare");
	QPushButton* buton_genereaza_lista_notificare = new QPushButton("Genereaza lista notificare");
	QPushButton* buton_goleste_lista_notificare = new QPushButton("Goleste lista notificare");

	QPushButton* buton_lista_notificare = new QPushButton("Lista notificare");
	QPushButton* buton_lista_notificare_read_only = new QPushButton("Lista notificare Read-Only");
	//GUIListaNotificare* gui_lista_notificare = new GUIListaNotificare(service_locatari, lista_de_notificare);

	QComboBox* qbox = new QComboBox;

	/*int nr_linii = 20;
	int nr_coloane = 4;
	QTableWidget* tabel = new QTableWidget{ nr_linii, nr_coloane };
	QTableWidgetItem* numar_apartament = new QTableWidgetItem("Numar apartament");
	QTableWidgetItem* nume_proprietar = new QTableWidgetItem("Nume proprietar");
	QTableWidgetItem* suprafata_apartament = new QTableWidgetItem("Suprafata apartament");
	QTableWidgetItem* tip_apartament = new QTableWidgetItem("Tip apartament");*/

	
	void initializeaza_GUI();
	void initializeaza_conexiuni();
	void incarca_locatari(const std::vector<Locatar> &lista_locatari);
	void incarca_tabel(const std::vector<Locatar>& lista_locatari);

public:
	GUI(ServiceLocatari& service_locatari, ListaDeNotificare& lista_de_notificare) : service_locatari{ service_locatari }, lista_de_notificare{ lista_de_notificare } {
		lista->setModel(model_lista);
		tabel->setModel(model_tabel);
		initializeaza_GUI();
		initializeaza_conexiuni();
		//incarca_locatari(service_locatari.service_get_lista_locatari());
		//incarca_tabel(service_locatari.service_get_lista_locatari());
	};
};

