#ifndef KRECIPES2_H
#define KRECIPES2_H_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QAction>
#include <KDE/KXmlGuiWindow>
#include "krecipes2view.h"

class Krecipes2 : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit Krecipes2(QWidget *parent = 0);
    ~Krecipes2();

private slots:
    void showCurrentRecipes(); //FIXME from krecipesview

private:
    Krecipes2View *m_view;

    void setupActions();
    QAction *showRecipeAction;

    QPushButton *createButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
};

#endif