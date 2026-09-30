// Solve the linear system A x = b by finding the inverse of A:  x = A^-1 * b 
// The inverse is found with Gauss-Jordan elimination (with row swapping).

#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 10;

int main() {
    int n;
    double A[MAXN][MAXN], inv[MAXN][MAXN], b[MAXN], x[MAXN];

    // ---- Input ----
    cout << "Enter size n (max " << MAXN << "): ";
    cin >> n;

    cout << "Enter matrix A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter vector b (" << n << " values):\n";
    for (int i = 0; i < n; i++)
        cin >> b[i];

    // ---- Start inv as the identity matrix ----
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = (i == j) ? 1.0 : 0.0;

    // ---- Gauss-Jordan elimination ----
    for (int i = 0; i < n; i++) {
        // 1. Find the row with the largest value in column i (best pivot)
        int pivotRow = i;
        for (int r = i + 1; r < n; r++)
            if (fabs(A[r][i]) > fabs(A[pivotRow][i]))
                pivotRow = r;

        // 2. If the pivot is (almost) zero, the matrix has no inverse
        if (fabs(A[pivotRow][i]) < 1e-12) {
            cout << "Matrix is singular - no unique solution.\n";
            return 1;
        }

        // 3. Swap the pivot row into position i (in both matrices)
        for (int c = 0; c < n; c++) {
            swap(A[i][c], A[pivotRow][c]);
            swap(inv[i][c], inv[pivotRow][c]);
        }

        // 4. Scale row i so the pivot becomes 1
        double pivot = A[i][i];
        for (int c = 0; c < n; c++) {
            A[i][c] /= pivot;
            inv[i][c] /= pivot;
        }

        // 5. Make every other row have 0 in column i
        for (int r = 0; r < n; r++) {
            if (r != i) {
                double factor = A[r][i];
                for (int c = 0; c < n; c++) {
                    A[r][c] -= factor * A[i][c];
                    inv[r][c] -= factor * inv[i][c];
                }
            }
        }
    }

    // ---- x = inv * b ----
    for (int i = 0; i < n; i++) {
        x[i] = 0;
        for (int j = 0; j < n; j++)
            x[i] += inv[i][j] * b[j];
    }

    // ---- Output ----
    cout << "\nInverse of A:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << inv[i][j] << "\t";
        cout << "\n";
    }

    cout << "\nSolution x:\n";
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << x[i] << "\n";

    return 0;
}