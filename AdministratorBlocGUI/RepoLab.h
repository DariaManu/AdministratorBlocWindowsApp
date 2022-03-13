#pragma once
#include "RepoAbstract.h"
#include <vector>
#include <map>

class ExceptieRepoLab {
private:
	std::string mesaj;

public:
	ExceptieRepoLab(std::string mesaj) : mesaj{ mesaj } {

	}

	std::string get_mesaj() const
	{
		return mesaj;
	}
};

class RepoLab : public RepoAbstract
{
private:
	std::vector<Locatar> vector_locatari;
	std::map<int, Locatar> lista_locatari;
	int probabilitate;
	int numar_locatari = 0;

public:
	RepoLab(int probabilitate) :probabilitate{ probabilitate } {

	};

	void adauga_locatar(const Locatar& locatar) override;

	int cauta_locatar(int numar_apartament) override;

	void modifica_nume_proprietar(int numar_apartament, const std::string& nume_nou) override;

	void modifica_suprafata_apartament(int numar_apartament, int suprafata_noua) override;

	void modifica_tip_apartament(int numar_apartament, const std::string& tip_apartament_nou) override;

	void sterge_locatar(int numar_apartament) override;

	const std::vector<Locatar>& get_lista_locatari() noexcept override;

	int get_numar_locatari() noexcept override;

	const Locatar& get_locatar(int pozitie) override;
};

