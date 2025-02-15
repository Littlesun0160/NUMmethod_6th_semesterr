#include <iostream>
#include <math.h>
#include <iomanip>

//Задаем заданную в условии функцию как f(x) и ее точную производную как F(x)
double f(double x)
{
    return (x*sqrt(pow(x*x-1,3)));
}
double F(double x)
{
    return ((sqrt(pow(x*x-1,5)))/5);
}

//Вычиление относительной погрешности
void Inaccuracy(double ExactValue, double Approximation)
{
    std::cout << "Погрешность метода равна " << std::fixed <<
        std::abs((ExactValue - Approximation) / ExactValue) * 100 << "%\n\n";
    return;
}
//Метод левых прямоугольников
double Method1(double a, double b, double Eps)
{
    std::cout << "Метод левых прямоугольников\n";
    double Old_Result = 0; //Необходимо для оценки точности
    int n = 2; //Задаем начальное количество точек за равное 2
    while (true)
    {
        double h = (b - a) / n;
        double Result = 0;
        //Принимая за x0 = a, а за xn = b, по следующей формуле выразим сумму
        //значений функции f(xi)
        for (int i = 0; i < n; i++)
        {
            Result += f(a + h * i);
        }
        Result *= h;
        if (std::abs(Result - Old_Result) < Eps)
        {
            std::cout << "Приближенное значение интеграла I = " << std::setprecision(12) << Result << "\n" <<
                "Количество точек разбиения n = " << n << "\n" <<
                "Величина последнего шага h = " << std::fixed << std::setprecision(8) << h << "\n";
            return Result;
        }
        n *= 2; Old_Result = Result;
    }
}
//Метод правых прямоугольников
double Method2(double a, double b, double Eps)
{
    std::cout << "Метод правых прямоугольников\n";
    double Old_Result = 0; //Необходимо для оценки точности
    int n = 2; //Задаем начальное количество точек за равное 2
    while (true)
    {
        double h = (b - a) / n;
        double Result = 0;
        //Принимая за x0 = a, а за xn = b, по следующей формуле выразим сумму
        //значений функции f(xi)
        for (int i = 1; i <= n; i++)
        {
            Result += f(a + h * i);
        }
        Result *= h;
        if (std::abs(Result - Old_Result) < Eps)
        {
            std::cout << "Приближенное значение интеграла I = " << std::setprecision(12) << Result << "\n" <<
                "Количество точек разбиения n = " << n << "\n" <<
                "Величина последнего шага h = " << std::fixed << std::setprecision(8) << h << "\n";
            return Result;
        }
        n *= 2; Old_Result = Result;
    }
}
//Метод средних прямоугольников
double Method3(double a, double b, double Eps)
{
    std::cout << "Метод средних прямоугольников\n";
    double Old_Result = 0; //Необходимо для оценки точности
    int n = 2; //Задаем начальное количество точек за равное 2
    while (true)
    {
        double h = (b - a) / n;
        double Result = 0;
        //Принимая за x0 = a, а за xn = b, по следующей формуле выразим сумму
        //значений функции f(xi)
        for (int i = 1; i <= n; i++)
        {
            Result += f(a + h * (i - 1) + (h / 2));
        }
        Result *= h;
        if (std::abs(Result - Old_Result) < Eps)
        {
            std::cout << "Приближенное значение интеграла I = " << std::setprecision(12) << Result << "\n" <<
                "Количество точек разбиения n = " << n << "\n" <<
                "Величина последнего шага h = " << std::fixed << std::setprecision(8) << h << "\n";
            return Result;
        }
        n *= 2; Old_Result = Result;
    }
}
//Метод трапеций
double Method4(double a, double b, double Eps)
{
    std::cout << "Метод трапеций\n";
    double Old_Result = 0; //Необходимо для оценки точности
    int n = 2; //Задаем начальное количество точек за равное 2
    while (true)
    {
        double h = (b - a) / n;
        double Result = 0;
        //Принимая за x0 = a, а за xn = b, по следующей формуле выразим сумму
        //значений функции f(xi)
        for (int i = 1; i < n; i++)
        {
            Result += f(a + h * i);
        }
        Result += ((f(a) + f(b)) / 2);
        Result *= h;
        if (std::abs(Result - Old_Result) < Eps)
        {
            std::cout << "Приближенное значение интеграла I = " << std::setprecision(12) << Result << "\n" <<
                "Количество точек разбиения n = " << n << "\n" <<
                "Величина последнего шага h = " << std::fixed << std::setprecision(8) << h << "\n";
            return Result;
        }
        n *= 2; Old_Result = Result;
    }
}
//Метод Симпсона
double Method5(double a, double b, double Eps)
{
    std::cout << "Метод Симпсона\n";
    double Old_Result = 0; //Необходимо для оценки точности
    int n = 2; //Задаем начальное количество точек за равное 2
    while (true)
    {
        double h = (b - a) / n;
        double Result = 0;
        //Принимая за x0 = a, а за xn = b, по следующей формуле выразим сумму
        //значений функции f(xi)
        for (int i = 2; i < n; i += 2)
        {
            Result += f(a + h * i);
        }
        double InterSumm = 0;
        for (int i = 1; i <= n; i += 2)
        {
            InterSumm += f(a + h * i);
        }
        Result *= 2; InterSumm *= 4;
        Result += (InterSumm + f(a) + f(b));
        Result *= (h / 3);
        if (std::abs(Result - Old_Result) < Eps)
        {
            std::cout << "Приближенное значение интеграла I = " << std::setprecision(12) << Result << "\n" <<
                "Количество точек разбиения n = " << n << "\n" <<
                "Величина последнего шага h = " << std::fixed << std::setprecision(8) << h << "\n";
            return Result;
        }
        n *= 2; Old_Result = Result;
    }
}
int main()
{
	setlocale(LC_ALL, "ru");
    double a = 1; double b = 2; double Eps = 0.0001;
    double I = F(b) - F(a);
    std::cout << "Точное значение интеграла: I = " << std::setprecision(12) << I << "\n\n";
    
    Inaccuracy(I, Method1(a, b, Eps));
    Inaccuracy(I, Method2(a, b, Eps));
    Inaccuracy(I, Method3(a, b, Eps));
    Inaccuracy(I, Method4(a, b, Eps));
    Inaccuracy(I, Method5(a, b, Eps));
}

