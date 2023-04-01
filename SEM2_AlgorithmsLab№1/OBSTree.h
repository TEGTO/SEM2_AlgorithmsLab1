#include <cfloat>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;



// �������� ������� ��� ��������� ���� �������� ������
// freq[i] �� freq[j]
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
/* ������� �� ����� ���������� �������������, ��� ��������
�������� ������� �������� ������ ������. */
int optimalSearchTree(double keys[], double freq[], int n)
{
    /* �������� �������� 2D ������� ��� ��������� ����������
      ��������� */
    double**cost = new double*[n];
    for (int i = 0; i < n; i++)
        cost[i] = new double[n];
  

    /* cost[i][j] = ���������� ������� �������� ������ ������
      �� ������ ���� ��������� �� keys[i] �� keys[j].
      cost[0][n-1] ���������� ����������� ������� */

      // ��� ������ ����� ������� ������� ������ �����
    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];

    // ����� ��� ������� ���������� ������� �������� 2, 3, ... .
    // L � ������� �������.
    for (int L = 2; L <= n; L++)
    {
        // i ����� ����� � �������[][]
        for (int i = 0; i <n - L + 1; i++)
        {
            // �������� ����� ������� j � ����� ����� i �
             // ������� ������� L
            int j = i + L - 1;
            cost[i][j] = DBL_MAX;
            double off_set_sum = sum(freq, i, j);

            // ��������� ������� �� ����� � �������� keys[i..j] �� root
            for (int r = i; r <= j; r++)
            {
                // c = �������, ���� keys[r] ��� ������� ����� ��������
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

