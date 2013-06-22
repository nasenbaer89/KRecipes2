#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QSqlDatabase> //FIXME doesn't belong here

class TableEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TableEditor(QWidget *parent = 0);
    
private slots:

    
private:
    float getDbVersion();
    float db_version;
    float db_version_latest;
    QSqlDatabase db;
    
    void portOldDatabse();
    
    QPushButton *createButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
};
    
#endif