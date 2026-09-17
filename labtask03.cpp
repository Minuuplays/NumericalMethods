#include <bits/stdc++.h>
using namespace std;

// Substitutes x back into the original A and b, and reports how close
// A*x is to b. Returns true if every equation checks out.
bool verifySolution(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &x)
{
    int n = A.size();
    bool ok = true;
    cout << endl
         << "Verification (substituting x back into original equations):" << endl;
    for (int i = 0; i < n; i++)
    {
        double lhs = 0;
        for (int j = 0; j < n; j++)
        {
            lhs += A[i][j] * x[j];
        }
        cout << "Equation " << i + 1 << ": " << lhs << " (should be " << b[i] << ")" << endl;
        if (fabs(lhs - b[i]) > 1e-6)
            ok = false;
    }
    return ok;
}

// Reduces a copy of the given matrix to row-echelon form (Gaussian
// elimination with partial pivoting) and returns its rank
int computeRank(vector<vector<double>> mat)
{
    int rows = mat.size();
    int cols = mat[0].size();
    int rank = 0;
    for (int col = 0; col < cols && rank < rows; col++)
    {
        int pivotRow = -1;
        double best = 1e-9;
        for (int r = rank; r < rows; r++)
        {
            if (fabs(mat[r][col]) > best)
            {
                best = fabs(mat[r][col]);
                pivotRow = r;
            }
        }
        if (pivotRow == -1)
            continue; // no usable pivot in this column
        swap(mat[rank], mat[pivotRow]);
        for (int r = 0; r < rows; r++)
        {
            if (r == rank)
                continue;
            double factor = mat[r][col] / mat[rank][col];
            for (int c = col; c < cols; c++)
            {
                mat[r][c] -= factor * mat[rank][c];
            }
        }
        rank++;
    }
    return rank;
}

int main()
{
    int n;
label:
    cout << "Enter number of equations: ";
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    cout << "Enter the augmented Matrix :" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
        cin >> b[i];
    }

    // Build [A|b]
    vector<vector<double>> Augmented(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Augmented[i][j] = A[i][j];
        }
        Augmented[i][n] = b[i];
    }

    int rankA = computeRank(A);
    int rankAug = computeRank(Augmented);
    cout << endl
         << "Rank(A) = " << rankA << ", Rank([A|b]) = " << rankAug << ", n = " << n << endl
         << endl;

    if (rankA < rankAug)
    {
        cout << "System has NO solution (inconsistent)." << endl;
    }
    else if (rankA < n)
    {
        // rank(A) == rank([A|b]) but less than n -> consistent, but not
        // enough independent equations to pin down every unknown.
        int freeCount = n - rankA;
        cout << "System has INFINITELY MANY solutions (" << freeCount << " free variable(s))." << endl;
    }
    else
    {
        // rankA == rankAug == n -> exactly one solution, safe to solve.
        vector<vector<double>> L(n, vector<double>(n, 0));
        vector<vector<double>> U(n, vector<double>(n, 0));
        for (int j = 0; j < n; j++)
        {
            for (int i = j; i < n; i++)
            {
                double sum = 0;
                for (int k = 0; k < j; k++)
                {
                    sum += L[j][k] * U[k][i];
                }
                U[j][i] = (A[j][i] - sum);
            }
            L[j][j] = 1;
            for (int i = j + 1; i < n; i++)
            {
                double sum = 0;
                for (int k = 0; k < j; k++)
                {
                    sum += L[i][k] * U[k][j];
                }
                L[i][j] = (A[i][j] - sum) / U[j][j];
            }
        }
        cout << "Lower Triangular Matrix L:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << L[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "Upper Triangular Matrix U:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << U[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        vector<double> y(n);
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += L[i][k] * y[k];
            }
            y[i] = b[i] - sum;
        }
        vector<double> x(n);
        for (int i = n - 1; i >= 0; i--)
        {
            double sum = 0;
            for (int k = i + 1; k < n; k++)
            {
                sum += U[i][k] * x[k];
            }
            x[i] = (y[i] - sum) / U[i][i];
        }
        // x[1..n] : fully and uniquely determined above.
        cout << "Solved using Doolittle Method:" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "x" << i + 1 << " = " << x[i] << endl;
        }

        if (verifySolution(A, b, x))
        {
            cout << "All equations satisfied - solution verified." << endl;
        }
        else
        {
            cout << "Warning: solution does not satisfy the original equations." << endl;
        }
    }

    char ch;
    cout << "Solve another System ? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')  goto label;
    return 0;
}