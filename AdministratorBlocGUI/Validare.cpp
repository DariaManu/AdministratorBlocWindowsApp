#include "Validare.h"

void Validare::valideaza_numar_apartament(const int numar_apartament)
{
	if (numar_apartament <= 0)
		throw ExceptieValidare("Date de intrare gresite!\n");
}

void Validare::valideaza_nume_proprietar(const std::string & nume_proprietar)
{
	if (nume_proprietar == "")
		throw ExceptieValidare("Date de intrare gresite!\n");
}

void Validare::valideaza_suprafata(const int suprafata)
{
	if (suprafata <= 0)
		throw ExceptieValidare("Date de intrare gresite!\n");
}

void Validare::valideaza_tip_apartament(const std::string & tip_apartament)
{
	if (tip_apartament == "")
		throw ExceptieValidare("Date de intrare gresite!\n");
}
