#include <iostream>
#include <cmath>
#include <iomanip>

//������ �������� � ������� ������ ��� f(x)
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

//������� ���������� �������� f(x) � ����� h = (b-a)/n
// � ������ ������ ��� ��������� ������ h = 0.35
void ValuesOfFunction(double a, double b, int n)
{
    std::cout << "������� �������� ������� � ��������� a,b,n\n";
    double x = a;
    for (int i = 1; i <= n + 1; i++)
    {
        std::cout << i << ") x = " << std::setprecision(12) << x << "  f(x) = "
            << f(x) << "\n";
        x += (b - a) / n;
    }
}
//1) ����� �������(����� �����������)
// � ������ ������ � �������� ���������� ����������� ��������� x0 = 1
void Method1(double x0, double Eps)
{
    std::cout << "\n����� �������\n";
    int Iter = 1; //���������� ��������
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

//2) ����� ����
void Method2(double x0, double b, double Eps)
{
    std::cout << "\n����� ����\n";
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

//3) ����� �������
//� �������� ���. ����� ������� x0=1.5 � x1=2
void Method3(double Eps)
{
    std::cout << "\n����� �������\n";
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

//4) ����������������� ����� �������
//� �������� ��������� ������� h = 0.05
void Method4(double x0, double Eps)
{
    std::cout << "\n����������������� ����� �������\n";
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

//5) ����� �����������
void Method5(double x0, double Eps)
{
    std::cout << "\n����� �����������\n";
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

//6) ����� ������� ��������
//����� ����� ������� �������� t = 0.05
void Method6(double x0, double Eps)
{
    std::cout << "\n����� ������� ��������\n";
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
    const double Eps = 1e-7; //����������� ��������
    //����� ������������� ������ � ���������� 1<x<2
    a = 1; b = 2;
    Method1(a, Eps);
    Method2(a, b, Eps);
    Method3(Eps);
    Method4(a, Eps);
    Method5(b, Eps);
    Method6(a, Eps);
}