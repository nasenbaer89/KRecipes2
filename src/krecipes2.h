#ifndef KRECIPES2_H
#define KRECIPES2_H_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QAction>
#include <KDE/KXmlGuiWindow>

class Krecipes2 : public KXmlGuiWindow
{
    Q_OBJECT
    
public:
    explicit Krecipes2(QWidget *parent = 0);
    
private slots:
    void showCurrentRecipes(); //FIXME from krecipesview
    
private:
    
    void setupActions();
    QAction *showRecipeAction;
    
    QPushButton *createButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
};
    
#endif