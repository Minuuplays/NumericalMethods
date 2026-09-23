#include <bits/stdc++.h>
using namespace std;

int rnk(vector<vector<double>> A)
{
    int rows = A.size();
    int cols = A[0].size();

    int rank = 0;
    for (int col = 0; col < cols && rank < rows; col++)
    {
        int pivot = rank;
        for (int i = rank + 1; i < rows; i++)
        {
            if (fabs(A[i][col]) > fabs(A[pivot][col]))
            {
                pivot = i;
            }
        }
        if (fabs(A[pivot][col]) < 1e-12)
            continue;
        swap(A[rank], A[pivot]);

        for (int i = rank + 1; i < rows; i++)
        {
            double factor = A[i][col] / A[rank][col];

            for (int j = col; j < cols; j++)
            {
                A[i][j] = A[i][j] - factor * A[rank][j];
            }
        }
        rank++;
    }
    return rank;
}

bool gauss(vector<vector<double>> U, vector<double> B, vector<double> &X)
{

    int n = U.size();
    for (int k = 0; k < n; k++)
    {
        int pivot = k;

        for (int i = k + 1; i < n; i++)
        {
            if (fabs(U[i][k]) > fabs(U[pivot][k]))
            {
                pivot = i;
            }
        }

        // No pivot
        if (fabs(U[pivot][k]) < 1e-12)
        {
            return false;
        }

        // Swap rows
        swap(U[k], U[pivot]);

        double pivotV = U[k][k];
        for (int j = 0; j < n + 1; j++)
        {
            U[k][j] = U[k][j] / pivotV;
        }
        for (int i = 0; i < n; i++)
        {
            if (i == k)
                continue;
            double factor = U[i][k];
            for (int j = 0; j < n + 1; j++)
            {
                U[i][j] = U[i][j] - factor * U[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << U[i][j] << " ";
        }
    }

    for (int i = 0; i < n; i++)
    {
        X[i] = U[i][n];
    }

    return true;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> U(n, vector<double>(n + 1));
    vector<double> B(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
        cin >> B[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            U[i][j] = A[i][j];
        }
        U[i][n] = B[i];
    }

    int rnkA = rnk(A);
    int rnkAB = rnk(U);
    cout << "Rank: " << rnkA << endl;
    cout << "Rank: " << rnkAB << endl;

    cout << "--------------\n";

    vector<double> X(n, 0);

    if (gauss(U, B, X))
    {
        for (int i = 0; i < n; i++)
        {
            cout << "x" << i + 1 << " = " << X[i] << endl;
        }
    }
    return 0;
}