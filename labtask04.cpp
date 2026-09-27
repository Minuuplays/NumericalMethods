#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int rankk(vector<vector<double>> m) {
    int p = m.size();
    int q = m[0].size();
    int rnk = 0;
    for (int col = 0; col < q && rnk < p; col++) {
        int pivot = rnk;
        for (int i = rnk + 1; i < p; i++) {
            if (fabs(m[i][col]) > fabs(m[pivot][col])) {
                pivot = i;
            }
        }
        if (fabs(m[pivot][col]) < 1e-12) continue;   // fixed parenthesis bug
        swap(m[rnk], m[pivot]);
        for (int i = rnk + 1; i < p; i++) {
            double factor = m[i][col] / m[rnk][col];
            for (int j = col; j < q; j++) {
                m[i][j] -= factor * m[rnk][j];
            }
        }
        rnk++;
    }
    return rnk;
}

void printMatrix(const vector<vector<double>> &U, int step) {
    cout << "\n--- Matrix after step " << step << " ---\n";
    int n = U.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)U[i].size(); j++) {
            cout << fixed << setprecision(4) << setw(10) << U[i][j] << " ";
        }
        cout << "\n";
    }
}

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

        printMatrix(U, k + 1);   // show matrix after each elimination step
    }

    for (int i = 0; i < n; i++)
        X[i] = U[i][n];

    return true;
}

int main(){
label:int n;
    cout << "Enter number of equations: ";
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> aug(n, vector<double>(n + 1));   // fixed: n x (n+1)
    vector<double> b(n);
    vector<double> x(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
        cin >> b[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n] = b[i];
    }

    int rA  = rankk(A);
    int rAg = rankk(aug);
    cout << "Rank of A: " << rA << endl;
    cout << "Rank of Augmented: " << rAg << endl;

    if (rA == rAg && rA == n) {
        cout << "Unique solution exists.\n";

        bool ok = gauss(aug, x);
        if (!ok) {
            cout << "Gauss-Jordan failed (singular pivot encountered).\n";
        } else {
            cout << "\nSolution:\n";
            for (int i = 0; i < n; i++)
                cout << "x" << i + 1 << " = " << fixed << setprecision(6) << x[i] << endl;

            // Verification: plug x back into A*x and compare with b
            cout << "\nVerification (A * x vs b):\n";
            bool valid = true;
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int j = 0; j < n; j++)
                    sum += A[i][j] * x[j];
                cout << "Row " << i + 1 << ": computed = " << fixed << setprecision(6)
                     << sum << " , expected = " << b[i];
                if (fabs(sum - b[i]) > 1e-6) {
                    cout << "  --> MISMATCH";
                    valid = false;
                }
                cout << endl;
            }
            cout << (valid ? "\nSolution verified successfully.\n"
                            : "\nSolution verification FAILED.\n");
        }
    } else if (rA != rAg) {
        cout << "No solution (inconsistent system)." << endl;
    } else {
        cout << "Infinite solutions (rank < n, consistent system)." << endl;
    }

    char ch;
    cout << "\nSolve another system? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y') goto label;

    return 0;
}

/*
5
2 1 -1 3 2 9
1 3 2 -1 1 8
3 2 4 1 -2 20
2 1 3 2 1 17
1 -1 2 3 4 15
*/