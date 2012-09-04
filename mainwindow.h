#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString geoTag(double, double);
    QString makeLink(double, double);

public slots:
    void proceed(bool);
    void digit2Degs(double, double*, double*, double*);

    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
