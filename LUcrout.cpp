#include <bits/stdc++.h>
using namespace std;

void printEq(vector<vector<double>> &A, vector<double> &b, int n)
{
    cout << "\nThe system of equations is:\n";
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            char a = 'x' + j;
            if (A[i][j] == 0)
            {
                continue;
            }
            else if (A[i][j] == 1)
            {
                if (count > 0)
                    cout << "+ ";
                cout << a << " ";
                count++;
            }
            else if (A[i][j] == -1)
            {
                cout << "- ";
                cout << a << " ";
                count++;
            }
            else if (A[i][j] < 0)
            {
                cout << "- ";
                cout << abs(A[i][j]) << a << " ";
                count++;
            }
            else
            {
                if (count > 0)
                    cout << "+ ";
                cout << abs(A[i][j]) << a << " ";
                count++;
            }
        }
        cout << "= " << b[i] << endl;
    }
    cout << endl;
}

// Computes rank of a matrix using Gaussian elimination (row echelon form)
int computeRank(vector<vector<double>> mat, int rows, int cols)
{
    int rank = 0;
    for (int col = 0; col < cols && rank < rows; col++)
    {
        // find a row below (including) 'rank' with non-zero entry in this column
        int pivotRow = -1;
        for (int i = rank; i < rows; i++)
        {
            if (fabs(mat[i][col]) > 1e-9)
            {
                pivotRow = i;
                break;
            }
        }
        if (pivotRow == -1)
            continue; // whole column is zero, skip it

        swap(mat[rank], mat[pivotRow]);

        // eliminate entries below the pivot
        for (int i = rank + 1; i < rows; i++)
        {
            double factor = mat[i][col] / mat[rank][col];
            for (int j = col; j < cols; j++)
                mat[i][j] -= factor * mat[rank][j];
        }
        rank++;
    }
    return rank;
}

int main()
{
    int n;
    cout << "Number of unknowns: ";
    cin >> n;

    // A is the coefficient matrix and b is the constant vector
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    cout << "Enter the coefficients and constants of each equation:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Equation " << i + 1 << ":\n";
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
        cin >> b[i];
    }

    printEq(A, b, n);

    // Build augmented matrix [A|b] to check rank
    vector<vector<double>> augmented(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            augmented[i][j] = A[i][j];
        augmented[i][n] = b[i];
    }

    int rankA = computeRank(A, n, n);
    int rankAug = computeRank(augmented, n, n + 1);

    cout << "\nRank of coefficient matrix A = " << rankA << endl;
    cout << "Rank of augmented matrix [A|b] = " << rankAug << endl;

    if (rankA < rankAug)
    {
        cout << "\nThe system has NO SOLUTION (inconsistent).\n";
        return 0;
    }
    else if (rankA == rankAug && rankA < n)
    {
        cout << "\nThe system has INFINITE SOLUTIONS (underdetermined).\n";
        return 0;
    }
    else
    {
        cout << "\nThe system has a UNIQUE SOLUTION. Solving using Crout's method...\n";
    }
    cout << endl;

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    // Crout's method - U has unit diagonal elements
    for (int j = 0; j < n; j++)
    {
        for (int i = j; i < n; i++)
        { // column of L
            double sum = 0;
            for (int k = 0; k < j; k++)
            {
                sum += L[i][k] * U[k][j];
            }
            L[i][j] = A[i][j] - sum;
        }
        U[j][j] = 1; // diagonal of U is always 1
        for (int i = j + 1; i < n; i++)
        { // row of U
            double sum = 0;
            for (int k = 0; k < j; k++)
            {
                sum += L[j][k] * U[k][i];
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }

    cout << "Lower Triangular Matrix L:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << L[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "Upper Triangular Matrix U:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << U[i][j] << "  ";
        }
        cout << endl;
    }

    // Forward Substitution L*y=b
    vector<double> y(n);
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int k = 0; k < i; k++)
        {
            sum += L[i][k] * y[k];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }

    // Backward Substituition U*x = y
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int k = i + 1; k < n; k++)
        {
            sum += U[i][k] * x[k];
        }
        x[i] = y[i] - sum; // U[i][i] = 1 always...so no divition needed
    }

    // Print the final solution
    cout << "\nSolution:\n";
    for (int i = 0; i < n; i++)
    {
        char a = 'x' + i;
        cout << a << " = " << x[i] << endl;
    }

    return 0;
}