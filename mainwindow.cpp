#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chart.h"
#include <QtCharts/QChartView>
#include "analyser.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chartView = new ChartView(this);
    analyser = new Analyser(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chartView;
    delete analyser;
}



void MainWindow::on_pushButtonStart_clicked()
{
    int instances = ui->spinBox_instances->value();
    int maxPrime = ui->spinBox_primes->value();

    analyser->AnalysisStart(instances, maxPrime);

    /*
    if(ui->checkBox_process->isChecked()){
        analyser->AnalysisStart(instances, maxPrime);
    }

    if(ui->checkBox_threads->isChecked()){
        analyser->threadsAnalysis(instances, maxPrime);
    }*/

    chartView->show();
}
