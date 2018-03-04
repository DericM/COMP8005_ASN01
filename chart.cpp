
#include "chart.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>



ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    setRenderHint(QPainter::Antialiasing);
    setWindowFlag(Qt::Window);
    setFixedSize(1000, 900);

    series0 = new QScatterSeries();
    series0->setName("Process");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(10.0);

    series1 = new QScatterSeries();
    series1->setName("Threads");
    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series1->setMarkerSize(10.0);

    setRenderHint(QPainter::Antialiasing);

    chart()->addSeries(series0);
    chart()->addSeries(series1);

    chart()->setTitle("Process and Thread Comparison");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);

    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);

    maxJobSize = 0;
    maxTime = 0;

    //series1->append(0.5, 0.5);
}


void ChartView::scaleChart(int jobSize, double time){
    if(jobSize > maxJobSize){
        maxJobSize = jobSize;
        chart()->axisX()->setMax(maxJobSize);
    }
    if(time > maxTime){
        maxTime = time;
        chart()->axisY()->setMax(maxTime);
    }
}

void ChartView::addProcessMarker(int jobSize, double time)
{
    scaleChart(jobSize, time);
    series0->append(jobSize, time);
}


void ChartView::addThreadMarker(int jobSize, double time)
{
    scaleChart(jobSize, time);
    series1->append(jobSize, time);
}
