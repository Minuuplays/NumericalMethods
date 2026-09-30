// Newton's Forward Interpolation
// Works for equally spaced x values.
//
// f(x) = y0 + u*d1 + u(u-1)/2! * d2 + u(u-1)(u-2)/3! * d3 + ...
// where u = (x - x0) / h   and   dk = k-th forward difference at y0

#include <iostream>
using namespace std;

const int MAXN = 20;

int main() {
    int n;
    double x[MAXN], diff[MAXN][MAXN];

    // ---- Input ----
    cout << "Enter number of data points (max " << MAXN << "): ";
    cin >> n;

    cout << "Enter x values (equally spaced):\n";
    for (int i = 0; i < n; i++)
        cin >> x[i];

    cout << "Enter y values:\n";
    for (int i = 0; i < n; i++)
        cin >> diff[i][0];      // first column of the table is y

    double xp;
    cout << "Enter the x value to interpolate at: ";
    cin >> xp;

    // ---- Build forward difference table ----
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            diff[i][j] = diff[i + 1][j - 1] - diff[i][j - 1];

    // ---- Print the table ----
    cout << "\nForward difference table:\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] << "\t";
        for (int j = 0; j < n - i; j++)
            cout << diff[i][j] << "\t";
        cout << "\n";
    }

    // ---- Apply the formula ----
    double h = x[1] - x[0];
    double u = (xp - x[0]) / h;

    double result = diff[0][0];
    double term = 1;            // holds u(u-1)...(u-j+1) / j!

    for (int j = 1; j < n; j++) {
        term = term * (u - (j - 1)) / j;
        result += term * diff[0][j];
    }

    cout << "\nf(" << xp << ") = " << result << "\n";

    return 0;
}