#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AdministratorBlocGUI.h"

class AdministratorBlocGUI : public QMainWindow
{
    Q_OBJECT

public:
    AdministratorBlocGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::AdministratorBlocGUIClass ui;
};
