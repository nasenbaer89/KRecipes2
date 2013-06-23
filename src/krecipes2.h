#ifndef KRECIPES2_H
#define KRECIPES2_H_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>

class Krecipes2 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Krecipes2(QWidget *parent = 0);
    
private slots:

    
private:
    
    QPushButton *createButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
};
    
#endif