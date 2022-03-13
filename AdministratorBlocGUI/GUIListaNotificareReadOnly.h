#pragma once
#include "ListaDeNotificare.h"
#include "ObserverObservable.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>

class GUIListaNotificareReadOnly : public QWidget, public Observer
{
private:
	ListaDeNotificare& lista_de_notificare;

public:

	GUIListaNotificareReadOnly(ListaDeNotificare& lista_de_notificare) : lista_de_notificare{ lista_de_notificare } {
		lista_de_notificare.adauga_observer(this);
		repaint();
	};

	void paintEvent(QPaintEvent* eveniment) override{
		QPainter painter{ this };

		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> const dist(0, 300);

		painter.setFont(QFont("TimesNewRoman", 20));
		painter.setPen(Qt::darkBlue);
		painter.drawText(rect(), Qt::AlignTop | Qt::AlignLeft, "Numar apartamente in lista de notificare:");
		painter.setPen(Qt::red);
		painter.drawText(rect(), Qt::AlignTop | Qt::AlignRight, QString::number(lista_de_notificare.get_dimensiune()));

		auto& apartamente_notificate = lista_de_notificare.get_lista();
		for (const auto apartament : apartamente_notificate)
		{
			const int x = dist(mt);
			const int y = dist(mt);

			int h = this->height();
			int w = this->width();
			painter.drawEllipse(0, 0, 100, 100);
			painter.drawEllipse(w-100, 0, 100, 100);
			painter.drawEllipse(0, h-100, 100, 100);
			painter.drawEllipse(w-100, h-100, 100, 100);

			int start = 10;
			painter.setPen(Qt::black);
			for (int i = 1; i < 9; i++)
			{
				painter.drawRect(start, h - i*10, 20, i*10);
				start += 40;
			}
			

			if (apartament.get_tip_apartament() == "penthouse")
				painter.drawImage(x, y, QImage("penthouse.jpg"));

			else
				if (apartament.get_tip_apartament() == "garsoniera")
					painter.drawImage(x, y, QImage("garsoniera.jpg"));
				else
					painter.fillRect(x, y, x, y, Qt::BrushStyle::Dense2Pattern);
		}
	}

	void update() override {
		repaint();
	}
};

