#include "Teste.h"
#include <assert.h>
#include <vector>
#include <map>
#include "Locatar.h"
#include "RepoLocatari.h"
#include "ServiceLocatari.h"
#include "VectorDinamic.h"
#include "Validare.h"
#include "FileRepoLocatari.h"
#include "FakeRepository.h"
#include <fstream>

//functie de test pentru domeniul aplicatiei - pentru Locatar
void ruleaza_teste_domeniu()
{
	Locatar locatar1{ 10, "a", 10000, "garsoniera" };
	assert(locatar1.get_numar_apartament() == 10);
	assert(locatar1.get_nume_proprietar() == "a");
	assert(locatar1.get_suprafata() == 10000);
	assert(locatar1.get_tip_apartament() == "garsoniera");

	locatar1.set_nume_proprietar("b");
	assert(locatar1.get_nume_proprietar() == "b");
	locatar1.set_suprafata(10001);
	assert(locatar1.get_suprafata() == 10001);
	locatar1.set_tip_apartament("penthouse");
	assert(locatar1.get_tip_apartament() == "penthouse");
}

//functie de test pentru adaugarea din repo
void ruleaza_teste_repo_adauga()
{
	RepoLocatari repo_locatari;
	Locatar locatar1{ 10, "a", 1000, "garsoniera" };
	Locatar locatar2{ 11, "b", 1001, "penthouse" };
	Locatar locatar3{ 12, "c", 1002, "castel" };
	
	repo_locatari.adauga_locatar(locatar1);
	assert(repo_locatari.get_numar_locatari() == 1);
	try {
		repo_locatari.adauga_locatar(locatar1);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar existent!\n");
	}
	
	assert(repo_locatari.get_numar_locatari() == 1);

	
	repo_locatari.adauga_locatar(locatar2);
	repo_locatari.adauga_locatar(locatar3);
	assert(repo_locatari.get_numar_locatari() == 3);

	auto pozitie_locatar_cautat = repo_locatari.cauta_locatar(11);
	assert(pozitie_locatar_cautat == 1);
	Locatar locatar_inexistent{ 20, "x", 20000, "asdf" };
	try {
		pozitie_locatar_cautat = repo_locatari.cauta_locatar(20);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}

}

//functie de test pentru functiile de modificare din repo
void ruleaza_teste_repo_modifica()
{
	RepoLocatari repo_locatari;
	Locatar locatar{ 10, "a", 10000, "penthouse" };
	repo_locatari.adauga_locatar(locatar);
	assert(repo_locatari.get_numar_locatari() == 1);
	auto lista_locatari1 = repo_locatari.get_lista_locatari();
	assert(lista_locatari1.at(0).get_nume_proprietar() == "a");
	assert(lista_locatari1.at(0).get_suprafata() == 10000);
	assert(lista_locatari1.at(0).get_tip_apartament() == "penthouse");

	repo_locatari.modifica_nume_proprietar(10, "b");
	repo_locatari.modifica_suprafata_apartament(10, 10001);
	repo_locatari.modifica_tip_apartament(10, "garsoniera");

	auto lista_locatari2 = repo_locatari.get_lista_locatari();

	assert(lista_locatari2.at(0).get_nume_proprietar() == "b");
	assert(lista_locatari2.at(0).get_suprafata() == 10001);
	assert(lista_locatari2.at(0).get_tip_apartament() == "garsoniera");

	try {
		repo_locatari.modifica_nume_proprietar(11, "c");
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
	
	try {
		repo_locatari.modifica_suprafata_apartament(11, 10001);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
	
	try {
		repo_locatari.modifica_tip_apartament(11, "garsoniera");
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
	

}

//functie de test pentru functia de stergere din repo
void ruleaza_teste_repo_sterge()
{
	RepoLocatari repo_locatari;
	Locatar locatar1{ 10, "a", 1000, "garsoniera" };
	Locatar locatar2{ 11, "b", 1001, "penthouse" };
	Locatar locatar3{ 12, "c", 1002, "castel" };

	repo_locatari.adauga_locatar(locatar1);
	repo_locatari.adauga_locatar(locatar2);
	repo_locatari.adauga_locatar(locatar3);
	assert(repo_locatari.get_numar_locatari() == 3);
	
	int pozitie_locatar_cautat{ -1 };
	repo_locatari.sterge_locatar(11);
	assert(repo_locatari.get_numar_locatari() == 2);
	try {
		pozitie_locatar_cautat = repo_locatari.cauta_locatar(11);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
	
	repo_locatari.sterge_locatar(10);
	assert(repo_locatari.get_numar_locatari() == 1);
	try {
		pozitie_locatar_cautat = repo_locatari.cauta_locatar(10);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}

	repo_locatari.sterge_locatar(12);
	assert(repo_locatari.get_numar_locatari() == 0);
	try {
		pozitie_locatar_cautat = repo_locatari.cauta_locatar(12);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
	
	try {
		repo_locatari.sterge_locatar(12);
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
	
}


//functie de test pentru functia de adauagare din service
void ruleaza_teste_service_adauga()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(10, "a", 1000, "penthouse");
	try {
		service_locatari.service_adauga_locatar(10, "a", 1000, "penthouse");
	}catch (const ExceptieRepo &exceptie) {
		assert(exceptie.get_mesaj() == "Locatar existent!\n");
	}
	
	assert(service_locatari.service_get_numar_locatari() == 1);

	auto lista_locatari = service_locatari.service_get_lista_locatari();
	const int pozitie_locatar_cautat = service_locatari.service_cauta_locatar(10);
	assert(pozitie_locatar_cautat == 0);
	assert(lista_locatari.at(0).get_nume_proprietar() == "a");
}

//functie de test pentru functiile de modificare din service
void ruleaza_teste_service_modifica()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(10, "a", 1000, "penthouse");

	service_locatari.service_modifica_nume_proprietar(10, "b");
	service_locatari.service_modifica_suprafata_apartament(10, 1001);
	service_locatari.service_modifica_tip_apartament(10, "garsoniera");
	
	auto lista_locatari = service_locatari.service_get_lista_locatari();

	assert(lista_locatari.at(0).get_nume_proprietar() == "b");
	assert(lista_locatari.at(0).get_suprafata() == 1001);
	assert(lista_locatari.at(0).get_tip_apartament() == "garsoniera");

}

//functie de test pentru functia de stergere din service
void ruleaza_teste_service_sterge()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };

	service_locatari.service_adauga_locatar(10, "a", 1000, "penthouse");
	auto lista_locatari1 = service_locatari.service_get_lista_locatari();

	assert(lista_locatari1.size() == 1);
	assert(service_locatari.service_get_numar_locatari() == 1);

	service_locatari.service_sterge_locatar(10);
	
	auto lista_locatari2 = service_locatari.service_get_lista_locatari();
	assert(lista_locatari2.size() == 0);
	assert(service_locatari.service_get_numar_locatari() == 0);
}

//functie de test pentru filtrarea dupa tipul apartamentului
void ruleaza_teste_service_filtrare_tip_apartament()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(10, "a", 1000, "garsoniera");
	service_locatari.service_adauga_locatar(11, "b", 1001, "penthouse");
	service_locatari.service_adauga_locatar(12, "c", 1002, "garsoniera");

	auto lista_locatari = service_locatari.service_get_lista_locatari();
	std::vector<Locatar> lista_locatari_filtrata;
	assert(lista_locatari.size() == 3);
	assert(lista_locatari_filtrata.size() == 0);

	service_locatari.service_filtrare_dupa_tip_apartament(lista_locatari_filtrata, "garsoniera");
	assert(lista_locatari_filtrata.size() == 2);
	assert(lista_locatari.size() == 3);

	std::vector<Locatar> lista_locatari_filtrata1;
	service_locatari.service_filtrare_dupa_tip_apartament(lista_locatari_filtrata1, "penthouse");
	assert(lista_locatari_filtrata1.size() == 1);
	assert(lista_locatari.size() == 3);

	std::vector<Locatar> lista_locatari_filtrata2;
	service_locatari.service_filtrare_dupa_tip_apartament(lista_locatari_filtrata2, "castel");
	assert(lista_locatari_filtrata2.size() == 0);
	assert(lista_locatari.size() == 3);
}

//functie de test pentru filtrarea dupa suprafata apartamentului
void ruleaza_teste_service_filtrare_dupa_suprafata()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(10, "a", 1000, "garsoniera");
	service_locatari.service_adauga_locatar(11, "b", 1001, "penthouse");
	service_locatari.service_adauga_locatar(12, "c", 1002, "garsoniera");

	auto lista_locatari = service_locatari.service_get_lista_locatari();
	std::vector<Locatar> lista_locatari_filtrata1;

	service_locatari.service_filtrare_dupa_suprafata(lista_locatari_filtrata1, 1001);
	assert(lista_locatari_filtrata1.size() == 2);
	assert(lista_locatari.size() == 3);

	std::vector<Locatar> lista_locatari_filtrata2;
	service_locatari.service_filtrare_dupa_suprafata(lista_locatari_filtrata2, 1000);
	assert(lista_locatari_filtrata2.size() == 1);
	assert(lista_locatari.size() == 3);

	std::vector<Locatar> lista_locatari_filtrata3;
	service_locatari.service_filtrare_dupa_suprafata(lista_locatari_filtrata3, 900);
	assert(lista_locatari_filtrata3.size() == 0);
	assert(lista_locatari.size() == 3);
}

//functie de test pentru sortarea dupa numele proprietarului si pentru sortarea dupa suprafata
void ruleaza_teste_sortare1()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(10, "c", 1001, "garsoniera");
	service_locatari.service_adauga_locatar(11, "a", 1000, "penthouse");
	service_locatari.service_adauga_locatar(12, "b", 1002, "airbnb");

	auto lista_sortata1 = service_locatari.service_get_lista_locatari();
	service_locatari.sortare_dupa_nume(lista_sortata1);
	assert(lista_sortata1.at(0).get_nume_proprietar() == "a");
	assert(lista_sortata1.at(1).get_nume_proprietar() == "b");
	assert(lista_sortata1.at(2).get_nume_proprietar() == "c");

	auto lista_sortata2 = service_locatari.service_get_lista_locatari();
	service_locatari.sortare_dupa_suprafata(lista_sortata2);
	assert(lista_sortata2.at(0).get_suprafata() == 1000);
	assert(lista_sortata2.at(1).get_suprafata() == 1001);
	assert(lista_sortata2.at(2).get_suprafata() == 1002);
}

//functie de test pentru sortarea dupa tipul apartamentului si suprafata
void ruleaza_teste_sortare2()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(12, "b", 1002, "airbnb");
	service_locatari.service_adauga_locatar(13, "d", 1003, "sky");
	service_locatari.service_adauga_locatar(10, "c", 1001, "penthouse");
	service_locatari.service_adauga_locatar(11, "a", 1000, "penthouse");

	auto lista_sortata = service_locatari.service_get_lista_locatari();
	service_locatari.sortare_dupa_tip_si_suprafata(lista_sortata);
	assert(lista_sortata.at(0).get_nume_proprietar() == "b");
	assert(lista_sortata.at(1).get_nume_proprietar() == "a");
	assert(lista_sortata.at(2).get_nume_proprietar() == "c");
	assert(lista_sortata.at(3).get_nume_proprietar() == "d");
}

void ruleaza_teste_frecvente_aparitii()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(12, "b", 1002, "airbnb");
	service_locatari.service_adauga_locatar(13, "d", 1000, "sky");
	service_locatari.service_adauga_locatar(10, "c", 1002, "penthouse");
	service_locatari.service_adauga_locatar(11, "a", 1000, "penthouse");
	std::map<int, int> frecvente_suprafete;
	service_locatari.frecventa_suprafete(frecvente_suprafete);
	assert(frecvente_suprafete[1000] == 2);
	assert(frecvente_suprafete[1002] == 2);
}

//functie de test pentru vectorul dinamic
void ruleaza_teste_vector_dinamic()
{
	VectorDinamic<Locatar> v1;
	assert(v1.get_dimensiune() == 0);
	Locatar locatar1{ 10, "a", 1000, "garsoniera" };
	Locatar locatar2{ 11, "b", 1001, "penthouse" };
	Locatar locatar3{ 12, "c", 1002, "castel" };
	v1.adauga_final(locatar1);
	v1.adauga_final(locatar2);
	v1.adauga_final(locatar3);
	assert(v1.get_dimensiune() == 3);
	VectorDinamic<Locatar> v2 = v1;
	assert(v2.get_dimensiune() == 3);
	v1.sterge_pozitie(1);
	assert(v1.get_dimensiune() == 2);
	assert(v2.get_dimensiune() == 3);
	assert(v1.get_element(0).get_nume_proprietar() == "a");
	assert(v1.get_element(1).get_nume_proprietar() == "c");
	while (v2.get_dimensiune() != 0)
	{
		v2.sterge_pozitie(0);
	}
	assert(v2.get_dimensiune() == 0);
	v2.adauga_final(locatar1);
	assert(v2.get_dimensiune() == 1);
}


//functie de test pentru validarea datelor
void ruleaza_teste_validare()
{
	const int numar_apartament{ 26 };
	std::string nume_proprietar{ "a" };
	const int suprafata{ 10000 };
	std::string tip_apartament{ "garsoniera" };
	Validare validator;

	validator.valideaza_numar_apartament(numar_apartament);
	validator.valideaza_nume_proprietar(nume_proprietar);
	validator.valideaza_suprafata(suprafata);
	validator.valideaza_tip_apartament(tip_apartament);

	const int numar_apartament_invalid{ -10 };
	std::string nume_proprietar_invalid{ "" };
	const int suprafata_invalida{ -100 };
	std::string tip_apartament_invalid{ "" };

	try {
		validator.valideaza_numar_apartament(numar_apartament_invalid);
	}catch (const ExceptieValidare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Date de intrare gresite!\n");
	}

	try {
		validator.valideaza_nume_proprietar(nume_proprietar_invalid);
	}catch (const ExceptieValidare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Date de intrare gresite!\n");
	}

	try {
		validator.valideaza_suprafata(suprafata_invalida);
	}catch (const ExceptieValidare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Date de intrare gresite!\n");
	}

	try {
		validator.valideaza_tip_apartament(tip_apartament_invalid);
	}catch (const ExceptieValidare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Date de intrare gresite!\n");
	}
}

//functie de test pentru lista de notificare
void ruleaza_teste_lista_notificare()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(12, "b", 1002, "airbnb");
	service_locatari.service_adauga_locatar(13, "d", 1003, "sky");
	service_locatari.service_adauga_locatar(10, "c", 1001, "penthouse");
	service_locatari.service_adauga_locatar(11, "a", 1000, "penthouse");

	const auto &lista_locatari = service_locatari.service_get_lista_locatari();
	service_locatari.genereaza_lista_notificare(2);
	const auto &lista_notificare = service_locatari.get_lista_notificare();

	assert(lista_locatari.size() == 4);
	assert(lista_notificare.size() == 2);

	service_locatari.genereaza_lista_notificare(3);
	assert(lista_notificare.size() == 3);

	service_locatari.goleste_lista_notificare();
	assert(service_locatari.get_dimensiune_lista_notificare() == 0);

	try {
		service_locatari.goleste_lista_notificare();
	}catch (const ExceptieListaNotificare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Lista de notificare este deja vida");
	}

	service_locatari.adauga_locatar_in_lista_notificare(13);
	assert(lista_notificare.size() == 1);

	try {
		service_locatari.adauga_locatar_in_lista_notificare(13);
	}catch (const ExceptieListaNotificare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Locatar existent in lista de notificare");
	}

	try {
		service_locatari.adauga_locatar_in_lista_notificare(20);
	}catch (const ExceptieListaNotificare &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Locatar inexistent in lista de locatari");
	}

	assert(lista_notificare.size() == 1);
}

void ruleaza_teste_export_lista_notificare()
{
	std::ofstream fisier("testListaNotificare.txt", std::ios::trunc);
	fisier.close();
	FileRepoLocatari repo_locatari{ "testListaNotificare.txt" };
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(12, "b", 1002, "airbnb");
	service_locatari.service_adauga_locatar(13, "d", 1003, "sky");
	service_locatari.service_adauga_locatar(10, "c", 1001, "penthouse");
	service_locatari.service_adauga_locatar(11, "a", 1000, "penthouse");

	service_locatari.adauga_locatar_in_lista_notificare(10);
	service_locatari.adauga_locatar_in_lista_notificare(12);
	assert(service_locatari.get_dimensiune_lista_notificare() == 2);
	std::ofstream fisier_export("testExport.txt", std::ios::trunc);
	fisier_export.close();
	service_locatari.export_lista_notificare("testExport.txt");
	
}

void ruleaza_teste_undo()
{
	RepoLocatari repo_locatari;
	Validare validator;
	ListaDeNotificare lista_de_notificare{ repo_locatari };
	ServiceLocatari service_locatari{ repo_locatari, validator, lista_de_notificare };
	service_locatari.service_adauga_locatar(12, "b", 1002, "airbnb");
	service_locatari.service_modifica_nume_proprietar(12, "a");
	service_locatari.service_modifica_suprafata_apartament(12, 1000);
	service_locatari.service_modifica_tip_apartament(12, "penthouse");
	service_locatari.service_sterge_locatar(12);
	assert(service_locatari.service_get_numar_locatari() == 0);

	service_locatari.undo();
	assert(service_locatari.service_get_numar_locatari() == 1);
	const Locatar &locatar1 = repo_locatari.get_locatar(0);
	assert(locatar1.get_nume_proprietar() == "a");
	assert(locatar1.get_suprafata() == 1000);
	assert(locatar1.get_tip_apartament() == "penthouse");

	service_locatari.undo();
	const Locatar &locatar2 = repo_locatari.get_locatar(0);
	assert(locatar2.get_tip_apartament() == "airbnb");

	service_locatari.undo();
	const Locatar &locatar3 = repo_locatari.get_locatar(0);
	assert(locatar3.get_suprafata() == 1002);

	service_locatari.undo();
	const Locatar &locatar4 = repo_locatari.get_locatar(0);
	assert(locatar4.get_nume_proprietar() == "b");

	service_locatari.undo();
	assert(service_locatari.service_get_numar_locatari() == 0);

	try {
		service_locatari.undo();
	}catch (const ExceptieService &exceptie) {
		assert(true);
		assert(exceptie.get_mesaj() == "Nu se mai poate face undo!\n");
	}
}

//functie de test pentru filerepo
void ruleaza_teste_repo_fisier()
{
	std::ofstream fisier("testLocatari.txt", std::ios::trunc);
	fisier.close();
	FileRepoLocatari repo_locatari1{ "testLocatari.txt" };
	Locatar locatar{ 10, "a", 1000, "b" };
	repo_locatari1.adauga_locatar(locatar);
	assert(repo_locatari1.get_numar_locatari() == 1);

	FileRepoLocatari repo_locatari2{ "testLocatari.txt" };
	auto locatar_cautat = repo_locatari2.get_locatar(0);
	assert(locatar_cautat.get_nume_proprietar() == "a");
	try {
		repo_locatari1.adauga_locatar(locatar);
	}catch (const ExceptieRepo& exceptie) {
		assert(exceptie.get_mesaj() == "Locatar existent!\n");
	}

	repo_locatari2.modifica_nume_proprietar(10, "z");
	locatar_cautat = repo_locatari2.get_locatar(0);
	assert(locatar_cautat.get_nume_proprietar() == "z");

	repo_locatari2.modifica_suprafata_apartament(10, 2000);
	locatar_cautat = repo_locatari2.get_locatar(0);
	assert(locatar_cautat.get_suprafata() == 2000);

	repo_locatari2.modifica_tip_apartament(10, "y");
	locatar_cautat = repo_locatari2.get_locatar(0);
	assert(locatar_cautat.get_tip_apartament() == "y");

	repo_locatari2.sterge_locatar(10);
	assert(repo_locatari2.get_numar_locatari() == 0);
	try {
		repo_locatari2.cauta_locatar(10);
	}catch (const ExceptieRepo& exceptie) {
		assert(exceptie.get_mesaj() == "Locatar inexistent!\n");
	}
		
}

void Test_Add_ValidLocatar_throwsException()
{
	FakeRepository repo_fake;
	ListaDeNotificare lista_de_notificare{ repo_fake };
	Validare validator;
	ServiceLocatari service_locatari{ repo_fake, validator, lista_de_notificare };
	try {
		service_locatari.service_adauga_locatar(12, "a", 1000, "a");
		assert(false);
	}
	catch (const ExceptieRepo& exceptie)
	{
		assert(exceptie.get_mesaj() == "Fail!\n");
	}

}

//functie care ruleaza toate testele
void ruleaza_toate_testele()
{
	ruleaza_teste_domeniu();
	
	ruleaza_teste_repo_adauga();
	ruleaza_teste_repo_modifica();
	ruleaza_teste_repo_sterge();
	
	ruleaza_teste_service_adauga();
	ruleaza_teste_service_modifica();
	ruleaza_teste_service_sterge();
	ruleaza_teste_service_filtrare_tip_apartament();
	ruleaza_teste_service_filtrare_dupa_suprafata();
	ruleaza_teste_sortare1();
	ruleaza_teste_sortare2();
	ruleaza_teste_frecvente_aparitii();
	
	ruleaza_teste_vector_dinamic();

	ruleaza_teste_validare();

	ruleaza_teste_lista_notificare();
	ruleaza_teste_export_lista_notificare();

	ruleaza_teste_undo();

	ruleaza_teste_repo_fisier();
	
	Test_Add_ValidLocatar_throwsException();

}
