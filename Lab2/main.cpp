#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <locale>

std::vector<double> GaussMethod(std::vector<std::vector<double>> a, std::vector<double> b)
{
	//создаем расширенную матрицу
	for (int i = 0; i < a.size(); ++i)
	{
		a[i].push_back(b[i]);
	}
	for (int i = 0; i < a.size(); i++)
	{
		int maxnum = i; //задаем номер строки главного элемента
		for (int j = i+1; j < a.size(); ++j)
		{
			//находим максимальный по модулю элемент в столбце
			if (std::abs(a[j][i]) > std::abs(a[maxnum][i]))
			{
				maxnum = j;
			}
		}
		// перестановка строк, чтобы главный элемент был на диагонали
		std::swap(a[i], a[maxnum]);

		//прямой ход: приведение к верхнетреугольному виду матрицы
		for (int k = i + 1; k < a.size(); ++k)
		{
			double temp = a[k][i] / a[i][i]; // коэффициент для вычитания

			for (int j = i; j < a.size() + 1; ++j)
			{
				a[k][j] -= temp * a[i][j];
			}
		}
	}
	std::cout << "верхнетреугольный вид матрицы в результате прямого хода:\n";
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a.size(); j++)
		{
			std::cout << std::setprecision(20) << std::fixed << a[i][j] << "   ";
		}
		std::cout << "\n";
	}

	std::vector<double> result;
	for (int i = 0; i < a.size(); i++)
	{
		result.push_back(0);
	}
	for (int i = a.size() - 1; i >= 0; --i)
	{
		result[i] = a[i][a.size()]; // последний элемент в строке i - это значение b[i] после преобразований
		for (int j = i + 1; j < a.size(); ++j)
		{
			result[i] -= a[i][j] * result[j]; // вычитаем известные значения, чтобы получить result[i]
		}
		result[i] /= a[i][i]; // делим на диагональный элемент
	}
	return result;
}

//Проверяем выполнение достаточного условия сходимости
bool IsDiagonalDominant(const std::vector<std::vector<double>>& A) 
{
    for (int i = 0; i < A.size(); ++i) 
	{
        double Summ = 0.0; //Задаем сумму элементов на строке
        for (int j = 0; j < A.size(); ++j) 
		{
            if (i != j) Summ += abs(A[i][j]);
        }
		if (abs(A[i][i]) < Summ)
		{
			std::cout << "\nДостаточное условие не выполняется. Метод может не сойтись\n";
			return false;
		}
    }
	std::cout << "\nДостаточное условие выполняется\n";
    return true;
}

std::vector<double> SeidelMethod(std::vector<std::vector<double>> A,std::vector<double> b) 
{
	IsDiagonalDominant(A);
	int MaxIter = 1000; //Зададим максимальное количество итераций
    std::vector<double> x(A.size(), 0.0), x_new(A.size(), 0.0); 
    std::vector<std::vector<double>> LastIters; //Задаем вектор последних итераций для отслеживания

	std::cout << "Преобразованная для метода Зейделя матрица:\n";
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			std::cout << std::setprecision(20) << std::fixed << A[i][j] << "   ";
		}
		std::cout << "\n";
	}

	//Применяем метод простых итераций
    for (int iter = 0; iter < MaxIter; ++iter) 
	{
		for (int i = 0; i < A.size(); ++i) 
		{
			double Summ1 = 0.0, Summ2 = 0.0;
			for (int j = 0; j < i; ++j)
			{
				Summ1 += A[i][j] * x_new[j];
			}
			for (int j = i + 1; j < A.size(); ++j)
			{
				Summ2 += A[i][j] * x[j];
			}
			x_new[i] = (b[i] - Summ1 - Summ2) / A[i][i];
		}
        
		//Нам необходимы лишь последние 3 итерации, остальные убираем
        if (LastIters.size() >= 3) 
		{
            LastIters.erase(LastIters.begin());
        }
        LastIters.push_back(x_new); //Последней итерацией принимаем x_new

		//Определяем максимальную погрешность между старыми и новыми значениями
		double Inaccuracy = 0.0;
		for (int j = 0; j < A.size(); ++j)
		{
			Inaccuracy = std::max(Inaccuracy, std::abs(x_new[j] - x[j]));
		}
		//И если она меньше заданной точности (10^(-9)), то мы нашли необходимое приближенное решение
		if (Inaccuracy < 0.000000001) break;
        x = x_new; //Иначе повторяем итерации
    }

    std:: cout << "\nТри последних итерации:\n";
    for (int j = 0; j < LastIters.size(); ++j) 
	{
        std::cout << MaxIter - LastIters.size() + j + 1 << ") ";
        for (double Value : LastIters[j]) 
		{
            std::cout << std::fixed << std::setprecision(18) << Value << "  ";
        }
        std::cout << "\n";
    }
    return x_new;
}


int main()
{
	setlocale(LC_ALL, "ru");
	std::vector<std::vector<double>> A{ {0.15 , 2.11, 3.75 , 8.14},
										{0.64 , 1.21 , 2.05 , -0.99},
										{3.21 , 1.53 , -1.04 , -3.18},
										{0.77 , 1.22 , 1.18 , 2.25} };
	
	std::vector<std::vector<double>> A_Seidel = {
		{3.21, 1.53, -1.04, -3.18},
		{0.64, 1.21, 2.05, -0.99},
		{0.15, 2.11, 3.75, 8.14},
		{0.77, 1.22, 1.18, 2.25}
	};

	std::vector<double> b = { 3.82, 2.47, -6.35, -1.52 };
	std::vector<double> x = { 1, -1, 1, -1 };
	std::vector<double> Gaussresult = GaussMethod(A, b);
	std::cout << "\nРезультат метода Гаусса:\n";
	for (int i = 0; i < Gaussresult.size(); i++)
	{
		std::cout << std::setprecision(20) << std::fixed << Gaussresult[i] << "   ";
	}
	std::cout << "\n\nПогрешность метода Гаусса равна:\n";
	for (int i = 0; i < Gaussresult.size(); i++)
	{
		std::cout << std::setprecision(20) << std::fixed << (Gaussresult[i]-x[i]) << "   ";
	}

	std::vector<double> SeidelResult = SeidelMethod(A_Seidel, b);

	std::cout << "\nРешение методом Зейделя:\n";
	for (double Value : SeidelResult)
	{
		std::cout << std::fixed << std::setprecision(20) << Value << "  ";
	}
	std::cout << "\n";

	std::cout << "\nПогрешность метода Зейделя:\n";
	for (size_t i = 0; i < SeidelResult.size(); ++i)
	{
		std::cout << std::fixed << std::setprecision(20) << std::abs(x[i] - SeidelResult[i]) << "  ";
	}
	std::cout << "\n";

}