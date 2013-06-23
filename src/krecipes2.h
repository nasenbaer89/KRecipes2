#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>

class TableEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TableEditor(QWidget *parent = 0);
    
private slots:

    
private:
    
    QPushButton *createButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
};
    
#endif