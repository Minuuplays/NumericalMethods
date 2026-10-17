// Jacobi iteration method for a system of 3 linear equations
//
//   a11 x + a12 y + a13 z = b1
//   a21 x + a22 y + a23 z = b2
//   a31 x + a32 y + a33 z = b3
//
// Rearranged form (every new value uses ONLY the previous iteration's values):
//   x_new = (b1 - a12*y - a13*z) / a11
//   y_new = (b2 - a21*x - a23*z) / a22
//   z_new = (b3 - a31*x - a32*y) / a33
//
// Converges if the matrix is diagonally dominant (|aii| > sum of |aij|, j != i).

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a[3][3], b[3];

    cout << "===== Jacobi Iteration Method =====\n";
    cout << "Enter the coefficients and constant of each equation\n";
    cout << "(a1 a2 a3 b, one equation per line):\n";
    for (int i = 0; i < 3; i++) {
        cout << "Equation " << i + 1 << ": ";
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> b[i];
    }

    // Diagonal elements must be non-zero
    for (int i = 0; i < 3; i++) {
        if (fabs(a[i][i]) < 1e-12) {
            cout << "\nDiagonal element a" << i + 1 << i + 1
                 << " is zero. Rearrange the equations and try again.\n";
            return 1;
        }
    }

    // Warn if not diagonally dominant
    bool dominant = true;
    for (int i = 0; i < 3; i++) {
        double sum = 0;
        for (int j = 0; j < 3; j++)
            if (j != i) sum += fabs(a[i][j]);
        if (fabs(a[i][i]) <= sum) dominant = false;
    }
    if (!dominant)
        cout << "\nWarning: system is not diagonally dominant; "
                "the method may not converge.\n";

    double tol;
    int maxIter;
    cout << "\nEnter tolerance (e.g. 0.0001): ";
    cin >> tol;
    cout << "Enter maximum iterations: ";
    cin >> maxIter;

    double x = 0, y = 0, z = 0;           // initial guess
    cout << "\nIter" << setw(14) << "x" << setw(14) << "y" << setw(14) << "z" << "\n";
    cout << fixed << setprecision(6);

    bool converged = false;
    int it;
        for (it = 1; it <= maxIter; it++) {
        double xo = x, yo = y, zo = z;

        x = (b[0] - a[0][1] * y - a[0][2] * z) / a[0][0];
        y = (b[1] - a[1][0] * x - a[1][2] * z) / a[1][1];   // uses new x
        z = (b[2] - a[2][0] * x - a[2][1] * y) / a[2][2];   // uses new x and y

        cout << setw(4) << it << setw(14) << x << setw(14) << y << setw(14) << z << "\n";

        double err = max(fabs(x - xo), max(fabs(y - yo), fabs(z - zo)));

        if (err < tol) { converged = true; break; }
    }

    if (converged)
        cout << "\nConverged after " << it << " iterations.\n";
    else
        cout << "\nDid not converge within " << maxIter << " iterations.\n";

    cout << "\nSolution:\n";
    cout << "  x = " << x << "\n";
    cout << "  y = " << y << "\n";
    cout << "  z = " << z << "\n";

    return 0;
}