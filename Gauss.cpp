#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

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
// Gauss elimination — forward elimination with partial pivoting,
// then back substitution. Returns false if the system is singular
// (no unique solution). Does not call rnk() or share state with it.
// ---------------------------------------------------------------------
bool gaussElm(vector<vector<double>> A, vector<double> B, vector<double> &X)
{
    int n = A.size();

    for (int k = 0; k < n - 1; k++)
    {
        // partial pivoting
        int pivot = k;
        for (int i = k + 1; i < n; i++)
            if (fabs(A[i][k]) > fabs(A[pivot][k]))
                pivot = i;

        if (fabs(A[pivot][k]) < EPS)
            return false; // no valid pivot in this column -> singular

        swap(A[k], A[pivot]);
        swap(B[k], B[pivot]);

        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++)
                A[i][j] -= factor * A[k][j];
            B[i] -= factor * B[k];
        }
    }

    if (fabs(A[n - 1][n - 1]) < EPS)
        return false; // last pivot is zero -> singular

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = B[i];
        for (int j = i + 1; j < n; j++)
            sum -= A[i][j] * X[j];
        X[i] = sum / A[i][i];
    }
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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            AB[i][j] = A[i][j];
        }
        cin >> B[i];
        AB[i][n] = B[i];
    }

    int rankA  = rnk(A);
    int rankAB = rnk(AB); // includes RHS column, so an inconsistent row

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
        if (gaussElm(A, B, X))
        {
            for (int i = 0; i < n; i++)
                cout << "x" << i + 1 << " = " << X[i] << "\n";
        }
        else
        {
            // Shouldn't happen given rankA == n, but kept as a safety net
            // since gaussElm() does its own independent pivoting/checks.
            cout << "gaussElm() reported singular despite rankA == n\n";
        }
    }

    return 0;
}