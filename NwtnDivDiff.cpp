// Newton's Divided Difference Interpolation
// Works for ANY x values (equal or unequal spacing).
//
// f(x) = f[x0] + (x-x0)*f[x0,x1] + (x-x0)(x-x1)*f[x0,x1,x2] + ...
// where f[...] are the divided differences stored in the top row of the table

#include <iostream>
using namespace std;

const int MAXN = 20;

int main() {
    int n;
    double x[MAXN], dd[MAXN][MAXN];

    // ---- Input ----
    cout << "Enter number of data points (max " << MAXN << "): ";
    cin >> n;

    cout << "Enter x values (any spacing):\n";
    for (int i = 0; i < n; i++)
        cin >> x[i];

    cout << "Enter y values:\n";
    for (int i = 0; i < n; i++)
        cin >> dd[i][0];        // first column of the table is y

    double xp;
    cout << "Enter the x value to interpolate at: ";
    cin >> xp;

    // ---- Build divided difference table ----
    // CHANGE 1: divide each difference by the x-distance it spans
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            dd[i][j] = (dd[i + 1][j - 1] - dd[i][j - 1]) / (x[i + j] - x[i]);

    // ---- Print the table ----
    cout << "\nDivided difference table:\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] << "\t";
        for (int j = 0; j < n - i; j++)
            cout << dd[i][j] << "\t";
        cout << "\n";
    }

    // ---- Apply the formula ----
    double result = dd[0][0];
    double product = 1;         // holds (x-x0)(x-x1)...(x-x_{j-1})

    for (int j = 1; j < n; j++) {
        // CHANGE 2: no u or h; multiply by the actual factor (xp - x[j-1])
        product = product * (xp - x[j - 1]);
        result += product * dd[0][j];
    }

    cout << "\nf(" << xp << ") = " << result << "\n";

    return 0;
}