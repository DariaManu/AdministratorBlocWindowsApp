#include "ListaDeNotificare.h"
#include <algorithm>
#include <random>
#include <chrono>

/*functie care adauga un locatar din lista de locatari in lista de notificare a locatarilor
pre: numar_apartament - intreg; numarul apartamentului unui locatar din lista de locatari
post: ExceptieListaNotificare, daca locatarul exista deja in lista de notificare
	  ExceptieListaNotificare, daca locatarul nu exista in lista de locatari
	  lista de notificare contine locatarul cu numarul de apartament dat, altfel
*/
void ListaDeNotificare::adauga_locatar(int numar_apartament)
{
	const auto &lista_locatari = repo_locatari.get_lista_locatari();
	
	auto rezultat_cautare_notificare = std::find_if(lista_de_notificare.begin(), lista_de_notificare.end(), [numar_apartament](const Locatar &locatar_curent) noexcept {
		return locatar_curent.get_numar_apartament() == numar_apartament;
	});
	if(rezultat_cautare_notificare!= lista_de_notificare.end())
		throw ExceptieListaNotificare("Locatar existent in lista de notificare");
	
	auto rezultat_cautare = std::find_if(lista_locatari.begin(), lista_locatari.end(), [numar_apartament](const Locatar &locatar_curent) noexcept {
		return locatar_curent.get_numar_apartament() == numar_apartament;
	});
	if (rezultat_cautare == lista_locatari.end())
		throw ExceptieListaNotificare("Locatar inexistent in lista de locatari");

	Locatar locatar_cautat = *rezultat_cautare;
	lista_de_notificare.push_back(locatar_cautat);

	notifica();
}

/*functie care goleste lista de notificare
pre: lista_de_notificare sa existe si sa nu fie deja vida
post: ExceptieListaNotificare, daca lista este deja vida
	  lista_de_notificare nu mai contine niciun locatar
*/
void ListaDeNotificare::goleste_lista()
{
	if (lista_de_notificare.size() == 0)
		throw ExceptieListaNotificare("Lista de notificare este deja vida");
	while (lista_de_notificare.size() != 0)
	{
		lista_de_notificare.erase(lista_de_notificare.begin());
	}

	notifica();
}

/*functie care genereaza o lista_de_notificare aleator din lista de locatari
pre: numar_total_apartamente - intreg, numar mai mic decat nuamrul total de locatari din lista de locatari
post: lista_de_notificare va contine "numar_total_apartamente" aleator alese din lista_locatari
*/
void ListaDeNotificare::genereaza_lista(int numar_total_apartamente)
{
	auto lista_locatari = repo_locatari.get_lista_locatari();
	if (lista_de_notificare.size() != 0)
		goleste_lista();
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(lista_locatari.begin(), lista_locatari.end(), std::default_random_engine(seed));
	for (const auto &locatar_curent : lista_locatari)
	{
		if (numar_total_apartamente == 0)
			break;
		lista_de_notificare.push_back(locatar_curent);
		numar_total_apartamente--;
	}

	notifica();
}

//functie care returneaza numarul de elemente din lista_de_notificare
int ListaDeNotificare::get_dimensiune() noexcept
{
	return lista_de_notificare.size();
}

//functie care returneaza lista_de_notificare
std::vector<Locatar>& ListaDeNotificare::get_lista() noexcept
{
	return lista_de_notificare;
}
