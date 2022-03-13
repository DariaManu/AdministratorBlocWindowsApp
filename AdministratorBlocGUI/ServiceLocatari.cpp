#include "ServiceLocatari.h"
#include "Locatar.h"
#include "RepoLocatari.h"
#include "Undo.h"
#include <algorithm>
#include <map>
#include <fstream>
#include <memory>

/*functie de service pentru adaugarea unui locatar in lista de locatari
pre: numar_apartament - intreg, nume_proprietar - referinta la string, suprafata - intreg, tip_apartament - referinta la string
post: status_adaugare = 1, daca locatarul a fost adaugat
						0, daca locatarul exista deja in lista
*/
void ServiceLocatari::service_adauga_locatar(int numar_apartament, const std::string &nume_proprietar, int suprafata, const std::string &tip_apartament)
{
	validator.valideaza_numar_apartament(numar_apartament);
	validator.valideaza_nume_proprietar(nume_proprietar);
	validator.valideaza_suprafata(suprafata);
	validator.valideaza_tip_apartament(tip_apartament);
	Locatar locatar{ numar_apartament, nume_proprietar, suprafata, tip_apartament };
	repo_locatari.adauga_locatar(locatar);
	lista_actiuni_undo.push_back(std::make_unique<UndoAdauga>(repo_locatari, locatar));
}

/*functie de service pentru cautarea unui locatar in lista de locatari
pre: numar_apartament - intreg
post: status_cautare = pozitia locatarului in lista, daca locatarul exista in lista
					  -1, daca locatarul nu exista in lista
*/
int ServiceLocatari::service_cauta_locatar(int numar_apartament)
{
	validator.valideaza_numar_apartament(numar_apartament);
	const int pozitie_locatar_cautat = repo_locatari.cauta_locatar(numar_apartament);
	return pozitie_locatar_cautat;
}

/*functie de service pentru modificarea numelui unui proprietar
pre: numar_apartament - intreg, nume_nou - referinta la string
post: status_modificare = 1, daca locatarul a fost modificat cu succes
						  0, daca locatarul nu exista in lista
*/
void ServiceLocatari::service_modifica_nume_proprietar(int numar_apartament, const std::string &nume_nou)
{
	validator.valideaza_numar_apartament(numar_apartament);
	validator.valideaza_nume_proprietar(nume_nou);
	const int pozitie = repo_locatari.cauta_locatar(numar_apartament);
	const Locatar locatar = repo_locatari.get_locatar(pozitie);
	repo_locatari.modifica_nume_proprietar(numar_apartament, nume_nou);
	lista_actiuni_undo.push_back(std::make_unique<UndoModificaNume>(repo_locatari, locatar));
}

/*functie de service pentru modificarea suprafetei unui apartament
pre: numar_apartament - intreg, suprafata_noua - intreg
post: status_modificare = 1, daca locatarul a fost modificat cu succes
						  0, daca locatarul nu exista in lista
*/
void ServiceLocatari::service_modifica_suprafata_apartament(int numar_apartament, int suprafata_noua)
{
	validator.valideaza_numar_apartament(numar_apartament);
	validator.valideaza_suprafata(suprafata_noua);
	const int pozitie = repo_locatari.cauta_locatar(numar_apartament);
	const Locatar locatar = repo_locatari.get_locatar(pozitie);
	repo_locatari.modifica_suprafata_apartament(numar_apartament, suprafata_noua);
	lista_actiuni_undo.push_back(std::make_unique<UndoModificaSuprafata>(repo_locatari, locatar));
}

/*functie de service pentru modificarea tipului unui apartament
pre: numar_apartament - intreg, tip_apartament_nou - referinta la string
post: status_modificare = 1, daca locatarul a fost modificat cu succes
						  0, daca locatarul nu exista in lista
*/
void ServiceLocatari::service_modifica_tip_apartament(int numar_apartament, const std::string &tip_apartament_nou)
{
	validator.valideaza_numar_apartament(numar_apartament);
	validator.valideaza_tip_apartament(tip_apartament_nou);
	const int pozitie = repo_locatari.cauta_locatar(numar_apartament);
	const Locatar locatar = repo_locatari.get_locatar(pozitie);
	repo_locatari.modifica_tip_apartament(numar_apartament, tip_apartament_nou);
	lista_actiuni_undo.push_back(std::make_unique<UndoModificaTip>(repo_locatari, locatar));
}

/*functie de service pentru stergerea unui locatar din lista
pre: numar_apartament - intreg
post: status_stergere = 1, daca locatarul a fost sters din lista
						0, daca locataroul nu exista in lista
*/
void ServiceLocatari::service_sterge_locatar(int numar_apartament)
{
	validator.valideaza_numar_apartament(numar_apartament);
	const int pozitie = repo_locatari.cauta_locatar(numar_apartament);
	const Locatar locatar = repo_locatari.get_locatar(pozitie);
	repo_locatari.sterge_locatar(numar_apartament);
	lista_actiuni_undo.push_back(std::make_unique<UndoSterge>(repo_locatari, locatar));
}

/*functie de filtrare a locatarilor care care au tipul apartamentului diferit de cel dat de utilizator
pre: lista_locatari_filtrare - referinta la o lista care va contine locatarii care respecta conditia de filtrare, conditie_filtrare - referinta la string
post: lista_locatari_filtrare contine doar locatarii care au tipul apartamentului = conditie_filtrare
*/
/*
void ServiceLocatari::service_filtrare_dupa_tip_apartament(std::vector<Locatar> &lista_locatari_filtrare, const std::string &conditie_filtrare)
{
	for(int i=0; i<lista_locatari_filtrare.get_dimensiune(); i++)
		if (lista_locatari_filtrare.get_element(i).get_tip_apartament() != conditie_filtrare)
		{
			lista_locatari_filtrare.sterge_pozitie(i);
			i--;
		}
}*/
void ServiceLocatari::service_filtrare_dupa_tip_apartament(std::vector<Locatar> &lista_locatari_filtrare, const std::string &conditie_filtrare)
{
	const auto &lista_locatari = repo_locatari.get_lista_locatari();
	std::copy_if(lista_locatari.begin(), lista_locatari.end(), std::back_inserter(lista_locatari_filtrare), [conditie_filtrare](const Locatar &locatar_curent) {
		return locatar_curent.get_tip_apartament() == conditie_filtrare;
	});
}



/*functie de filtrare a locatarilor care au suprafata apartamentului mai mare decat cea data de utilizator
pre: lista_locatari_filtrare - referinta la o lista care va contine locatarii care respecta conditia de filtrare, conditie_filtrare - intreg
post: lista_locatari_filtrare contine doar locatarii care au suprafata apartamentului < conditie_filtrare
*/
/*
void ServiceLocatari::service_filtrare_dupa_suprafata(std::vector<Locatar> lista_locatari_filtrare, int conditie_filtrare)
{
	for (int i = 0; i < lista_locatari_filtrare.get_dimensiune(); i++)
		if (lista_locatari_filtrare.get_element(i).get_suprafata() > conditie_filtrare)
		{
			lista_locatari_filtrare.sterge_pozitie(i);
			i--;
		}
}*/
void ServiceLocatari::service_filtrare_dupa_suprafata(std::vector<Locatar>& lista_locatari_filtrare, int conditie_filtrare)
{
	const auto &lista_locatari = repo_locatari.get_lista_locatari();
	std::copy_if(lista_locatari.begin(), lista_locatari.end(), std::back_inserter(lista_locatari_filtrare), [conditie_filtrare](const Locatar &locatar_curent)noexcept {
		return locatar_curent.get_suprafata() <= conditie_filtrare;
	});
}


/*functie care compara doi locatari dupa suprafata apartamentului
pre: locatar1 - referinta la un locatar existent, locatar2 - referinta la un locatar existent
post: false - daca locatar1>locatar2
	  true - altfel
*/
bool compara_dupa_suprafata(const Locatar& locatar1, const Locatar& locatar2) noexcept
{
	if (locatar1.get_suprafata() > locatar2.get_suprafata())
		return false;
	return true;
}

void ServiceLocatari::sortare(std::vector<Locatar> &lista_locatari_sortare)
{
	Locatar locatar_auxiliar{0, "", 0, ""};
	for(unsigned int i=0; i<lista_locatari_sortare.size()-1; i++)
		for(unsigned int j=i+1; j<lista_locatari_sortare.size(); j++)
			if (compara_dupa_suprafata(lista_locatari_sortare.at(i), lista_locatari_sortare.at(j)) == false)
			{
				auto aux = lista_locatari_sortare.at(i);
				lista_locatari_sortare.at(i) = lista_locatari_sortare.at(j);
				lista_locatari_sortare.at(j) = aux;
			}
}

bool compara_dupa_nume(const Locatar& locatar1, const Locatar& locatar2)
{
	if (locatar1.get_nume_proprietar() > locatar2.get_nume_proprietar())
		return false;
	return true;
}

void ServiceLocatari::sortare_nume(std::vector<Locatar>& lista_locatari_sortare)
{
	Locatar locatar_auxiliar{ 0, "", 0, "" };
	for (unsigned int i = 0; i < lista_locatari_sortare.size() - 1; i++)
		for (unsigned int j = i + 1; j < lista_locatari_sortare.size(); j++)
			if (compara_dupa_nume(lista_locatari_sortare.at(i), lista_locatari_sortare.at(j)) == false)
			{
				auto aux = lista_locatari_sortare.at(i);
				lista_locatari_sortare.at(i) = lista_locatari_sortare.at(j);
				lista_locatari_sortare.at(j) = aux;
			}
}

bool compara_dupa_tip_si_suprafata(const Locatar& locatar1, const Locatar& locatar2)
{
	if (locatar1.get_tip_apartament() > locatar2.get_tip_apartament())
		return false;
	else if (locatar1.get_tip_apartament() == locatar2.get_tip_apartament())
		if (locatar1.get_suprafata() > locatar2.get_suprafata())
			return false;
	return true;
}

void ServiceLocatari::sortare_tip_suprafata(std::vector<Locatar>& lista_locatari_sortare)
{
	Locatar locatar_auxiliar{ 0, "", 0, "" };
	for (unsigned int i = 0; i < lista_locatari_sortare.size() - 1; i++)
		for (unsigned int j = i + 1; j < lista_locatari_sortare.size(); j++)
			if (compara_dupa_tip_si_suprafata(lista_locatari_sortare.at(i), lista_locatari_sortare.at(j)) == false)
			{
				auto aux = lista_locatari_sortare.at(i);
				lista_locatari_sortare.at(i) = lista_locatari_sortare.at(j);
				lista_locatari_sortare.at(j) = aux;
			}
}

/*functie care compara doi locatari dupa numele proprietarului
pre: locatar1 - referinta la un locatar existent, locatar2 - referinta la un locatar existent
post: false - daca locatar1>locatar2
	  true - altfel
*/


/*functie care compara doi locatari dupa tipul apartamentului si apoi dupa suprafata
pre: locatar1 - referinta la un locatar existent, locatar2 - referinta la un locatar existent
post: false - daca locatar1>=locatar2
	  true - altfel
*/




/*
functie de sortare a listei de locatari dupa numele proprietarului
pre: lista_locatari_sortare - referinta la o copie a listei de locatari
post: lista_locatri_sortare este sortata dupa numele proprietarilor
*/
/*
void ServiceLocatari::sortare_dupa_nume(std::vector<Locatar>& lista_locatari_sortare)
{
	
	sortare(lista_locatari_sortare, compara_dupa_nume);
}*/
void ServiceLocatari::sortare_dupa_nume(std::vector<Locatar>& lista_locatari_sortare)
{
	std::sort(lista_locatari_sortare.begin(), lista_locatari_sortare.end(), [](const Locatar &locatar1, const Locatar &locatar2) {
		return locatar1.get_nume_proprietar() <= locatar2.get_nume_proprietar();
	});
}

/*
functie de sortare a listei de locatari dupa suprafata apartamentului
pre: lista_locatari_sortare - referinta la o copie a listei de locatari
post: lista_locatri_sortare este sortata dupa suprafetele apartamentelor
*/
/*
void ServiceLocatari::sortare_dupa_suprafata(std::vector<Locatar>& lista_locatari_sortare)
{
	sortare(lista_locatari_sortare, compara_dupa_suprafata);
}*/
void ServiceLocatari::sortare_dupa_suprafata(std::vector<Locatar>& lista_locatari_sortare)
{
	std::sort(lista_locatari_sortare.begin(), lista_locatari_sortare.end(), [](const Locatar &locatar1, const Locatar &locatar2)noexcept {
		return locatar1.get_suprafata() <= locatar2.get_suprafata();
	});
}

/*
functie de sortare a listei de locatari dupa tipul apartamentului si suprafata apartamentului
pre: lista_locatari_sortare - referinta la o copie a listei de locatari
post: lista_locatri_sortare este sortata dupa tipul apartamentului si dupa suprafata apartamentului
*/
/*
void ServiceLocatari::sortare_dupa_tip_si_suprafata(std::vector<Locatar>& lista_locatari_sortare)
{
	sortare(lista_locatari_sortare, compara_dupa_tip_si_suprafata);
}*/
void ServiceLocatari::sortare_dupa_tip_si_suprafata(std::vector<Locatar>& lista_locatari_sortare)
{
	std::sort(lista_locatari_sortare.begin(), lista_locatari_sortare.end(), [](const Locatar &locatar1, const Locatar &locatar2) {
		if (locatar1.get_tip_apartament() > locatar2.get_tip_apartament())
			return false;
		else if (locatar1.get_tip_apartament() == locatar2.get_tip_apartament())
			if (locatar1.get_suprafata() > locatar2.get_suprafata())
				return false;
		return true;
	});
}

void ServiceLocatari::frecventa_suprafete(std::map<int, int> &frecvente_suprafete)
{
	const auto &lista_locatari = repo_locatari.get_lista_locatari();
	for (const auto &locatar_curent : lista_locatari)
	{
		frecvente_suprafete[locatar_curent.get_suprafata()]++;
	}
}

//functie de service care returneaza o referinta la lista de locatari
const std::vector<Locatar>& ServiceLocatari::service_get_lista_locatari() noexcept
{
	return repo_locatari.get_lista_locatari();
}

void ServiceLocatari::undo()
{
	if (lista_actiuni_undo.size() == 0)
		throw ExceptieService("Nu se mai poate face undo!\n");
	lista_actiuni_undo.back()->doUndo();
	lista_actiuni_undo.pop_back();
}

//functie de service care returneaza numarul de locatari din lista de locatari
int ServiceLocatari::service_get_numar_locatari() noexcept
{
	return repo_locatari.get_numar_locatari();
}

/*functie de service pentru adaugarea unui locatar in lista de notificare
pre: numar_apartament - intreg
post: se arunca exceptie daca nu se poate adauga locatarul
	  se adauga locatarul, altfel
*/
void ServiceLocatari::adauga_locatar_in_lista_notificare(int numar_apartament)
{
	validator.valideaza_numar_apartament(numar_apartament);
	lista_de_notificare.adauga_locatar(numar_apartament);
}

/*functie de service pentru golirea listei de notificare
pre: lista de notificare nu este deja goala
post: se arunca exceptie daca lista este deja goala
	  se goleste lista,  altfel
*/
void ServiceLocatari::goleste_lista_notificare()
{
	lista_de_notificare.goleste_lista();
}

/*functie de service pentru generarea unei liste de notificare
pre: numar_total_apartamente - intreg, numar mai mic decat nuamrul total de locatari din lista de locatari
post: se genereaza o lista de notificare avand "numar_total_apartamente" locatari 
*/
void ServiceLocatari::genereaza_lista_notificare(int numar_total_apartamente)
{
	validator.valideaza_numar_apartament(numar_total_apartamente);
	lista_de_notificare.genereaza_lista(numar_total_apartamente);
}

/*functie de service pentru salvarea listei de notificare intr-un fisier dat de utilizator
pre: nume_fisier - string; reprezinta numele unui fisier
post: fisierul "nume_fisier" va contine locatarii care se afla in momentul apelului functiei in lista de notificare
*/
void ServiceLocatari::export_lista_notificare(std::string const& nume_fisier)
{
	std::ofstream fisier(nume_fisier);
	auto const& lista_notificare = lista_de_notificare.get_lista();
	for (const auto &locatar : lista_notificare)
	{
		fisier << locatar.get_numar_apartament() << ";" << locatar.get_nume_proprietar() << ";" << locatar.get_suprafata() << ";" << locatar.get_tip_apartament() << "\n";
	}
}

//functie de service care returneaza numarul de locatari din lista de notificare
int ServiceLocatari::get_dimensiune_lista_notificare() noexcept
{
	return lista_de_notificare.get_dimensiune();
}

//functie de service care returneaza lista de notificare
std::vector<Locatar>& ServiceLocatari::get_lista_notificare() noexcept
{
	return lista_de_notificare.get_lista();
}

