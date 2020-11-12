#include "compute_shapley.h"
#include <iostream>
#include <QDebug>
#include <math.h>


//Пока на 12.11.2020 Записывать доли от акций можно через setUi_qvPlayerProportionShares() вписав нужные числа возможно будет далее импорт из файла или рандом

compute_shapley::compute_shapley(QObject *parent) : QObject(parent)
{
    setUi_qvPlayerProportionShares();
    iPlayersValue_n=ui_qvPlayerProportionShares.size(); //ограничение по числу игроков задается количеством записанных долей
    iCoalitionMaxVal=pow(2,iPlayersValue_n);
    qDebug()<<"Максимальное число коалиций = "<<iCoalitionMaxVal<<"\nМаксимальное число долей = "<<iAllSharesVal<<"\nМаксимальное число игроков = "<<iPlayersValue_n<<endl;
    setLi_qvFactorialCalculatedValues();
    createAllWinStrategyCoalitions();
    configureVectorShapley();
    for(int i = 0;i<d_qvectorShapley.size();i++)
    qDebug()<<"Вектор Шепли ["<<i<<"] ="<<d_qvectorShapley[i];

}
void compute_shapley::setiPlayersValue_n(int n)
{
    iPlayersValue_n=n;
}
void compute_shapley::setLi_qvFactorialCalculatedValues()
{
    for(int i=0;i<=iPlayersValue_n;i++)
    {
        d_qvFactorialCalculatedValues.push_back(factorial(static_cast<long double>(i)));
        // qDebug()<<"Factorial["<<i<<"]="<<li_qvFactorialCalculatedValues[i]<<endl;
    }

}
void compute_shapley::setUi_qvPlayerProportionShares()
{
    iAllSharesVal=0;
    //Всем поровну (для теста)
//    for(int i=0;i<iPlayersValue_n;i++) //Индексация с 0
//    {
//        ui_qvPlayerProportionShares.push_back(ciAllSharesVal/iPlayersValue_n);
//        //qDebug()<<"Доля участника["<<i<<"]="<<ui_qvPlayerProportionShares[i]<<endl;
//    }
    ui_qvPlayerProportionShares.push_back(35);
    iAllSharesVal+=35;
    ui_qvPlayerProportionShares.push_back(25);
    iAllSharesVal+=25;
    ui_qvPlayerProportionShares.push_back(22);
    iAllSharesVal+=22;
    ui_qvPlayerProportionShares.push_back(18);
    iAllSharesVal+=18;
    for(int i =0;i<ui_qvPlayerProportionShares.size();i++)
        qDebug()<<"Игрок - "<<i<<" Доля игрока = "<<ui_qvPlayerProportionShares[i];
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
    if(summ>(iAllSharesVal/2)) //Условие выйгрыша коалиции
    {
        arr=qvTemparr;
        i_qvAllWinCoalitionsIndexSumm.push_back(summ); //Сумма акций всех участников коалиции (индексация по порядку (-1) из всех возможных коалиций)
        i_qvCoalitionValue_t.push_back(tSumm); // Записываем количество участников данной стратегии для расчета вектора Шепли
        return 1;
    }
    return 0;
}
double compute_shapley::getLi_qvFactorialCalculatedValues(int i)
{
    return d_qvFactorialCalculatedValues[i];
}
void compute_shapley::computeShapley_i(int i,int j)
{
    int t=i_qvCoalitionValue_t[j]; //находим количество членов j коалиции для формулы
    int n=iPlayersValue_n; //Число участников
    double a=getLi_qvFactorialCalculatedValues(t-1);
    double b=getLi_qvFactorialCalculatedValues(n-t);
    double c=getLi_qvFactorialCalculatedValues(n);
    double summ=a*b/c;
    d_qvectorShapley[i]+=summ; //Суммируем значение для i значения вектора Шепли
    //qDebug()<<"Итерация: i="<<i<<" j="<<j<<" a="<<a<<" b="<<b<<" c="<<c<<"Значение Шепли = "<<summ;
}
void compute_shapley::configureVectorShapley()
{
    for(int i=0;i<iPlayersValue_n;i++)
    d_qvectorShapley.push_back(0);
    //Сначала выделим решающего члена коалиции, затем вычислим для него вектор Шепли
    for(int j=0;j<i_qvWinningCoalitions.size();j++) //перебор всех выйгрышных коалицицй
    {
        for(int i=0;i<iPlayersValue_n;i++) //Перебор всех участников игры
        {
            if(i_qvWinningCoalitions[j][i]==1) //Если такой член коалиции сущесвует, то проверим сможет ли коалиция выйграть без него
            {
                int winShare=i_qvAllWinCoalitionsIndexSumm[j]-i_qvWinningCoalitions[j][i]*ui_qvPlayerProportionShares[i];
                if(winShare<=(iAllSharesVal/2))
                    computeShapley_i(i,j);
            }
        }
    }
}



