#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     QObject::connect(ui->convert, SIGNAL(toggled(bool)), this, SLOT(proceed(bool)));
}

void MainWindow::proceed(bool ignore) {
    QString in = ui->input->text();
    QStringList splited = in.split(QRegExp("\\ *,\\ *"));
    QStringList cleared;
    foreach(QString a, splited) {
        cleared.append(a.replace(QRegExp("^\\ *"), "").replace(QRegExp("\\ *$"), ""));
    }
    if (cleared.length() != 2) {
        ui->link->setPlainText("WTF ??? need 2 comma separeted digits");
        return;
    }
    QVector<double> doubles;
    foreach(QString a, cleared) {
        bool good = true;
        double ret = a.toDouble(&good);
        if (!good) {
            ui->link->setPlainText(QString("Could not convert \"%1\" to double value").arg(a));
            return;
        }
        doubles.append(ret);
    };
    ui->link->clear();
    ui->link->insertPlainText(this->geoTag(doubles[1], doubles[0]));
    ui->link->insertPlainText("\n");
    ui->link->insertPlainText(this->makeLink(doubles[1], doubles[0]));

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
    return QString("<geo>%1 %2 %3 %4</geo>").arg(aa).arg(ui->north->isChecked() ? "N" : "S").arg(bb).arg(ui->east->isChecked() ? "E" : "W");
}

QString MainWindow::makeLink(double lat, double lon)
{
    QString name = this->ui->name->text();
    if (name.isEmpty()) {
        return "WTF?? Need article name to fill this correctly";
    }
    QString url = this->ui->siteurl->text();
    if (url.isEmpty()) {
        return "Site URL must not be empty";
    }
    double latdeg, latmin, latsec;
    double londeg, lonmin, lonsec;
    this->digit2Degs(lat, &latdeg, &latmin, &latsec);
    this->digit2Degs(lon, &londeg, &lonmin, &lonsec);
    QString link = QString("%1/Special:Geo?subaction=near&dist=0.5&latdeg=%2&latmin=%3&latsec=%4&latns=%5&londeg=%6&lonmin=%7&lonsec=%8&lonew=%9&ignore=%10")
            .arg(url)
            .arg(latdeg)
            .arg(latmin)
            .arg(latsec)
            .arg(ui->north->isChecked() ? "N" : "S")
            .arg(londeg)
            .arg(lonmin)
            .arg(lonsec)
            .arg(ui->west->isChecked() ? "W" : "E")
            .arg(name);
    return QString::fromUtf8("<pagesidebar>\n* Рядом находится\n** %1 | Смотреть\n</pagesidebar>")
            .arg(link);


}
