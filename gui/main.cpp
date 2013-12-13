#include "mainwindow.h"
#include <QApplication>
#include <QMdiArea>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QFrame>
#include <QAbstractScrollArea>
#include "utils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QMainWindow w;
    QMdiArea* mdi = new QMdiArea(&w);
    w.setCentralWidget(mdi);

    test(mdi);
#ifdef FUCK
    QWidget* sww = new QWidget();
//    QFrame* sww = new QFrame();
//    QAbstractScrollArea* sww = new QAbstractScrollArea();

    QMdiSubWindow* sw = mdi->addSubWindow(sww);

    QVBoxLayout* vb1 = new QVBoxLayout();
    sww->setLayout(vb1);

    QHBoxLayout* hb1 = new QHBoxLayout();
    vb1->addLayout(hb1);

    QFormLayout* fl1= new QFormLayout();
    hb1->addLayout(fl1);
    fl1->addRow("lable1", new QLineEdit());
    fl1->addRow("lable1", new QLineEdit("za2"));
    QFormLayout* fl2= new QFormLayout();
    hb1->addLayout(fl2);
    fl2->addRow("lable1", new QLineEdit("zas"));
    fl2->addRow("lable1", new QLineEdit("za2"));

    QTableView* tab1= new QTableView(/*sww*/);
    vb1->addWidget(tab1);

    QStandardItemModel *model = new QStandardItemModel(4, 4);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }
//    filldata(model);
    tab1->setModel(model);

#endif //FUCK

    w.show();

    return a.exec();
}
