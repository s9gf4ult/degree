#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->go, SIGNAL(clicked(bool)), this, SLOT(proceed(bool)));
}

void MainWindow::proceed(bool ignore) {
    QString in = ui->input->text();
    QStringList splited = in.split(QRegExp("\\ *,\\ *"));
    QStringList cleared;
    foreach(QString a, splited) {
        cleared.append(a.replace(QRegExp("^\\ *"), "").replace(QRegExp("\\ *$"), ""));
    }
    if (cleared.length() != 2) {
        ui->output->setText("WTF ??? need 2 comma separeted digits");
        return;
    }
    QVector<double> doubles;
    foreach(QString a, cleared) {
        bool good = true;
        double ret = a.toDouble(&good);
        if (!good) {
            ui->output->setText(QString("Could not convert \"%1\" to double value").arg(a));
            return;
        }
        doubles.append(ret);
    };
    ui->output->setText(this->geoTag(doubles[1], doubles[0]));

}

void MainWindow::digit2Degs(double value, double *deg, double *min, double *sec)
{
    *deg = floor(value);
    double sick = value - floor(value);
    *min = floor(sick * 60);
    double sick2 = sick - (*min / 60);
    *sec = sick2 * 3600;
}


MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::geoTag(double a, double b)
{
    double deg, min, sec;
    this->digit2Degs(a, &deg, &min, &sec);
    QString aa = QString("%1 %2 %3").arg(deg).arg(min).arg(sec);
    this->digit2Degs(b, &deg, &min, &sec);
    QString bb = QString("%1 %2 %3").arg(deg).arg(min).arg(sec);
    return QString("<geo>%1 N %2 E</geo>").arg(aa).arg(bb);
}
