#include "Locatar.h"

/*returneaza numarul apartamentului locatarului
pre: -
post: numar_apartament - intreg
*/
int Locatar::get_numar_apartament() const noexcept
{
	return numar_apartament;
}

/*returneaza numele proprietarului apartamentului
pre: -
post: nume_proprietar - string
*/
std::string Locatar::get_nume_proprietar() const
{
	return nume_proprietar;
}

/*returneaza suprafata apartamentului locatarului
pre: -
post: suprafata - intreg
*/
int Locatar::get_suprafata() const noexcept
{
	return suprafata;
}

/*returneaza tipul apartamentului locatarului
pre: -
post: tip_apartament - string
*/
std::string Locatar::get_tip_apartament() const
{
	return tip_apartament;
}

/*modifica numele proprietarului apartamentului
pre: nume_nou - referinta la un string
post: nume_proprietar = nume_nou
*/
void Locatar::set_nume_proprietar(const std::string &nume_nou)
{
	this->nume_proprietar = nume_nou;
}

/*modifica suprafata apartamentului locatarului
pre: -
post: suprafata = suprafata_nou
*/
void Locatar::set_suprafata(const int suprafata_noua) noexcept
{
	this->suprafata = suprafata_noua;
}

/*modifica tipul apartamentului locatarului
pre: -
post: tip_apartament = tip_nou
*/
void Locatar::set_tip_apartament(const std::string &tip_nou)
{
	this->tip_apartament = tip_nou;
}
