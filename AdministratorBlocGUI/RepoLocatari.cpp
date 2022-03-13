#include "RepoLocatari.h"
#include "Locatar.h"
#include <algorithm>

/*adauga locatar in mod unic la lista de locatari
pre: locatar - referinta unui locatar existent
post: status_adaugare = 1, daca locatarul a fost adaugat
						0, daca locatarul exista deja in lista

void RepoLocatari::adauga_locatar(const Locatar &locatar)
{
	for (const auto &locatar_curent : lista_locatari)
		if (locatar_curent.get_numar_apartament() == locatar.get_numar_apartament())
		{
			throw ExceptieRepo("Locatar existent!\n");
		}
	lista_locatari.adauga_final(locatar);
}*/

void RepoLocatari::adauga_locatar(const Locatar &locatar)
{
	auto rezultat_cautare = std::find_if(lista_locatari.begin(), lista_locatari.end(), [locatar](const Locatar &locatar_curent) noexcept {
		return locatar_curent.get_numar_apartament() == locatar.get_numar_apartament();
	});
	if (rezultat_cautare != lista_locatari.end())
	{
		throw ExceptieRepo("Locatar existent!\n");
	}
	lista_locatari.push_back(locatar);
}

/*cauta un locatar in lista de locatari dupa numarul apartamentului
pre: numar_apartament - intreg
post: status_cautare = pozitia locatarului in lista, daca locatarul exista in lista
					  -1, daca locatarul nu exista in lista
*/
int RepoLocatari::cauta_locatar(int numar_apartament)
{
	int pozitie_locatar = 0;
	for (const Locatar &locatar_curent : lista_locatari)
	{
		if (locatar_curent.get_numar_apartament() == numar_apartament)
		{
			return pozitie_locatar;
		}
		pozitie_locatar++;
	}
	throw ExceptieRepo("Locatar inexistent!\n");
}

/*modifica numele proprietarului unui apartament
pre: numar_apartament - intreg, nume_nou - referinta unui string
post: status_modificare = 1, daca locatarul a fost modificat cu succes
						  0, daca locatarul nu exista in lista
*/
void RepoLocatari::modifica_nume_proprietar(int numar_apartament, const std::string &nume_nou)
{
	for(Locatar &locatar_curent : lista_locatari)
		if (locatar_curent.get_numar_apartament() == numar_apartament)
		{
			locatar_curent.set_nume_proprietar(nume_nou);
			return;
		}
	throw ExceptieRepo("Locatar inexistent!\n");
}

/*modifica suprafata apartamentului unui locatar
pre: numar_apartament - intreg, suprafata_nou - intreg
post: status_modificare = 1, daca locatarul a fost modificat cu succes
						  0, daca locatarul nu exista in lista
*/
void RepoLocatari::modifica_suprafata_apartament(int numar_apartament, int suprafata_noua)
{
	for(auto &locatar_curent : lista_locatari)
		if (locatar_curent.get_numar_apartament() == numar_apartament)
		{
			locatar_curent.set_suprafata(suprafata_noua);
			return;
		}
	throw ExceptieRepo("Locatar inexistent!\n");
}

/*modifica tipul apartamentului unui locatar
pre: numar_apartament - intreg, tip_apartament_nou - referinta la un string
post: status_modificare = 1, daca locatarul a fost modificat cu succes
						  0, daca locatarul nu exista in lista
*/
void RepoLocatari::modifica_tip_apartament(int numar_apartament, const std::string &tip_apartament_nou)
{
	for(auto &locatar_curent : lista_locatari)
		if (locatar_curent.get_numar_apartament() == numar_apartament)
		{
			locatar_curent.set_tip_apartament(tip_apartament_nou);
			return;
		}
	throw ExceptieRepo("Locatar inexistent!\n");
}

/*sterge un locatar din lista de locatari
pre: numar_apartament - intreg
post: status_stergere = 1, daca locatarul a fost sters din lista
						0, daca locataroul nu exista in lista

void RepoLocatari::sterge_locatar(int numar_apartament)
{
	int i = 0;
	for (const auto &locatar_curent : lista_locatari)
	{
		if (locatar_curent.get_numar_apartament() == numar_apartament)
		{
			lista_locatari.sterge_pozitie(i);
			return;
		}
		i++;
	}
	throw ExceptieRepo("Locatar inexistent!\n");
}*/

void RepoLocatari::sterge_locatar(int numar_apartament)
{
	auto rezultat_cautare = std::find_if(lista_locatari.begin(), lista_locatari.end(), [numar_apartament](const Locatar &locatar_curent)noexcept {
		return locatar_curent.get_numar_apartament() == numar_apartament;
	});
	if (rezultat_cautare == lista_locatari.end())
	{
		throw ExceptieRepo("Locatar inexistent!\n");
	}
	lista_locatari.erase(rezultat_cautare);
}

/*
returneaza o referinta a listei de locatari
*/
const std::vector<Locatar>& RepoLocatari::get_lista_locatari() noexcept
{
	return lista_locatari;
}

/*
returneaza numarul de locatari din lista
*/
int RepoLocatari::get_numar_locatari() noexcept
{
	return lista_locatari.size();
}

const Locatar & RepoLocatari::get_locatar(int pozitie)
{
	return lista_locatari.at(pozitie);
}
