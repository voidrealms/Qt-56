#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tableView);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("LOCALHOST\\SQLEXPRESS");
    db.setDatabaseName("mydsn32");

    db.open();

    model = new QSqlRelationalTableModel(this);
    model->setTable("People");
    model->setRelation(0,QSqlRelation("wages","id","salary"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}
