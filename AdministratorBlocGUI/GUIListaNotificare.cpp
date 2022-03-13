#include "GUIListaNotificare.h"

void GUIListaNotificare::initialieaza_GUI()
{
	QHBoxLayout* layout_principal = new QHBoxLayout;
	setLayout(layout_principal);

	QGroupBox* grup_lista = new QGroupBox;
	QVBoxLayout* layout_grup_lista = new QVBoxLayout;
	grup_lista->setLayout(layout_grup_lista);
	layout_grup_lista->addWidget(lista);
	numar_locatari_lista_notificare->setText("Numar locatari in lista de notificare: 0");
	layout_grup_lista->addWidget(numar_locatari_lista_notificare);

	layout_principal->addWidget(grup_lista);

	QGroupBox* grup_actualizari = new QGroupBox;
	QVBoxLayout* layout_grup_actualizari = new QVBoxLayout;
	grup_actualizari->setLayout(layout_grup_actualizari);

	QFormLayout* form_layout = new QFormLayout;
	spin_numar_apartament_adauga->setRange(1, 10000);
	form_layout->addRow("Numar apartament", spin_numar_apartament_adauga);
	form_layout->addWidget(buton_adauga);
	spin_numar_notificati->setRange(1, 10000);
	form_layout->addRow("Numar apartamente notificate", spin_numar_notificati);
	form_layout->addWidget(buton_genereaza_lista);
	form_layout->addRow("Nume fisier export", text_fisier_export);
	form_layout->addWidget(buton_export);
	layout_grup_actualizari->addLayout(form_layout);

	layout_grup_actualizari->addWidget(buton_goleste_lista);

	layout_principal->addWidget(grup_actualizari);
}

void GUIListaNotificare::initializeaza_conexiuni()
{
	lista_de_notificare.adauga_observer(this);

	QObject::connect(buton_adauga, &QPushButton::clicked, this, [&]() {
		int numar_apartament = spin_numar_apartament_adauga->value();
		try {
			service_locatari.adauga_locatar_in_lista_notificare(numar_apartament);
			//incarca_lista_notificare(service_locatari.get_lista_notificare());
		}
		catch (const ExceptieValidare& exceptie_validare)
		{
			QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_validare.get_mesaj()));
		}
		catch (const ExceptieListaNotificare& exceptie_lista_notificare) {
			QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_lista_notificare.get_mesaj()));
		}
		});

	QObject::connect(buton_genereaza_lista, &QPushButton::clicked, this, [&]() {
		int numar_apartamente = spin_numar_notificati->value();
		if (numar_apartamente > service_locatari.service_get_numar_locatari())
		{
			QMessageBox::warning(nullptr, "Exceptie lista notificare", "Insuficient numar de locatari in lista de locatari");
		}
		else
		{
			try {
				service_locatari.genereaza_lista_notificare(numar_apartamente);
				//incarca_lista_notificare(service_locatari.get_lista_notificare());
			}
			catch (const ExceptieValidare& exceptie_validare) {
				QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_validare.get_mesaj()));
			}
		}
		});

	QObject::connect(buton_export, &QPushButton::clicked, this, [&]() {
		QString nume_fisier = text_fisier_export->text();
		service_locatari.export_lista_notificare(nume_fisier.toStdString());
		});

	QObject::connect(buton_goleste_lista, &QPushButton::clicked, this, [&]() {
		try {
			service_locatari.goleste_lista_notificare();
			//incarca_lista_notificare(service_locatari.get_lista_notificare());
		}
		catch (const ExceptieListaNotificare& exceptie_lista_notificare) {
			QMessageBox::warning(nullptr, "Exceptie lista notificare", QString::fromStdString(exceptie_lista_notificare.get_mesaj()));
		}
		});
}

void GUIListaNotificare::incarca_lista_notificare(const std::vector<Locatar>& lista_notificare)
{
	lista->clear();
	for (const auto& locatar : lista_notificare)
	{
		QString numar_apartament;
		numar_apartament.setNum(locatar.get_numar_apartament());
		QString suprafata_apartament;
		suprafata_apartament.setNum(locatar.get_suprafata());
		QListWidgetItem* inregistrare = new QListWidgetItem(numar_apartament + " " + QString::fromStdString(locatar.get_nume_proprietar()) + " " + suprafata_apartament + " " + QString::fromStdString(locatar.get_tip_apartament()));
		lista->addItem(inregistrare);
	}
	QString numar_locatari;
	numar_locatari.setNum(lista_notificare.size());
	numar_locatari_lista_notificare->setText("Numar locatari in lista de notificare :" + numar_locatari);
}
