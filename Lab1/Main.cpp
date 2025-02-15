#include <iostream>
#include <cmath>
#include <iomanip>

//Задаем заданную в условии задачу как f(x)
double f(double x)
{
    return (log(2 * x) - (5 * pow(x, -2)));
}
double Derivative_of_f_First(double x)
{
    return ((pow(x, 2) + 10 / pow(x, 3)));
}
double Derivative_of_f_Second(double x)
{
    return (-((pow(x, 2) + 30) / pow(x, 4)));
}

//Функция нахождения значений f(x) с шагом h = (b-a)/n
// В данном случае шаг получится равным h = 0.35
void ValuesOfFunction(double a, double b, int n)
{
    std::cout << "Таблица значений функции с заданными a,b,n\n";
    double x = a;
    for (int i = 1; i <= n + 1; i++)
    {
        std::cout << i << ") x = " << std::setprecision(12) << x << "  f(x) = "
            << f(x) << "\n";
        x += (b - a) / n;
    }
}
//1) метод Ньютона(метод касательных)
// В данной задаче в качестве начального приближения принимаем x0 = 1
void Method1(double x0, double Eps)
{
    std::cout << "\nМетод Ньютона\n";
    int Iter = 1; //количество итераций
    while (true)
    {
        double x = x0 - f(x0) / Derivative_of_f_First(x0);
        std::cout << "x" << Iter << " = " << std::setprecision(12) << x << "\n";
        if (std::abs(x - x0) < Eps)
        {
            return;
        }
        Iter++; x0 = x;
    }
}

//2) метод хорд
void Method2(double x0, double b, double Eps)
{
    std::cout << "\nМетод хорд\n";
    int Iter = 1;
    while (true)
    {
        double x = x0 - f(x0) * (b - x0) / (f(b) - f(x0));
        std::cout << "x" << Iter << " = " << std::setprecision(12) << x << "\n";
        if (std::abs(x - x0) < Eps)
        {
            return;
        }
        Iter++; x0 = x;
    }
}

//3) Метод секущих
//В качетсве нач. точек зададим x0=1.5 и x1=2
void Method3(double Eps)
{
    std::cout << "\nМетод секущих\n";
    int Iter = 1; double x0 = 1.5; double x1 = 2;
    while (true)
    {
        double x = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        std::cout << "x" << Iter << " = " << std::setprecision(12) << x << "\n";
        if (std::abs(x - x0) < Eps)
        {
            return;
        }
        Iter++; x0 = x;
    }
}

//4) Конечноразностный метод Ньютона
//В качестве параметра возьмем h = 0.05
void Method4(double x0, double Eps)
{
    std::cout << "\nконечноразностный метод Ньютона\n";
    int Iter = 1; double h = 0.05;
    while (true)
    {
        double x = x0 - h * f(x0) / (f(x0+h) - f(x0));
        std::cout << "x" << Iter << " = " << std::setprecision(12) << x << "\n";
        if (std::abs(x - x0) < Eps)
        {
            return;
        }
        Iter++; x0 = x;
    }
}

//5) Метод Стеффенсена
void Method5(double x0, double Eps)
{
    std::cout << "\nМетод Стеффенсена\n";
    int Iter = 1;
    while (true)
    {
        double x = x0 - pow(f(x0),2) / (f(x0+f(x0)) - f(x0));
        std::cout << "x" << Iter << " = " << std::setprecision(12) << x << "\n";
        if (std::abs(x - x0) < Eps)
        {
            return;
        }
        Iter++; x0 = x;
    }
}

//6) Метод простых итераций
//Здесь также положим параметр t = 0.05
void Method6(double x0, double Eps)
{
    std::cout << "\nМетод простых итераций\n";
    int Iter = 1; double t = 0.05;
    while (true)
    {
        double x = x0 - t * f(x0);
        std::cout << "x" << Iter << " = " << std::setprecision(12) << x << "\n";
        if (std::abs(x - x0) < Eps)
        {
            return;
        }
        Iter++; x0 = x;
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    double a = 0; double b = 3.5; const int n = 10;
    ValuesOfFunction(a, b, n);
    const double Eps = 1e-7; //Необходимая точность
    //Далее рассматриваем задачу в промежутке 1<x<2
    a = 1; b = 2;
    Method1(a, Eps);
    Method2(a, b, Eps);
    Method3(Eps);
    Method4(a, Eps);
    Method5(b, Eps);
    Method6(a, Eps);
}
