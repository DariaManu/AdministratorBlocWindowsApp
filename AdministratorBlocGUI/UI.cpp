#include "UI.h"
#include "ServiceLocatari.h"
#include "VectorDinamic.h"
#include <iostream>
#include <string>
#include <map>

//se afiseaza meniul aplicatiei
void UI::meniu()
{
	std::cout << "\n0. Exit\n1. Adauga\n2. Cauta\n3. Modifica nume\n4. Modifica suprafata\n5. Modifica tip apartament\n6. Sterge\n";
	std::cout << "7. Filtreaza dupa tip apartament\n8. Filtreaza dupa suprafata\n";
	std::cout << "9. Sorteaza dupa nume\n10. Sorteaza dupa suprafata\n11. Sorteaza dupa tip si suprafata\n";
	std::cout << "12. Afiseaza\n";
	std::cout << "13. Adauga in lista de notificare\n14. Goleste lista de notificare\n15. Genereaza lista de notificare\n16. Afiseaza lista de notificare\n";
	std::cout << "17. Frecvente suprafete\n18. Export\n19. Undo\n";
	std::cout << "Comanda:";
}

//functie de ui pentru adaugarea unui proprietar la lista de proprietari
void UI::ui_adauga_locatar()
{
	std::string nume_proprietar, tip_apartament;
	int numar_apartament, suprafata;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	std::cout << "Dati numele proprietarului:";
	std::cin >> nume_proprietar;
	std::cout << "Dati suprafata apartamentului:";
	std::cin >> suprafata;
	std::cout << "Dati tipul apartamentului:";
	std::cin >> tip_apartament;

	try {
		service_locatari.service_adauga_locatar(numar_apartament, nume_proprietar, suprafata, tip_apartament);
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj();
	}
	catch (const ExceptieRepo &exceptie_repo) {
		std::cout << exceptie_repo.get_mesaj();
	}
	
	/*if (status_adaugare == 1)
		std::cout << "Locatar adaugat cu succes\n";
	else
		std::cout << "Locatar existent\n";*/
}

//functie de ui pentru cautarea unui locatar in lista de locatari
void UI::ui_cauta_locatar()
{
	int numar_apartament;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	try {
		const int pozitie_locatar_cautat = service_locatari.service_cauta_locatar(numar_apartament);
		auto lista_locatari = service_locatari.service_get_lista_locatari();
		std::cout << lista_locatari.at(pozitie_locatar_cautat).get_numar_apartament() << " " << lista_locatari.at(pozitie_locatar_cautat).get_nume_proprietar() << " " << lista_locatari.at(pozitie_locatar_cautat).get_suprafata() << " " << lista_locatari.at(pozitie_locatar_cautat).get_tip_apartament() << std::endl;
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj();
	}
	catch (const ExceptieRepo &exceptie_repo) {
		std::cout << exceptie_repo.get_mesaj();
	}
	
}

//functie de ui pentru modificarea numelui unui proprietar de apartament
void UI::ui_modifica_nume_proprietar()
{
	int numar_apartament;
	std::string nume_nou;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	std::cout << "Dati noul nume:";
	std::cin >> nume_nou;
	try {
		service_locatari.service_modifica_nume_proprietar(numar_apartament, nume_nou);
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj();
	}
	catch (const ExceptieRepo &exceptie_repo) {
		std::cout << exceptie_repo.get_mesaj();
	}
	
	/*if (status_modificare == 1)
		std::cout << "Locatar modificat cu succes\n";
	else
		std::cout << "Locatar inexistent\n";*/
}

//functie de ui pentru modificarea suprafetei unui apartament
void UI::ui_modifica_suprafata()
{
	int numar_apartament, suprafata_noua;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	std::cout << "Dati noul spatiu:";
	std::cin >> suprafata_noua;
	try {
		service_locatari.service_modifica_suprafata_apartament(numar_apartament, suprafata_noua);
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj();
	}
	catch (const ExceptieRepo &exceptie_repo) {
		std::cout << exceptie_repo.get_mesaj();
	}
	
	/*if (status_modificare == 1)
		std::cout << "Locatar modificat cu succes\n";
	else
		std::cout << "Locatar inexistent\n";*/
}

//functie de ui pentru modificarea tipului unui apartament
void UI::ui_modifica_tip_apartament()
{
	int numar_apartament;
	std::string tip_nou;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	std::cout << "Dati noul tip:";
	std::cin >> tip_nou;
	try {
		service_locatari.service_modifica_tip_apartament(numar_apartament, tip_nou);
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj();
	}
	catch (const ExceptieRepo &exceptie_repo) {
		std::cout << exceptie_repo.get_mesaj();
	}
	
	/*if (status_modificare == 1)
		std::cout << "Locatar modificat cu succes\n";
	else
		std::cout << "Locatar inexistent\n";*/
}

//functie de ui pentru stergerea unui locatar
void UI::ui_sterge_locatar()
{
	int numar_apartament;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	try {
		service_locatari.service_sterge_locatar(numar_apartament);
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj();
	}
	catch (const ExceptieRepo &exceptie_repo) {
		std::cout << exceptie_repo.get_mesaj();
	}
	
	/*if (status_stergere == 1)
		std::cout << "Locatar sters cu succes\n";
	else
		std::cout << "Locatar inexistent\n";*/
}

//functie de ui pentru filtrarea locatarilor dupa tipul apartamentului
void UI::ui_filtreaza_dupa_tip_apartament()
{
	std::string conditie_filtrare;
	std::cout << "Dati tipul apartamentului dupa care se face filtrarea: ";
	std::cin >> conditie_filtrare;
	std::vector<Locatar> lista_locatari_filtrata;
	service_locatari.service_filtrare_dupa_tip_apartament(lista_locatari_filtrata, conditie_filtrare);
	for (const auto &locatar : lista_locatari_filtrata)
		std::cout << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
}

//functie de ui pentru filtrarea locatarilor dupa suprafata apartamentului
void UI::ui_filtreaza_dupa_suprafata()
{
	int conditie_filtrare;
	std::cout << "Dati suprafata dupa care se face filtrarea: ";
	std::cin >> conditie_filtrare;
	std::vector<Locatar> lista_locatari_filtrata;
	service_locatari.service_filtrare_dupa_suprafata(lista_locatari_filtrata, conditie_filtrare);
	for (const auto &locatar : lista_locatari_filtrata)
		std::cout << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
}

//functie de ui pentru sortarea locatarilor dupa numele proprietarilor
void UI::ui_sorteaza_dupa_nume()
{
	auto lista_sortata = service_locatari.service_get_lista_locatari();
	service_locatari.sortare_dupa_nume(lista_sortata);
	for (const auto &locatar : lista_sortata)
		std::cout << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
}

//functie de ui pentru sortarea locatarilor dupa suprafata apartamentelor
void UI::ui_sorteaza_dupa_suprafata()
{
	auto lista_sortata = service_locatari.service_get_lista_locatari();
	service_locatari.sortare_dupa_suprafata(lista_sortata);
	for (const auto &locatar : lista_sortata)
		std::cout << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
}

//functie de ui pentru sortarea locatarilor dupa tipul apartamentului si apoi dupa suprafata
void UI::ui_sorteaza_dupa_tip_si_suprafata()
{
	auto lista_sortata = service_locatari.service_get_lista_locatari();
	service_locatari.sortare_dupa_tip_si_suprafata(lista_sortata);
	for (const auto &locatar : lista_sortata)
		std::cout << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
}

void UI::ui_afiseaza_frecvente_suprafete()
{
	std::map<int, int> frecvente_suprafete;
	service_locatari.frecventa_suprafete(frecvente_suprafete);
	for (const auto &pereche : frecvente_suprafete)
	{
		auto suprafata = pereche.first;
		auto frecventa = pereche.second;
		std::cout << "suprafta: " << suprafata << " frecventa:" << frecventa << std::endl;
	}
}

//functie de ui pentru afisarea listei de locatari
void UI::ui_afiseaza_locatari()
{
	auto lista_locatari = service_locatari.service_get_lista_locatari();
	for (const auto &locatar : lista_locatari)
		std::cout << std::endl << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
}

//functie de ui pentru adaugarea unui locatar in lista de notificare
void UI::ui_adauga_in_lista_notificare()
{
	int numar_apartament;
	std::cout << "Dati numarul apartamentului:";
	std::cin >> numar_apartament;
	try {
		service_locatari.adauga_locatar_in_lista_notificare(numar_apartament);
	}
	catch (const ExceptieValidare &exceptie_validare)
	{
		std::cout << exceptie_validare.get_mesaj() << std::endl;
	}
	catch (const ExceptieListaNotificare &exceptie_lista_notificare) {
		std::cout << exceptie_lista_notificare.get_mesaj() << std::endl;
	}
	std::cout << "Numarul de apartamente din lista de notificare:" << service_locatari.get_dimensiune_lista_notificare();
}

//functie de ui pentru golirea listei de notificare
void UI::ui_goleste_lista_notificare()
{
	try {
		service_locatari.goleste_lista_notificare();
	}
	catch (const ExceptieListaNotificare &exceptie_lista_notificare) {
		std::cout << exceptie_lista_notificare.get_mesaj() << std::endl;
	}
	std::cout << "Numarul de apartamente din lista de notificare:" << service_locatari.get_dimensiune_lista_notificare();
}

//functie de ui pentru generearea unei liste de notificare
void UI::ui_genereaza_lista_notificare()
{
	int numar_apartamente;
	std::cout << "Dati numarul de apartamente din lista de notificare:";
	std::cin >> numar_apartamente;
	try {
		service_locatari.genereaza_lista_notificare(numar_apartamente);
	}
	catch (const ExceptieValidare &exceptie_validare) {
		std::cout << exceptie_validare.get_mesaj() << std::endl;
	}
	std::cout << "Numarul de apartamente din lista de notificare:" << service_locatari.get_dimensiune_lista_notificare();
}

//functie de ui pentru afisarea listei de notificare
void UI::ui_afiseaza_lista_notificare()
{
	const auto &lista_notificare = service_locatari.get_lista_notificare();
	for (const auto &locatar : lista_notificare)
	{
		std::cout << std::endl << locatar.get_numar_apartament() << " " << locatar.get_nume_proprietar() << " " << locatar.get_suprafata() << " " << locatar.get_tip_apartament() << std::endl;
	}
}

//functie de ui pentru salvarea listei de notificare in fisier
void UI::ui_export_lista_notificare()
{
	std::string nume_fisier;
	std::cout << "Dati numele fisierului:";
	std::cin >> nume_fisier;
	service_locatari.export_lista_notificare(nume_fisier);
}

//functie de ui pentru undo
void UI::ui_undo()
{
	try {
		service_locatari.undo();
	}catch (const ExceptieService &exceptie)
	{
		std::cout << exceptie.get_mesaj();
	}
}


//se ruleaza aplicatia
void UI::ruleaza_aplicatia()
{
	int comanda{ -1 };
	while (true)
	{
		meniu();
		std::cin >> comanda;
		if (comanda == 0)
			break;
		if (comanda == 1)
			ui_adauga_locatar();
		if (comanda == 2)
			ui_cauta_locatar();
		if (comanda == 3)
			ui_modifica_nume_proprietar();
		if (comanda == 4)
			ui_modifica_suprafata();
		if (comanda == 5)
			ui_modifica_tip_apartament();
		if (comanda == 6)
			ui_sterge_locatar();
		if (comanda == 7)
			ui_filtreaza_dupa_tip_apartament();
		if (comanda == 8)
			ui_filtreaza_dupa_suprafata();
		if (comanda == 9)
			ui_sorteaza_dupa_nume();
		if (comanda == 10)
			ui_sorteaza_dupa_suprafata();
		if (comanda == 11)
			ui_sorteaza_dupa_tip_si_suprafata();
		if (comanda == 12)
			ui_afiseaza_locatari();
		if (comanda == 13)
			ui_adauga_in_lista_notificare();
		if (comanda == 14)
			ui_goleste_lista_notificare();
		if (comanda == 15)
			ui_genereaza_lista_notificare();
		if (comanda == 16)
			ui_afiseaza_lista_notificare();
		if (comanda == 17)
			ui_afiseaza_frecvente_suprafete();
		if (comanda == 18)
			ui_export_lista_notificare();
		if (comanda == 19)
			ui_undo();
	}
}


