#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chart.h"
#include "analyser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::MainWindow *ui;
    ChartView *chartView;
    Analyser *analyser;
};

#endif // MAINWINDOW_H
