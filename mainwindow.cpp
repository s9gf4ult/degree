#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->go, SIGNAL(clicked(bool)), this, SLOT(proceed(bool)));
}

void MainWindow::proceed(bool ignore) {
    ui->output->setText("output");
}

MainWindow::~MainWindow()
{
    delete ui;
}
