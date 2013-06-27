/*
 *
 */

#ifndef KRECIPES2VIEW_H
#define KRECIPES2VIEW_H

#include <QWidget>

namespace Ui
{
class Krecipes2View;
}

class Krecipes2View : public QWidget
{
    Q_OBJECT
public:
    Krecipes2View(QWidget *parent);
    ~Krecipes2View();

private:
    Ui::Krecipes2View* ui;

};

#endif // KRECIPES2VIEW_H
