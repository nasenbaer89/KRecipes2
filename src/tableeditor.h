#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QSqlTableModel>

class TableEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TableEditor(QWidget *parent = 0);
    
private slots:
    void create_tables(QString tablename = "all");
    
private:
    float getDbVersion();
    float db_version;
    float db_version_latest;
    QSqlDatabase db;
    
    void portOldDatabse();
    
    QPushButton *createButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
};
    
#endif