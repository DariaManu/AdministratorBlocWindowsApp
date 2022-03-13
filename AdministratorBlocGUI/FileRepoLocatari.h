#pragma once
#include "RepoLocatari.h"
#include <string>

class ExceptieFileRepo {
private:
	std::string mesaj;

public:
	ExceptieFileRepo(std::string mesaj) : mesaj{ mesaj } {

	}

	std::string get_mesaj() const
	{
		return mesaj;
	}
};

class FileRepoLocatari : public RepoLocatari
{
private:
	std::vector<Locatar> lista_locatari;
	std::string nume_fisier;

	void incarca_din_fisier() ;

	void scrie_in_fisier() ;

public:

	FileRepoLocatari(const std::string& nume_fisier) : nume_fisier{ nume_fisier }{
		incarca_din_fisier();
	};

	void adauga_locatar(const Locatar& locatar) override {
		RepoLocatari::adauga_locatar(locatar);
		scrie_in_fisier();
	}

	void modifica_nume_proprietar(int numar_apartament, const std::string& nume_nou) override
	{
		RepoLocatari::modifica_nume_proprietar(numar_apartament, nume_nou);
		scrie_in_fisier();
	}

	void modifica_suprafata_apartament(int numar_apartament, int suprafata_noua) override
	{
		RepoLocatari::modifica_suprafata_apartament(numar_apartament, suprafata_noua);
		scrie_in_fisier();
	}

	void modifica_tip_apartament(int numar_apartament, const std::string& tip_apartament_nou) override
	{
		RepoLocatari::modifica_tip_apartament(numar_apartament, tip_apartament_nou);
		scrie_in_fisier();
	}

	void sterge_locatar(int numar_apartament) override
	{
		RepoLocatari::sterge_locatar(numar_apartament);
		scrie_in_fisier();
	}

	/*void adauga_locatar(const Locatar& locatar) override;

	int cauta_locatar(int numar_apartament) override;

	void modifica_nume_proprietar(int numar_apartament, const std::string& nume_nou) override;

	void modifica_suprafata_apartament(int numar_apartament, int suprafata_noua) override;

	void modifica_tip_apartament(int numar_apartament, const std::string& tip_apartament_nou) override;

	void sterge_locatar(int numar_apartament) override;

	const std::vector<Locatar>& get_lista_locatari() noexcept;

	int get_numar_locatari() noexcept override;

	Locatar& get_locatar(int pozitie) override;

	~FileRepoLocatari() = default;*/
};

