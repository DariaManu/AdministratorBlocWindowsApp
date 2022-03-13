#include "RepoLab.h"
#include <random>
#include "RepoLocatari.h"

void RepoLab::adauga_locatar(const Locatar& locatar)
{
    std::mt19937 mt{ std::random_device{}() }; 
    std::uniform_int_distribution<> const dist(0, 10); 
    const int nr_aleator = dist(mt);
    if (nr_aleator == probabilitate)
        throw(ExceptieRepo("Probabilitate!\n"));
    lista_locatari[numar_locatari] = locatar;
    numar_locatari++;
}

int RepoLab::cauta_locatar(int numar_apartament)
{
    for (const auto& locatar_curent : lista_locatari)
    {
        if (locatar_curent.second.get_numar_apartament() == numar_apartament)
            return locatar_curent.first;
    }
}

void RepoLab::modifica_nume_proprietar(int numar_apartament, const std::string& nume_nou)
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> const dist(0, 10);
    const int nr_aleator = dist(mt);
    if (nr_aleator == probabilitate)
        throw(ExceptieRepo("Probabilitate!\n"));
    for (auto& locatar_curent : lista_locatari)
    {
        if (locatar_curent.second.get_numar_apartament() == numar_apartament)
        {
            locatar_curent.second.set_nume_proprietar(nume_nou);
            return;
        }
    }
}

void RepoLab::modifica_suprafata_apartament(int numar_apartament, int suprafata_noua)
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> const dist(0, 10 - 1);
    const int nr_aleator = dist(mt);
    if (nr_aleator == probabilitate)
        throw(ExceptieRepo("Probabilitate!\n"));
    for (auto& locatar_curent : lista_locatari)
    {
        if (locatar_curent.second.get_numar_apartament() == numar_apartament)
        {
            locatar_curent.second.set_suprafata(suprafata_noua);
            return;
        }
    }
}

void RepoLab::modifica_tip_apartament(int numar_apartament, const std::string& tip_apartament_nou)
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> const dist(0, 10 - 1);
    const int nr_aleator = dist(mt);
    if (nr_aleator == probabilitate)
        throw(ExceptieRepo("Probabilitate!\n"));
    for (auto& locatar_curent : lista_locatari)
    {
        if (locatar_curent.second.get_numar_apartament() == numar_apartament)
        {
            locatar_curent.second.set_tip_apartament(tip_apartament_nou);
            return;
        }
    }
}

void RepoLab::sterge_locatar(int numar_apartament)
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> const dist(0, 10 - 1);
    const int nr_aleator = dist(mt);
    if (nr_aleator == probabilitate)
        throw(ExceptieRepo("Probabilitate!\n"));
    for (const auto& locatar_curent : lista_locatari)
    {
        if (locatar_curent.second.get_numar_apartament() == numar_apartament)
        {
            lista_locatari.erase(locatar_curent.first);
            numar_locatari--;
            return;
        }
    }
}

const std::vector<Locatar>& RepoLab::get_lista_locatari() noexcept
{
    for (auto& locatar_curent : vector_locatari)
    {
        locatar_curent;
        vector_locatari.erase(vector_locatari.begin());
    }

    for (const auto& locatar_curent : lista_locatari)
    {
         vector_locatari.push_back(locatar_curent.second);
    }
    return vector_locatari;
}

int RepoLab::get_numar_locatari() noexcept
{
    return lista_locatari.size();
}

const Locatar& RepoLab::get_locatar(int pozitie)
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> const dist(0, 10 - 1);
    const double nr_aleator = dist(mt);
    if (nr_aleator == probabilitate)
        throw(ExceptieRepo("Probabilitate!\n"));
    return lista_locatari[pozitie];
}
