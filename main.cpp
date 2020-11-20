#include <QApplication>
#include "compute_shapley.h"
#include <math.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDebug>
#include <QString>


QT_CHARTS_USE_NAMESPACE



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    compute_shapley shapley;

    QPieSeries *seriesStart = new QPieSeries();
    double maxStart=0;
    int max_indexStart=0;

    //Инициализируем График долей акций
    for(int i=0;i<shapley.ui_qvPlayerProportionShares.size();i++)
    {
        QString index=QString::number(i);
        seriesStart->append(index, shapley.ui_qvPlayerProportionShares[i]);
        if(shapley.ui_qvPlayerProportionShares[i]>maxStart)
        {
            maxStart=shapley.ui_qvPlayerProportionShares[i];
            max_indexStart=i;
        }
    }

    //Инициализируем График долей по вектору Шепли
    QPieSeries *series = new QPieSeries();
    double max=0;
    int max_index=0;
    for(int i=0;i<shapley.d_qvectorShapley.size();i++)
    {
        QString index=QString::number(i);
        series->append(index, shapley.d_qvectorShapley[i]);
        if(shapley.d_qvectorShapley[i]>max)
        {
            max=shapley.d_qvectorShapley[i];
            max_index=i;
        }
    }

    QPieSlice *slice = series->slices().at(max_index);
    slice->setLabelVisible();
    slice->setExploded();
    slice->setPen(QPen(Qt::darkGreen, max_index));
    slice->setBrush(Qt::green);


    QPieSlice *sliceStart = seriesStart->slices().at(max_indexStart);
    sliceStart->setLabelVisible();
    sliceStart->setExploded();
    sliceStart->setPen(QPen(Qt::darkGreen, max_indexStart));
    sliceStart->setBrush(Qt::green);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("ДОЛЯ ПО ВЕКТОРУ ШЕПЛИ");

    QChart *chartStart = new QChart();
    chartStart->addSeries(seriesStart);
    chartStart->setTitle("ДОЛЯ ПО КОЛИЧЕСТВУ АКЦИЙ");



    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QChartView *chartViewStart = new QChartView(chartStart);
    chartViewStart->setRenderHint(QPainter::Antialiasing);


    QTextEdit *txt = new QTextEdit;
    txt->append(shapley.messagesBuffer);




    QWidget *window=new QWidget;
    QVBoxLayout *qvbxLayout=new QVBoxLayout;
    txt->setReadOnly(true);
    qvbxLayout->addWidget(chartView);
    qvbxLayout->addWidget(chartViewStart);
    qvbxLayout->addWidget(txt);
    window->setLayout(qvbxLayout);
    window->resize(1920,1080);
    window->show();

    return a.exec();
}
