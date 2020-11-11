#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compute_shapley.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    compute_shapley shapley;

}

MainWindow::~MainWindow()
{
    delete ui;
}

