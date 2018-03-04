#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

QT_CHARTS_BEGIN_NAMESPACE
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);

    void addProcessMarker(int jobSize, double time);
    void addThreadMarker(int jobSize, double time);
    void scaleChart(int jobSize, double time);

private:
    QScatterSeries *series0;
    QScatterSeries *series1;

    int maxJobSize;
    int maxTime;

};

#endif // CHARTVIEW_H
