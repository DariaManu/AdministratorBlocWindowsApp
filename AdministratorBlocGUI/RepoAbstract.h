#pragma once
#include "Locatar.h"
#include <string>
#include <vector>

class RepoAbstract
{
public:
	
	virtual void adauga_locatar(const Locatar& locatar) = 0;

	virtual int cauta_locatar(int numar_apartament) = 0;

	virtual void modifica_nume_proprietar(int numar_apartament, const std::string& nume_nou) = 0;

	virtual void modifica_suprafata_apartament(int numar_apartament, int suprafata_noua) = 0;

	virtual void modifica_tip_apartament(int numar_apartament, const std::string& tip_apartament_nou) = 0;

	virtual void sterge_locatar(int numar_apartament) = 0;

	virtual const std::vector<Locatar>& get_lista_locatari() noexcept = 0;

	virtual int get_numar_locatari() noexcept = 0;

	virtual const Locatar& get_locatar(int pozitie) = 0;

	virtual ~RepoAbstract()=default;
};

