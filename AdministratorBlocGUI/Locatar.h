#pragma once
#include <string>
#include <iostream>

class Locatar
{
private:
	int numar_apartament;
	std::string nume_proprietar;
	int suprafata;
	std::string tip_apartament;

public:
	Locatar(int numar_apartament, const std::string &nume_proprietar, int suprafata, const std::string &tip_apartament):
		numar_apartament{ numar_apartament }, nume_proprietar{ nume_proprietar }, suprafata{ suprafata }, tip_apartament{ tip_apartament }{
	}
	
	Locatar() noexcept = default;

	/*
	Locatar(const Locatar &ot) : numar_apartament{ ot.numar_apartament }, nume_proprietar{ ot.nume_proprietar }, suprafata{ ot.suprafata }, tip_apartament{ ot.tip_apartament }{
		std::cout << "!!!!!!!!!\n";
	}*/
	
	int get_numar_apartament() const noexcept;
	
	std::string get_nume_proprietar() const;

	int get_suprafata() const noexcept;

	std::string get_tip_apartament() const;

	void set_nume_proprietar(const std::string &nume_nou);

	void set_suprafata(const int suprafata_noua) noexcept;

	void set_tip_apartament(const std::string &tip_nou);

	~Locatar() = default;
};

