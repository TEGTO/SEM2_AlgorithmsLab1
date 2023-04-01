#include <cfloat>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;



// Допоміжна функція для отримання суми елементів масиву
// freq[i] до freq[j]
int sum(double freq[], int i, int j)
{
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

void print(double _keys[], double _freq[], int n)
{
  
    std::vector<std::pair<double, double> > data;
    pair<double, double> buffer;
    for (size_t i = 0; i < n; i++)
    {
        buffer.first = _keys[i];
        buffer.second = _freq[i];
        data.push_back(buffer);

    }
    std::sort(data.begin(), data.end(), [](auto& left, auto& right) {
        return left.second > right.second;
        });
  
    cout << "Keys:     ";
    for (int i = 0; i < n; i++)
    {
        cout <<"  "<< data[i].first;
    }
    cout << endl << "Frequency:";
    for (int i = 0; i < n; i++)
    {
        cout << "  " << data[i].second;
    }
}
/* Функція на основі динамічного програмування, яка обчислює
мінімальна вартість бінарного дерева пошуку. */
int optimalSearchTree(double keys[], double freq[], int n)
{
    /* Створити допоміжну 2D матрицю для зберігання результатів
      підпроблем */
    double**cost = new double*[n];
    for (int i = 0; i < n; i++)
        cost[i] = new double[n];
  

    /* cost[i][j] = Оптимальна вартість бінарного дерева пошуку
      які можуть бути сформовані від keys[i] до keys[j].
      cost[0][n-1] зберігатиме результуючу вартість */

      // Для одного ключа вартість дорівнює частоті ключа
    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];

    // Тепер нам потрібно розглянути ланцюги довжиною 2, 3, ... .
    // L – довжина ланцюга.
    for (int L = 2; L <= n; L++)
    {
        // i номер рядка у вартості[][]
        for (int i = 0; i <n - L + 1; i++)
        {
            // Отримати номер стовпця j з рядка номер i і
             // довжина ланцюга L
            int j = i + L - 1;
            cost[i][j] = DBL_MAX;
            double off_set_sum = sum(freq, i, j);

            // Спробуйте зробити всі ключі в інтервалі keys[i..j] як root
            for (int r = i; r <= j; r++)
            {
                // c = вартість, коли keys[r] стає коренем цього піддерева
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                    ((r < j) ? cost[r + 1][j] : 0) +
                    off_set_sum;
                if (c < cost[i][j])
                    cost[i][j] = c;
            }
        }
    }
    return cost[0][n - 1];
}

