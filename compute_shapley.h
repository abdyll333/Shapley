#ifndef COMPUTE_SHAPLEY_H
#define COMPUTE_SHAPLEY_H

#include <QObject>

//* Класс вычислений с вектором Шепли *//

class compute_shapley : public QObject
{
    Q_OBJECT
    const int ciAllSharesVal=100;
    int iPlayersValue_n; // Число участников n
    int iCoalitionMaxVal; //Число возможных коалиций

    QVector<unsigned int>ui_qvPlayerProportionShares ; //Набор участников и их доля акций в компании где i - номер участиника

    QVector<QVector<int>>i_qvWinningCoalitions; //Победные коалиции вида {0,1,1..,n}
    QVector<int>i_qvCoalitionValue_t; //Число членов коалиции t для выборки (i соответсвует номеру стратегии)
    QVector<int>i_qvAllWinCoalitionsIndexSumm; //Сумма акций всех победных участников коалиции (индексация по порядку из всех возможных коалиций)

    QVector<long double>ld_qvectorShapley; // вычисляемый вектор Шепли

    QVector<ulong>li_qvFactorialCalculatedValues; //Вычисляемые заранее факториалы для задачи где v[i]-искомое значение i!

public:
    explicit compute_shapley(QObject *parent = nullptr);

    //инициализация входных значений
    void setiPlayersValue_n(int);
    void setLi_qvFactorialCalculatedValues();
    ulong factorial(ulong);
    void setUi_qvPlayerProportionShares();
    void createAllWinStrategyCoalitions(); //Составление набора всех неповторяющихся возможных победных стратегий коалиций
    /* Создает из 10сс 2сс масиив (делает выборку для коалиций ) с одновременным посчетом выигрыша (Одновременно создает победную выборку) */
    int binarray(QVector<int> &arr,int number);


signals:

};

#endif // COMPUTE_SHAPLEY_H
