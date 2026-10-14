// Curve fitting menu program
//   1) Linear regression                        y = a + b*x
//   2) Transcendental (exponential) regression  y = a * e^(b*x)
//   3) Polynomial regression                    y = a0 + a1*x + a2*x^2 + ... + am*x^m
//
// Exponential fit: ln(y) = ln(a) + b*x  -> straight line Y = A + B*x
//   where Y = ln(y), A = ln(a), B = b   (so a = e^A, b = B)
//
// Polynomial fit (least squares) -> normal equations, (m+1) x (m+1) system:
//   sum_j a_j * S(i+j) = T(i),   i = 0..m
//   where S(k) = sum of x^k,  T(i) = sum of x^i * y
// The system is solved with Gauss elimination (partial pivoting + back substitution).

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Least-squares straight line fit: y = A + B*x
void fitLine(const vector<double>& x, const vector<double>& y, double &A, double &B) {
    int n = x.size();
    double sx = 0, sy = 0, sxy = 0, sxx = 0;

    for (int i = 0; i < n; i++) {
        sx  += x[i];
        sy  += y[i];
        sxy += x[i] * y[i];
        sxx += x[i] * x[i];
    }

    B = (n * sxy - sx * sy) / (n * sxx - sx * sx);
    A = (sy - B * sx) / n;
}

// Solve M * c = rhs using Gauss elimination with partial pivoting.
// M is size x size, augmented internally. Returns false if the matrix is singular.
bool gaussSolve(vector<vector<double> > M, vector<double> rhs, vector<double>& c) {
    int size = rhs.size();

    // Build augmented matrix
    for (int i = 0; i < size; i++)
        M[i].push_back(rhs[i]);

    // Forward elimination
    for (int k = 0; k < size; k++) {
        // Partial pivoting: find the row with the largest |M[i][k]|
        int piv = k;
        for (int i = k + 1; i < size; i++)
            if (fabs(M[i][k]) > fabs(M[piv][k]))
                piv = i;

        if (fabs(M[piv][k]) < 1e-12)
            return false;               // singular / no unique solution

        if (piv != k)
            swap(M[piv], M[k]);

        for (int i = k + 1; i < size; i++) {
            double f = M[i][k] / M[k][k];
            for (int j = k; j <= size; j++)
                M[i][j] -= f * M[k][j];
        }
    }

    // Back substitution
    c.assign(size, 0.0);
    for (int i = size - 1; i >= 0; i--) {
        double s = M[i][size];
        for (int j = i + 1; j < size; j++)
            s -= M[i][j] * c[j];
        c[i] = s / M[i][i];
    }
    return true;
}

// Polynomial least-squares fit of degree m: coef[0] + coef[1]*x + ... + coef[m]*x^m
bool fitPoly(const vector<double>& x, const vector<double>& y, int m, vector<double>& coef) {
    int n = x.size();
    int size = m + 1;

    // Power sums S(k) = sum x^k, k = 0..2m
    vector<double> S(2 * m + 1, 0.0);
    for (int k = 0; k <= 2 * m; k++)
        for (int i = 0; i < n; i++)
            S[k] += pow(x[i], k);

    // T(i) = sum x^i * y, i = 0..m
    vector<double> T(size, 0.0);
    for (int k = 0; k <= m; k++)
        for (int i = 0; i < n; i++)
            T[k] += pow(x[i], k) * y[i];

    // Normal equation matrix
    vector<vector<double> > M(size, vector<double>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            M[i][j] = S[i + j];

    return gaussSolve(M, T, coef);
}

int main() {
label:
    int choice;
    cout << "\n===== Curve Fitting =====\n";
    cout << "1. Linear regression         (y = a + b x)\n";
    cout << "2. Transcendental regression (y = a e^(b x))\n";
    cout << "3. Polynomial regression     (y = a0 + a1 x + ... + am x^m)\n";
    cout << "Choose equation type (1/2/3): ";
    cin >> choice;

    if (choice != 1 && choice != 2 && choice != 3) {
        cout << "Invalid choice!\n";
        goto label;
    }

    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter x and y values (one pair per line):\n";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    if (choice == 1) {
        // ---------- Linear regression ----------
        double a, b;
        fitLine(x, y, a, b);
        cout << "\nLinear fit:  y = " << a << " + " << b << " x\n";
    }
    else if (choice == 2) {
        // ---------- Transcendental regression ----------
        vector<double> lnY(n);
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (y[i] <= 0) { ok = false; break; }
            lnY[i] = log(y[i]);
        }

        if (!ok) {
            cout << "\nExponential fit needs all y > 0.\n";
        } else {
            double A, B;
            fitLine(x, lnY, A, B);
            cout << "\nExponential fit:  y = " << exp(A) << " * e^(" << B << " x)\n";
        }
    }
    else {
        // ---------- Polynomial regression ----------
        int m;
        cout << "Enter degree of polynomial: ";
        cin >> m;

        if (m < 1 || m >= n) {
            cout << "\nDegree must be at least 1 and less than the number of data points.\n";
        } else {
            vector<double> coef;
            if (!fitPoly(x, y, m, coef)) {
                cout << "\nNormal equations are singular - cannot solve.\n";
            } else {
                cout << "\nPolynomial fit (degree " << m << "):\n  y = " << coef[0];
                for (int i = 1; i <= m; i++) {
                    if (coef[i] >= 0) cout << " + " << coef[i];
                    else              cout << " - " << -coef[i];
                    cout << " x";
                    if (i > 1) cout << "^" << i;
                }
                cout << "\n\nCoefficients:\n";
                for (int i = 0; i <= m; i++)
                    cout << "  a" << i << " = " << coef[i] << "\n";
            }
        }
    }

    char ch;
    cout << "\nSolve another system? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y') goto label;

    return 0;
}