#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "RepoLocatari.h"
#include "Locatar.h"
#include "Locatar.h"
#include "VectorDinamic.h"
#include "Validare.h"
#include "ListaDeNotificare.h"
#include "Undo.h"
#include "FileRepoLocatari.h"
#include "RepoAbstract.h"

//typedef bool(*FunctieComparare)(const Locatar &locatar1, const Locatar &locatar2);

class ExceptieService {
private:
	std::string mesaj;

public:
	ExceptieService(std::string mesaj) : mesaj{ mesaj } {

	}

	std::string get_mesaj() const
	{
		return mesaj;
	}
};

class ServiceLocatari
{
private:
	RepoAbstract& repo_locatari;
	Validare &validator;
	ListaDeNotificare &lista_de_notificare;
	std::vector<std::unique_ptr<ActiuneUndo>> lista_actiuni_undo;
	
public:
	ServiceLocatari(RepoAbstract &repo_locatari, Validare &validator, ListaDeNotificare &lista_de_notificare)noexcept :
		repo_locatari{ repo_locatari }, validator{ validator }, lista_de_notificare{ lista_de_notificare }{

	}

	ServiceLocatari(const ServiceLocatari &ot) = delete;

	void service_adauga_locatar(int numar_apartament, const std::string &nume_proprietar, int suprafata, const std::string &tip_apartament);

	int service_cauta_locatar(int numar_apartament);

	void service_modifica_nume_proprietar(int numar_apartament, const std::string &nume_nou);

	void service_modifica_suprafata_apartament(int numar_apartament, int suprafata_noua);

	void service_modifica_tip_apartament(int numar_apartament, const std::string &tip_apartament_nou);

	void service_sterge_locatar(int numar_apartament);

	void service_filtrare_dupa_tip_apartament(std::vector<Locatar> &lista_locatari_filtrare, const std::string &conditie_filtrare);

	void service_filtrare_dupa_suprafata(std::vector<Locatar> &lista_locatari_filtrare, int conditie_filtrare);

	//void sortare(std::vector<Locatar> &lista_locatari_sortare, bool (*compara)(const Locatar &locatar1, const Locatar &locatar2));
	void sortare(std::vector<Locatar>& lista_locatari_sortare);

	void sortare_nume(std::vector<Locatar>& lista_locatari_sortare);

	void sortare_tip_suprafata(std::vector<Locatar>& lista_locatari_sortare);

	void sortare_dupa_nume(std::vector<Locatar> &lista_locatari_sortare);

	void sortare_dupa_suprafata(std::vector<Locatar> &lista_locatari_sortare);

	void sortare_dupa_tip_si_suprafata(std::vector<Locatar> &lista_locatari_sortare);

	void frecventa_suprafete(std::map<int, int> &frecvente_suprafete);

	const std::vector<Locatar>& service_get_lista_locatari() noexcept;

	void undo();

	void adauga_locatar_in_lista_notificare(int numar_apartament);

	void goleste_lista_notificare();

	void genereaza_lista_notificare(int numar_total_apartamente);

	void export_lista_notificare(const std::string &nume_fisier);

	int get_dimensiune_lista_notificare() noexcept;

	std::vector<Locatar>& get_lista_notificare() noexcept;

	int service_get_numar_locatari() noexcept;

	~ServiceLocatari() = default;
};

