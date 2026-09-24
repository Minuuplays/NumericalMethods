#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;

// ---------------------------------------------------------------------
// Rank computation — completely independent of gauss().
// Row-reduces a copy of M with partial pivoting and counts pivots.
// Used twice in main(): once on A, once on [A|B].
// ---------------------------------------------------------------------
int rnk(vector<vector<double>> M)
{
    int rows = M.size();
    int cols = M[0].size();

    int rank = 0;
    for (int col = 0; col < cols && rank < rows; col++)
    {
        int pivot = rank;
        for (int i = rank + 1; i < rows; i++)
            if (fabs(M[i][col]) > fabs(M[pivot][col]))
                pivot = i;

        if (fabs(M[pivot][col]) < EPS)
            continue;

        swap(M[rank], M[pivot]);

        for (int i = rank + 1; i < rows; i++)
        {
            double factor = M[i][col] / M[rank][col];
            for (int j = col; j < cols; j++)
                M[i][j] -= factor * M[rank][j];
        }
        rank++;
    }
    return rank;
}

// ---------------------------------------------------------------------
// Gauss-Jordan elimination on the augmented matrix U (n x n+1).
// Reduces U's first n columns to the identity, eliminating both above
// and below each pivot, so U[i][n] is the solution directly — no
// back-substitution needed. Returns false if singular.
// Does not call rnk() or share state with it.
// ---------------------------------------------------------------------
bool gauss(vector<vector<double>> U, vector<double> &X)
{
    int n = U.size();

    for (int k = 0; k < n; k++)
    {
        // partial pivoting
        int pivot = k;
        for (int i = k + 1; i < n; i++)
            if (fabs(U[i][k]) > fabs(U[pivot][k]))
                pivot = i;

        if (fabs(U[pivot][k]) < EPS)
            return false; // no valid pivot in this column -> singular

        swap(U[k], U[pivot]);

        double pivotV = U[k][k];
        for (int j = 0; j < n + 1; j++)
            U[k][j] /= pivotV;

        for (int i = 0; i < n; i++)
        {
            if (i == k)
                continue;
            double factor = U[i][k];
            if (factor == 0.0)
                continue;
            for (int j = 0; j < n + 1; j++)
                U[i][j] -= factor * U[k][j];
        }
    }

    for (int i = 0; i < n; i++)
        X[i] = U[i][n];

    return true;
}

int main()
{
    int n;
    if (!(cin >> n) || n <= 0)
    {
        cout << "Invalid n\n";
        return 0;
    }

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> B(n);
    vector<vector<double>> AB(n, vector<double>(n + 1)); // for rnk() only
    vector<vector<double>> U(n, vector<double>(n + 1));  // for gauss() only

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            AB[i][j] = A[i][j];
            U[i][j] = A[i][j];
        }
        cin >> B[i];
        AB[i][n] = B[i];
        U[i][n] = B[i];
    }

    int rankA  = rnk(A);
    int rankAB = rnk(AB); // includes RHS column, so an inconsistent row
                           // (0 0 ... 0 | nonzero) is correctly counted

    cout << "Rank of A: " << rankA << "\n";
    cout << "Rank of [A|B]: " << rankAB << "\n";
    cout << "--------------\n";

    if (rankA != rankAB)
    {
        cout << "No solution (system is inconsistent)\n";
    }
    else if (rankA < n)
    {
        cout << "Infinitely many solutions (system is underdetermined)\n";
    }
    else
    {
        vector<double> X(n, 0.0);
        if (gauss(U, X))
        {
            for (int i = 0; i < n; i++)
                cout << "x" << i + 1 << " = " << X[i] << "\n";
        }
        else
        {
            // Shouldn't happen given rankA == n, but kept as a safety net
            // since gauss() does its own independent pivoting/checks.
            cout << "gauss() reported singular despite rankA == n\n";
        }
    }

    return 0;
}