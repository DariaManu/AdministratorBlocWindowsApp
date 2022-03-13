#pragma once
#include <QtWidgets/QWidget>
#include "ServiceLocatari.h"
#include "Locatar.h"
#include "ObserverObservable.h"
#include <vector>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qpushbutton.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>

class GUIListaNotificare : public QWidget, public Observer
{
private:
	ServiceLocatari& service_locatari;
	ListaDeNotificare& lista_de_notificare;

	QListWidget* lista = new QListWidget;
	QLabel* numar_locatari_lista_notificare = new QLabel;

	QSpinBox* spin_numar_apartament_adauga = new QSpinBox;
	QPushButton* buton_adauga = new QPushButton("Adauga");

	QSpinBox* spin_numar_notificati = new QSpinBox;
	QPushButton* buton_genereaza_lista = new QPushButton("Genereaza");

	QLineEdit* text_fisier_export = new QLineEdit;
	QPushButton* buton_export = new QPushButton("Export");

	QPushButton* buton_goleste_lista = new QPushButton("Goleste lista notificare");

	void initialieaza_GUI();
	void initializeaza_conexiuni();
	void incarca_lista_notificare(const std::vector<Locatar> &lista_notificare);

public:
	GUIListaNotificare(ServiceLocatari& service_locatari, ListaDeNotificare& lista_de_notificare) : service_locatari{ service_locatari }, lista_de_notificare{ lista_de_notificare } {
		initialieaza_GUI();
		initializeaza_conexiuni();
		incarca_lista_notificare(service_locatari.get_lista_notificare());
	};

	void update() override {
		incarca_lista_notificare(service_locatari.get_lista_notificare());
	}

};

