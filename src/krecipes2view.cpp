/*
 *
 */

#include "krecipes2view.h"
#include "../build/ui_krecipes2view.h"

Krecipes2View::Krecipes2View(QWidget *parent)
{
    ui = new Ui::Krecipes2View;
    ui->setupUi ( this );
}

Krecipes2View::~Krecipes2View()
{
    delete ui;
}
