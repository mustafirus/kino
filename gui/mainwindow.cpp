#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QMdiArea>

void filldata( QStandardItemModel *model );

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMdiArea* centralWidget = new QMdiArea(this);
    //centralWidget->setObjectName(QStringLiteral("centralWidget"));

    //ui->setupUi(this);
    /*
     *QStandardItemModel *model = new QStandardItemModel(4, 4);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }
    filldata(model);
    ui->tableView->setModel(model);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
