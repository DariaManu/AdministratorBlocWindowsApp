#pragma once
#include "Locatar.h"
#include <vector>
#include <qabstractitemmodel.h>
#include <qfont.h>
#include <qbrush.h>

class MyListModel : public QAbstractListModel
{
private:
	std::vector<Locatar> locatari;

public:
	MyListModel(const std::vector<Locatar>& locatari) : locatari{ locatari } {

	};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return locatari.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
		{
			auto numar_apartament = locatari[index.row()].get_numar_apartament();
			auto nume_proprietar = locatari[index.row()].get_nume_proprietar();
			auto suprafata = locatari[index.row()].get_suprafata();
			auto tip_apartament = locatari[index.row()].get_tip_apartament();

			return QString::number(numar_apartament) + " " + QString::fromStdString(nume_proprietar) + " " + QString::number(suprafata) + " " + QString::fromStdString(tip_apartament);
		}

		if (role == Qt::UserRole)
		{
			return locatari[index.row()].get_numar_apartament();
		}

		if (role == Qt::FontRole)
		{
			QFont font;
			font.setBold(index.row() % 2 == 1);
			font.setItalic(index.row() % 4 == 1);
			return font;
		}

		if (role == Qt::BackgroundRole && index.row() % 3 == 0)
		{
			QBrush brush{ Qt::red };
			return brush;
		}

		return QVariant{};
	}

	void set_locatari(const std::vector<Locatar>& locatari)
	{
		this->locatari = locatari;
		QModelIndex inceput = createIndex(0, 0);
		QModelIndex sfarsit = createIndex(rowCount(), 0);
		emit dataChanged(inceput, sfarsit);
		emit layoutChanged();
	}
};

