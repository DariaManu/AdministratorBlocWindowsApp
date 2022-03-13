#pragma once
#include "ServiceLocatari.h"

class UI
{
private:
	ServiceLocatari &service_locatari;

public:
	UI(ServiceLocatari &service_locatari) noexcept : service_locatari{ service_locatari } {
	}
	
	void meniu();

	void ui_adauga_locatar();

	void ui_cauta_locatar();

	void ui_modifica_nume_proprietar();

	void ui_modifica_suprafata();

	void ui_modifica_tip_apartament();

	void ui_sterge_locatar();

	void ui_filtreaza_dupa_tip_apartament();

	void ui_filtreaza_dupa_suprafata();

	void ui_sorteaza_dupa_nume();

	void ui_sorteaza_dupa_suprafata();

	void ui_sorteaza_dupa_tip_si_suprafata();

	void ui_afiseaza_frecvente_suprafete();

	void ui_afiseaza_locatari();

	void ui_adauga_in_lista_notificare();

	void ui_goleste_lista_notificare();

	void ui_genereaza_lista_notificare();

	void ui_afiseaza_lista_notificare();

	void ui_export_lista_notificare();

	void ui_undo();

	void ruleaza_aplicatia();

	~UI() = default;
};

