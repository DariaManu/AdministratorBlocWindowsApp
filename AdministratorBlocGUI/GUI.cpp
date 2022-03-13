#include "GUI.h"
#include "GUIListaNotificare.h"
#include "Locatar.h"
#include "Validare.h"
#include "RepoLocatari.h"
#include <vector>
#include <map>
#include <qboxlayout.h>
#include <qgroupbox.h>
#include <qformlayout.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qabstractitemmodel>

void GUI::initializeaza_GUI()
{
	QHBoxLayout* layout_principal = new QHBoxLayout;
	setLayout(layout_principal);

	QGroupBox* grup_lista = new QGroupBox("Lista locatari");
	QVBoxLayout* layout_grup_lista = new QVBoxLayout;
	grup_lista->setLayout(layout_grup_lista);
	layout_grup_lista->addWidget(tabel);
	layout_grup_lista->addWidget(lista);

	QGridLayout* layout_grid = new QGridLayout;
	layout_grid->addWidget(buton_sorteaza_nume, 0, 0);
	layout_grid->addWidget(buton_sorteaza_suprafata, 0, 1);
	layout_grid->addWidget(buton_sorteaza_tip_suprafata, 1, 0, 1, 2);
	layout_grup_lista->addLayout(layout_grid);

	QGroupBox* grup_filtrare1 = new QGroupBox("Filtrare dupa tip apartament");
	QFormLayout* form_layout_grup_filtrare1 = new QFormLayout;
	grup_filtrare1->setLayout(form_layout_grup_filtrare1);
	form_layout_grup_filtrare1->addRow("Tip apartament", text_tip_apartament_filtrare);
	form_layout_grup_filtrare1->addWidget(buton_filtreaza_tip);

	QGroupBox* grup_filtrare2 = new QGroupBox("Filtrare dupa suprafata");
	QFormLayout* form_layout_grup_filtrare2 = new QFormLayout;
	grup_filtrare2->setLayout(form_layout_grup_filtrare2);
	spin_suprafata_filtrare->setRange(1, 100000);
	spin_suprafata_filtrare->setSingleStep(1);
	form_layout_grup_filtrare2->addRow("Suprafata", spin_suprafata_filtrare);
	form_layout_grup_filtrare2->addWidget(buton_filtreaza_suprafata);

	layout_grid->addWidget(grup_filtrare1, 2, 0);
	layout_grid->addWidget(grup_filtrare2, 2, 1);
	
	layout_principal->addWidget(grup_lista);

	QGroupBox* grup_actualizari = new QGroupBox("Actualizari");
	QVBoxLayout* layout_grup_actualizari = new QVBoxLayout;
	grup_actualizari->setLayout(layout_grup_actualizari);
	layout_principal->addWidget(grup_actualizari);

	QGridLayout* grid_layout_actualizari = new QGridLayout;
	layout_grup_actualizari->addLayout(grid_layout_actualizari);

	QGroupBox* grup_adauga = new QGroupBox("Adauga locatar");
	QFormLayout* form_layout_grup_adauga = new QFormLayout;
	grup_adauga->setLayout(form_layout_grup_adauga);
	spin_numar_apartament_adauga->setRange(1, 100000);
	spin_numar_apartament_adauga->setSingleStep(1);
	spin_suprafata_adauga->setRange(1, 100000);
	spin_suprafata_adauga->setSingleStep(1);
	form_layout_grup_adauga->addRow("Numar apartament", spin_numar_apartament_adauga);
	form_layout_grup_adauga->addRow("Nume proprietar", text_nume_adauga);
	form_layout_grup_adauga->addRow("Suprafata apartament", spin_suprafata_adauga);
	form_layout_grup_adauga->addRow("Tip apartament", text_tip_apartament_adauga);
	form_layout_grup_adauga->addWidget(buton_adauga);
	grid_layout_actualizari->addWidget(grup_adauga, 0, 0);

	QGroupBox* grup_modifica_nume = new QGroupBox("Modifica nume proprietar");
	QFormLayout* form_layout_grup_modifica_nume = new QFormLayout;
	grup_modifica_nume->setLayout(form_layout_grup_modifica_nume);
	spin_numar_apartament_modifica_nume->setRange(1, 100000);
	spin_numar_apartament_modifica_nume->setSingleStep(1);
	form_layout_grup_modifica_nume->addRow("Numar apartament", spin_numar_apartament_modifica_nume);
	form_layout_grup_modifica_nume->addRow("Nume proprietar", text_nume_modifica_nume);
	form_layout_grup_modifica_nume->addWidget(buton_modifica_nume);
	grid_layout_actualizari->addWidget(grup_modifica_nume, 0, 1);

	QGroupBox* grup_modifica_suprafata = new QGroupBox("Modifica suprafata apartament");
	QFormLayout* form_layout_grup_modifica_suprafata = new QFormLayout;
	grup_modifica_suprafata->setLayout(form_layout_grup_modifica_suprafata);
	spin_numar_apartament_modifica_suprafata->setRange(1, 100000);
	spin_numar_apartament_modifica_suprafata->setSingleStep(1);
	spin_suprafata_modifica_suprafata->setRange(1, 100000);
	spin_suprafata_modifica_suprafata->setSingleStep(1);
	form_layout_grup_modifica_suprafata->addRow("Numar apartament", spin_numar_apartament_modifica_suprafata);
	form_layout_grup_modifica_suprafata->addRow("Suprafata apartament", spin_suprafata_modifica_suprafata);
	form_layout_grup_modifica_suprafata->addWidget(buton_modifica_suprafata);
	grid_layout_actualizari->addWidget(grup_modifica_suprafata, 1, 0);

	QGroupBox* grup_modifica_tip_apartament = new QGroupBox("Modifica tip apartament");
	QFormLayout* form_layout_grup_modifica_tip_apartament = new QFormLayout;
	grup_modifica_tip_apartament->setLayout(form_layout_grup_modifica_tip_apartament);
	spin_numar_apartament_modifica_tip_apartament->setRange(1, 100000);
	spin_numar_apartament_modifica_tip_apartament->setSingleStep(1);
	form_layout_grup_modifica_tip_apartament->addRow("Numar apartament", spin_numar_apartament_modifica_tip_apartament);
	form_layout_grup_modifica_tip_apartament->addRow("Tip apartament", text_tip_apartament_modifica_tip_apartament);
	form_layout_grup_modifica_tip_apartament->addWidget(buton_modifica_tip_apartament);
	grid_layout_actualizari->addWidget(grup_modifica_tip_apartament, 1, 1);

	QGroupBox* grup_sterge = new QGroupBox("Sterge");
	QFormLayout* form_layout_sterge = new QFormLayout;
	grup_sterge->setLayout(form_layout_sterge);
	spin_numar_aparatament_sterge->setRange(1, 100000);
	spin_numar_aparatament_sterge->setSingleStep(1);
	form_layout_sterge->addRow("Numar apartament", spin_numar_aparatament_sterge);
	form_layout_sterge->addWidget(buton_sterge);
	layout_grup_actualizari->addWidget(grup_sterge);

	layout_grup_actualizari->addWidget(buton_undo);

	layout_grup_actualizari->addWidget(buton_frecvente);

	layout_grup_actualizari->addWidget(buton_adauga_lista_notificare);
	layout_grup_actualizari->addWidget(buton_genereaza_lista_notificare);
	layout_grup_actualizari->addWidget(buton_goleste_lista_notificare);
	layout_grup_actualizari->addWidget(buton_lista_notificare);
	layout_grup_actualizari->addWidget(buton_lista_notificare_read_only);
	qbox->addItem("ceva");
	qbox->addItem("ceva2");
	layout_grup_actualizari->addWidget(qbox);

}

void GUI::initializeaza_conexiuni()
{
	QObject::connect(qbox, &QComboBox::currentTextChanged, this, [&]() {
		//qDebug() << "semnal!";
		auto selectat = qbox->currentText();
		qDebug() << selectat;
		});

	QObject::connect(buton_adauga, &QPushButton::clicked, this, [&]() {
		int numar_apartament = spin_numar_apartament_adauga->value();
		auto nume_proprietar = text_nume_adauga->text();
		int suprafata = spin_suprafata_adauga->value();
		auto tip_apartament = text_tip_apartament_adauga->text();
		try {
			service_locatari.service_adauga_locatar(numar_apartament, nume_proprietar.toStdString(), suprafata, tip_apartament.toStdString());
			incarca_locatari(service_locatari.service_get_lista_locatari());
			incarca_tabel(service_locatari.service_get_lista_locatari());
		}
		catch (const ExceptieValidare& exceptie_validare) {
			QMessageBox::warning(nullptr, "Exceptie Validare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieRepo& exceptie_repo) {
			QMessageBox::warning(nullptr, "Exceptie Repo", QString::fromStdString(exceptie_repo.get_mesaj()));
		}
		});


	QObject::connect(buton_modifica_nume, &QPushButton::clicked, this, [&]() {
		int numar_apartament = spin_numar_apartament_modifica_nume->value();
		auto nume_nou = text_nume_modifica_nume->text();
		try {
			service_locatari.service_modifica_nume_proprietar(numar_apartament, nume_nou.toStdString());
			incarca_locatari(service_locatari.service_get_lista_locatari());
			incarca_tabel(service_locatari.service_get_lista_locatari());
		}
		catch (const ExceptieValidare& exceptie_validare) {
			QMessageBox::warning(nullptr, "Exceptie Validare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieRepo& exceptie_repo) {
			QMessageBox::warning(nullptr, "Exceptie Repo", QString::fromStdString(exceptie_repo.get_mesaj()));
		}
		});


	QObject::connect(buton_modifica_suprafata, &QPushButton::clicked, this, [&]() {
		int numar_apartament = spin_numar_apartament_modifica_suprafata->value();
		int suprafata_noua = spin_suprafata_modifica_suprafata->value();
		try {
			service_locatari.service_modifica_suprafata_apartament(numar_apartament, suprafata_noua);
			incarca_locatari(service_locatari.service_get_lista_locatari());
			incarca_tabel(service_locatari.service_get_lista_locatari());
		}
		catch (const ExceptieValidare& exceptie_validare) {
			QMessageBox::warning(nullptr, "Exceptie Validare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieRepo& exceptie_repo) {
			QMessageBox::warning(nullptr, "Exceptie Repo", QString::fromStdString(exceptie_repo.get_mesaj()));
		}
		});


	QObject::connect(buton_modifica_tip_apartament, &QPushButton::clicked, this, [&]() {
		int numar_aparatament = spin_numar_apartament_modifica_tip_apartament->value();
		auto tip_nou = text_tip_apartament_modifica_tip_apartament->text();
		try {
			service_locatari.service_modifica_tip_apartament(numar_aparatament, tip_nou.toStdString());
			incarca_locatari(service_locatari.service_get_lista_locatari());
			incarca_tabel(service_locatari.service_get_lista_locatari());
		}
		catch (const ExceptieValidare& exceptie_validare) {
			QMessageBox::warning(nullptr, "Exceptie Validare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieRepo& exceptie_repo) {
			QMessageBox::warning(nullptr, "Exceptie Repo", QString::fromStdString(exceptie_repo.get_mesaj()));
		}
		});


	QObject::connect(buton_sterge, &QPushButton::clicked, this, [&]() {
		int numar_apartament = spin_numar_aparatament_sterge->value();
		try {
			service_locatari.service_sterge_locatar(numar_apartament);
			incarca_locatari(service_locatari.service_get_lista_locatari());
			incarca_tabel(service_locatari.service_get_lista_locatari());
		}
		catch (const ExceptieValidare& exceptie_validare) {
			QMessageBox::warning(nullptr, "Exceptie Validare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieRepo& exceptie_repo) {
			QMessageBox::warning(nullptr, "Exceptie Repo", QString::fromStdString(exceptie_repo.get_mesaj()));
		}
		});


	QObject::connect(buton_undo, &QPushButton::clicked, this, [&]() {
		try {
			service_locatari.undo();
			incarca_locatari(service_locatari.service_get_lista_locatari());
			incarca_tabel(service_locatari.service_get_lista_locatari());
		}
		catch (const ExceptieService& exceptie_service) {
			QMessageBox::warning(nullptr, "Exceptie Undo", QString::fromStdString(exceptie_service.get_mesaj()));
		}
		});


	QObject::connect(buton_sorteaza_nume, &QPushButton::clicked, this, [&]() {
		auto lista_sortata = service_locatari.service_get_lista_locatari();
		service_locatari.sortare_nume(lista_sortata);
		incarca_locatari(lista_sortata);
		incarca_tabel(lista_sortata);
		});

	QObject::connect(buton_sorteaza_suprafata, &QPushButton::clicked, this, [&]() {
		auto lista_sortata = service_locatari.service_get_lista_locatari();
		service_locatari.sortare(lista_sortata);
		incarca_locatari(lista_sortata);
		incarca_tabel(lista_sortata);
		});

	QObject::connect(buton_sorteaza_tip_suprafata, &QPushButton::clicked, this, [&]() {
		auto lista_sortata = service_locatari.service_get_lista_locatari();
		service_locatari.sortare_tip_suprafata(lista_sortata);
		incarca_locatari(lista_sortata);
		incarca_tabel(lista_sortata);
		});


	QObject::connect(buton_filtreaza_tip, &QPushButton::clicked, this, [&]() {
		auto tip_apartament = text_tip_apartament_filtrare->text();
		std::vector<Locatar> lista_locatari_filtrare;
		service_locatari.service_filtrare_dupa_tip_apartament(lista_locatari_filtrare, tip_apartament.toStdString());
		if (lista_locatari_filtrare.size() == 0)
		{
			QMessageBox::information(nullptr, "Info filtrare", "Nu exista apartamente cu tipul specificat.");
		}
		else
		{
			lista_filtrare->clear();
			for (const auto& locatar : lista_locatari_filtrare)
			{
				QString numar_apartament;
				numar_apartament.setNum(locatar.get_numar_apartament());
				QString suprafata;
				suprafata.setNum(locatar.get_suprafata());
				lista_filtrare->addItem(numar_apartament + " " + QString::fromStdString(locatar.get_nume_proprietar()) + " " + suprafata + " " + QString::fromStdString(locatar.get_tip_apartament()));
			}
			lista_filtrare->show();
		}
		});


	QObject::connect(buton_filtreaza_suprafata, &QPushButton::clicked, this, [&]() {
		int suprafata = spin_suprafata_filtrare->value();
		std::vector<Locatar> lista_locatari_filtrare;
		service_locatari.service_filtrare_dupa_suprafata(lista_locatari_filtrare, suprafata);
		if (lista_locatari_filtrare.size() == 0)
		{
			QMessageBox::information(nullptr, "Info filtrare", "Nu exista apartamente cu suprafata mai mica decat cea data.");
		}
		else
		{	
			lista_filtrare->clear();
			for (const auto& locatar : lista_locatari_filtrare)
			{
				QString numar_apartament;
				numar_apartament.setNum(locatar.get_numar_apartament());
				QString suprafata;
				suprafata.setNum(locatar.get_suprafata());
				lista_filtrare->addItem(numar_apartament + " " + QString::fromStdString(locatar.get_nume_proprietar()) + " " + suprafata + " " + QString::fromStdString(locatar.get_tip_apartament()));
			}
			lista_filtrare->show();
		}
		});


	/*QObject::connect(lista, &QListWidget::itemSelectionChanged, this, [&]() {
		auto elemente_selectate = lista->selectedItems();
		if (elemente_selectate.isEmpty())
		{
			spin_numar_apartament_adauga->setValue(1);
			text_nume_adauga->setText("");
			spin_suprafata_adauga->setValue(1);
			text_tip_apartament_adauga->setText("");
		}
		else 
		{
			auto element_selectat = elemente_selectate.at(0);
			auto numar_apartament = element_selectat->data(Qt::UserRole);
			spin_numar_apartament_adauga->setValue(numar_apartament.toInt());
			const int pozitie_locatar_cautat = service_locatari.service_cauta_locatar(numar_apartament.toInt());
			const auto &lista_locatari = service_locatari.service_get_lista_locatari();
			const auto& locatar = lista_locatari.at(pozitie_locatar_cautat);
			text_nume_adauga->setText(QString::fromStdString(locatar.get_nume_proprietar()));
			spin_suprafata_adauga->setValue(locatar.get_suprafata());
			text_tip_apartament_adauga->setText(QString::fromStdString(locatar.get_tip_apartament()));
		}
		});*/

	QObject::connect(lista->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (lista->selectionModel()->selectedIndexes().isEmpty())
		{
			spin_numar_apartament_adauga->setValue(0);
			text_nume_adauga->setText("");
			spin_suprafata_adauga->setValue(0);
			text_tip_apartament_adauga->setText("");
			return;
		}

		auto rand_selectat = lista->selectionModel()->selectedIndexes().at(0);
		auto numar_apartament = rand_selectat.data(Qt::UserRole);
		spin_numar_apartament_adauga->setValue(numar_apartament.toInt());
		const int pozitie_locatar_cautat = service_locatari.service_cauta_locatar(numar_apartament.toInt());
		const auto& lista_locatari = service_locatari.service_get_lista_locatari();
		const auto& locatar = lista_locatari.at(pozitie_locatar_cautat);
		text_nume_adauga->setText(QString::fromStdString(locatar.get_nume_proprietar()));
		spin_suprafata_adauga->setValue(locatar.get_suprafata());
		text_tip_apartament_adauga->setText(QString::fromStdString(locatar.get_tip_apartament()));

		});



	QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (tabel->selectionModel()->selectedIndexes().isEmpty())
		{
			spin_numar_apartament_adauga->setValue(0);
			text_nume_adauga->setText("");
			spin_suprafata_adauga->setValue(0);
			text_tip_apartament_adauga->setText("");
			return;
		}

		int rand_selectat = tabel->selectionModel()->selectedIndexes().at(0).row();
		auto coloana1 = tabel->model()->index(rand_selectat, 0);
		auto coloana2 = tabel->model()->index(rand_selectat, 1);
		auto coloana3 = tabel->model()->index(rand_selectat, 2);
		auto coloana4 = tabel->model()->index(rand_selectat, 3);

		auto numar_apartament = tabel->model()->data(coloana1, Qt::DisplayRole);
		spin_numar_apartament_adauga->setValue(numar_apartament.toInt());
		auto nume_proprietar = tabel->model()->data(coloana2, Qt::DisplayRole);
		text_nume_adauga->setText(nume_proprietar.toString());
		auto suprafata = tabel->model()->data(coloana3, Qt::DisplayRole);
		spin_suprafata_adauga->setValue(suprafata.toInt());
		auto tip_apartament = tabel->model()->data(coloana4, Qt::DisplayRole);
		text_tip_apartament_adauga->setText(tip_apartament.toString());

		});

	QObject::connect(buton_frecvente, &QPushButton::clicked, this, [&]() {
		std::map<int, int> frecvente_suprafete;
		service_locatari.frecventa_suprafete(frecvente_suprafete);
		lista_frecvente->clear();
		for (const auto& pereche : frecvente_suprafete)
		{
			QString suprafata;
			suprafata.setNum(pereche.first);
			QString frecventa;
			frecventa.setNum(pereche.second);
			lista_frecvente->addItem("suprafata: " + suprafata + " frecventa: " + frecventa);
		}
		lista_frecvente->show();
		});



	QObject::connect(buton_adauga_lista_notificare, &QPushButton::clicked, this, [&]() {
		int numar_apartament = spin_numar_apartament_adauga->value();
		try {
			service_locatari.adauga_locatar_in_lista_notificare(numar_apartament);
		}
		catch (const ExceptieValidare& exceptie_validare)
		{
			QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieListaNotificare& exceptie_lista_notificare) {
			QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_lista_notificare.get_mesaj()));
		}
		});

	QObject::connect(buton_genereaza_lista_notificare, &QPushButton::clicked, this, [&]() {
		int numar_apartamente = spin_numar_apartament_adauga->value();
		if (numar_apartamente > service_locatari.service_get_numar_locatari())
		{
			QMessageBox::warning(nullptr, "Exceptie lista notificare", "Insuficient numar de locatari in lista de locatari");
		}
		else
		{
			try {
				service_locatari.genereaza_lista_notificare(numar_apartamente);
			}
			catch (const ExceptieValidare& exceptie_validare) {
				QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_validare.get_mesaj()));
			}
		}
		});

	QObject::connect(buton_goleste_lista_notificare, &QPushButton::clicked, this, [&]() {
		try {
			service_locatari.goleste_lista_notificare();
		}
		catch (const ExceptieListaNotificare& exceptie_lista_notificare) {
			QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_lista_notificare.get_mesaj()));
		}
		});

	QObject::connect(buton_lista_notificare, &QPushButton::clicked, this, [&]() {
		GUIListaNotificare* gui_lista_notificare = new GUIListaNotificare(service_locatari, lista_de_notificare);
		gui_lista_notificare->show();
		});

	QObject::connect(buton_lista_notificare_read_only, &QPushButton::clicked, this, [&]() {
		GUIListaNotificareReadOnly* gui_lista_notificare_read_only = new GUIListaNotificareReadOnly(lista_de_notificare);
		gui_lista_notificare_read_only->show();
		});
}

/*void GUI::incarca_locatari(const std::vector<Locatar>& lista_locatari)
{
	lista->clear();
	for (const auto& locatar_curent : lista_locatari)
	{
		QString numar_apartament;
		numar_apartament.setNum(locatar_curent.get_numar_apartament());
		QString suprafata;
		suprafata.setNum(locatar_curent.get_suprafata());
		QListWidgetItem* inregistrare = new QListWidgetItem(numar_apartament + " " + QString::fromStdString(locatar_curent.get_nume_proprietar()) + " " + suprafata + " " + QString::fromStdString(locatar_curent.get_tip_apartament()), lista);
		inregistrare->setData(Qt::UserRole, numar_apartament);
		lista->addItem(inregistrare);
	}
}*/

void GUI::incarca_locatari(const std::vector<Locatar>& lista_locatari)
{
	model_lista->set_locatari(lista_locatari);
}

/*void GUI::incarca_tabel(const std::vector<Locatar>& lista_locatari)
{
	tabel->clear();
	int i = 0;
	for (const auto& locatar_curent : lista_locatari)
	{
		QString numar_apartament;
		numar_apartament.setNum(locatar_curent.get_numar_apartament());
		QString suprafata;
		suprafata.setNum(locatar_curent.get_suprafata());
		QTableWidgetItem* continut_coloana1 = new QTableWidgetItem(numar_apartament);
		QTableWidgetItem* continut_coloana2 = new QTableWidgetItem(QString::fromStdString(locatar_curent.get_nume_proprietar()));
		QTableWidgetItem* continut_coloana3 = new QTableWidgetItem(suprafata);
		QTableWidgetItem* continut_coloana4 = new QTableWidgetItem(QString::fromStdString(locatar_curent.get_tip_apartament()));
		tabel->setItem(i, 0, continut_coloana1);
		tabel->setItem(i, 1, continut_coloana2);
		tabel->setItem(i, 2, continut_coloana3);
		tabel->setItem(i, 3, continut_coloana4);
		i++;
	}
}*/

void GUI::incarca_tabel(const std::vector<Locatar>& lista_locatari)
{
	model_tabel->set_locatari(lista_locatari);
}