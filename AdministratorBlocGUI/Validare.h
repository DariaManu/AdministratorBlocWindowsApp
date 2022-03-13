#pragma once
#include<string>

class ExceptieValidare
{
private:
	std::string mesaj;

public:
	ExceptieValidare(std::string mesaj) : mesaj{ mesaj } {

	}

	std::string get_mesaj() const {
		return mesaj;
	}
};

class Validare
{
public:
	Validare() = default;

	void valideaza_numar_apartament(const int numar_apartament);

	void valideaza_nume_proprietar(const std::string &nume_proprietar);

	void valideaza_suprafata(const int suprafata);

	void valideaza_tip_apartament(const std::string &tip_apartament);
	
	~Validare() = default;

};

