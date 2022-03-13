#pragma once
#include <vector>
#include <string>
#include "Locatar.h"
#include "RepoLocatari.h"
#include "RepoAbstract.h"
#include "ObserverObservable.h"

class ExceptieListaNotificare {
private:
	std::string mesaj;

public:
	ExceptieListaNotificare(std::string mesaj) : mesaj{ mesaj } {

	};

	std::string get_mesaj() const
	{
		return mesaj;
	}
};

class ListaDeNotificare : public Observable
{
private:
	std::vector<Locatar> lista_de_notificare;
	RepoAbstract &repo_locatari;

public:
	//constructorul clasei de tip ListaDeNotificare
	ListaDeNotificare(RepoAbstract &repo_locatari) noexcept: repo_locatari{ repo_locatari } {

	};

	void adauga_locatar(int numar_apartament);

	void goleste_lista();

	void genereaza_lista(int numar_total_apartamente);

	int get_dimensiune() noexcept;

	std::vector<Locatar>& get_lista() noexcept;

	~ListaDeNotificare() = default;
};

