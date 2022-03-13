#include "Undo.h"

/*functie de undo pentru metoda adauga din repository
pre: -
post: lista de locatari nu va mai contine locatarul
*/
void UndoAdauga::doUndo()
{
	repo_locatari.sterge_locatar(locatar.get_numar_apartament());
}

/*functie de undo pentru metoda sterge din repository
pre: -
post: lista de locatari va contine din nou locatarul
*/
void UndoSterge::doUndo()
{
	repo_locatari.adauga_locatar(locatar);
}

/*functie de undo pentru metoda modifica_nume din repository
pre: -
post: locatarul din lista de locatari va avea numele de dinainte de ultima modificare a numelui
*/
void UndoModificaNume::doUndo()
{
	repo_locatari.modifica_nume_proprietar(locatar.get_numar_apartament(), locatar.get_nume_proprietar());
}

/*functie de undo pentru metoda modifica_suprafata din repository
pre: -
post: locatarul din lista de locatari va avea suprafata apartamentului de dinainte de ultima modificare a suprafetei apartamentului
*/
void UndoModificaSuprafata::doUndo()
{
	repo_locatari.modifica_suprafata_apartament(locatar.get_numar_apartament(), locatar.get_suprafata());
}

/*functie de undo pentru metoda modifica_tip din repository
pre: -
post: locatarul din lista de locatari va avea tipul apartamentului de dinainte de ultima modificare a tipului apartamentului
*/
void UndoModificaTip::doUndo()
{
	repo_locatari.modifica_tip_apartament(locatar.get_numar_apartament(), locatar.get_tip_apartament());
}
