#include "compute_shapley.h"
#include <iostream>
#include <QDebug>
#include <math.h>

compute_shapley::compute_shapley(QObject *parent) : QObject(parent)
{
    int n=4; //Временное ограничение по числу игроков
    iPlayersValue_n=n;
    iCoalitionMaxVal=pow(2,iPlayersValue_n);
    qDebug()<<"Максимальное число коалиций = "<<iCoalitionMaxVal<<endl;
    setLi_qvFactorialCalculatedValues();
    setUi_qvPlayerProportionShares();
    createAllWinStrategyCoalitions();

}
void compute_shapley::setiPlayersValue_n(int n)
{
    iPlayersValue_n=n;
}
void compute_shapley::setLi_qvFactorialCalculatedValues()
{
    for(int i=0;i<=iPlayersValue_n;i++)
    {
        li_qvFactorialCalculatedValues.push_back(factorial(static_cast<ulong>(i)));
        // qDebug()<<"Factorial["<<i<<"]="<<li_qvFactorialCalculatedValues[i]<<endl;
    }

}
void compute_shapley::setUi_qvPlayerProportionShares()
{
    for(int i=0;i<iPlayersValue_n;i++) //Индексация с 0
    {
        ui_qvPlayerProportionShares.push_back(ciAllSharesVal/iPlayersValue_n);
        //qDebug()<<"Доля участника["<<i<<"]="<<ui_qvPlayerProportionShares[i]<<endl;
    }
}
ulong compute_shapley::factorial(ulong n)
{
    if (n == 0) // если пользователь ввел ноль,
        return 1; // возвращаем факториал от нуля - не удивляетесь, но это 1 =)
    else // Во всех остальных случаях
        return n * factorial(n - 1); // делаем рекурсию.
}
void compute_shapley::createAllWinStrategyCoalitions() //Создает набор всевозможных коалиций без повторений (без коалиции из всех участников)
{
    for(int i=0;i<iCoalitionMaxVal;i++) //количество всех возможных вариантов стратегий 2^n соотвественно бинаризация даст все возможные варианты без повторений
    {
        QVector<int>tempVector;
        if(binarray(tempVector,i))
        i_qvWinningCoalitions.push_back(tempVector); //Организуем выборку всех возможных стратегий коалиций (включая коалиции из всех игроков и коалиций из 1 игрока)
    }
    for(int i=0;i<i_qvWinningCoalitions.size();i++)
    {
    qDebug()<<"Победная коалиция - "<<i_qvWinningCoalitions[i]<<" сумма долей выигрыша - "<<i_qvAllWinCoalitionsIndexSumm[i]<<" количество участников = "<<i_qvCoalitionValue_t[i];
    }

}
int compute_shapley::binarray(QVector<int> &arr,int number)
{
    int razr=iPlayersValue_n-1; //Начинаем запись на 1 разряд меньше
    int summ=0;
    int tSumm=0; //Сумма участников коалицицй
    QVector<int> qvTemparr;
    for (int i = 0; i < iPlayersValue_n; i++)
    {
       if(number & (1 << (razr-i)))
       {
           qvTemparr.push_back(1); //Бинаризация числа (индекс игрока на 1 меньше чем должен быть)
           summ+=ui_qvPlayerProportionShares[i];
           tSumm++;
       }
       else
       {
           qvTemparr.push_back(0); //Бинаризация числа (индекс игрока на 1 меньше чем должен быть)
       }
    }
    if(summ>(ciAllSharesVal/2)) //Условие выйгрыша коалиции
    {
        arr=qvTemparr;
        i_qvAllWinCoalitionsIndexSumm.push_back(summ); //Сумма акций всех участников коалиции (индексация по порядку (-1) из всех возможных коалиций)
        i_qvCoalitionValue_t.push_back(tSumm); // Записываем количество участников данной стратегии для расчета вектора Шепли
        return 1;
    }
    return 0;
}


