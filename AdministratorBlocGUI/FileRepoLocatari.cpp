#include "FileRepoLocatari.h"
#include "Locatar.h"
#include <fstream>

void FileRepoLocatari::incarca_din_fisier() 
{
	std::ifstream fisier(nume_fisier);
	while (!fisier.eof()) {
		int numar_apartament{ 0 };
		std::string nume_proprietar;
		int suprafata{ 0 };
		std::string tip_apartament;
		fisier >> numar_apartament;
		if (fisier.eof())
			break;
		fisier >> nume_proprietar;
		fisier >> suprafata;
		fisier >> tip_apartament;
		Locatar locatar{ numar_apartament, nume_proprietar.c_str(), suprafata, tip_apartament.c_str() };
		adauga_locatar(locatar);
	}
	fisier.close();
}

void FileRepoLocatari::scrie_in_fisier() 
{
	std::ofstream fisier(nume_fisier);
	for (const auto& locatar : get_lista_locatari())
	{
		fisier << locatar.get_numar_apartament();
		fisier << std::endl;
		fisier << locatar.get_nume_proprietar();
		fisier << std::endl;
		fisier << locatar.get_suprafata();
		fisier << std::endl;
		fisier << locatar.get_tip_apartament();
		fisier << std::endl;
	}
	fisier.close();
}

