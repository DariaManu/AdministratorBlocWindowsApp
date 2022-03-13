#pragma once
#include "Locatar.h"
#include <vector>
#include <qabstractitemmodel.h>
#include <qfont.h>
#include <qbrush.h>

class MyTableModel : public QAbstractTableModel
{
private:
	std::vector<Locatar> locatari;

public:
	MyTableModel(const std::vector<Locatar>& locatari) : locatari{ locatari } {

	};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return locatari.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
		{
			Locatar locatar = locatari[index.row()];
			if (index.column() == 0)
				return QString::number(locatar.get_numar_apartament());
			if (index.column() == 1)
				return QString::fromStdString(locatar.get_nume_proprietar());
			if (index.column() == 2)
				return QString::number(locatar.get_suprafata());
			if (index.column() == 3)
				return QString::fromStdString(locatar.get_tip_apartament());
		}

		if (role == Qt::UserRole)
		{
			return locatari[index.row()].get_numar_apartament();
		}

		if (role == Qt::FontRole)
		{
			QFont font;
			font.setBold(index.row() % 2 == 1 && index.column() % 3 == 1);
			font.setUnderline(true);
			font.setItalic(index.row() % 2 == 0);

			return font;
		}

		if (role == Qt::BackgroundRole)
		{
			QBrush brush{ Qt::red };
			return brush;
		}

		/*if (role == Qt::BackgroundRole && index.column() == 3)
		{
			QBrush brush{ Qt::blue };
			return brush;
		}*/

		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal && section == 0)
				return QString("Numar apartament");

			if (orientation == Qt::Horizontal && section == 1)
				return QString("Nume proprietar");

			if (orientation == Qt::Horizontal && section == 2)
				return QString("Suprafata apartament");

			if (orientation == Qt::Horizontal && section == 3)
				return QString("Tip apartament");

			if (orientation == Qt::Vertical)
				return QString("Rand %1").arg(section);
		}

		return QVariant{};
	}

	void set_locatari(const std::vector<Locatar>& locatari)
	{
		this->locatari = locatari;
		QModelIndex inceput = createIndex(0, 0);
		QModelIndex sfarsit = createIndex(rowCount(), columnCount());
		emit dataChanged(inceput, sfarsit);
		emit layoutChanged();
	}
};

