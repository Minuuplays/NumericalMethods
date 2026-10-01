// Newton's Backward Interpolation
// Works for equally spaced x values. Best when the point is near the END of the table.
//
// f(x) = yn + v*d1 + v(v+1)/2! * d2 + v(v+1)(v+2)/3! * d3 + ...
// where v = (x - xn) / h   and   dk = k-th backward difference at yn (last point)

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

    // ---- Build backward difference table ----
    // CHANGE 1: each entry = itself minus the entry ABOVE it (forward used the one BELOW)
    // CHANGE 2: the loop starts at i = j (the table fills from the bottom up)
    for (int j = 1; j < n; j++)
        for (int i = j; i < n; i++)
            diff[i][j] = diff[i][j - 1] - diff[i - 1][j - 1];

    // ---- Print the table ----
    // CHANGE 3: row i has i+1 entries (forward had n-i)
    cout << "\nBackward difference table:\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] << "\t";
        for (int j = 0; j <= i; j++)
            cout << diff[i][j] << "\t";
        cout << "\n";
    }

    // ---- Apply the formula ----
    double h = x[1] - x[0];
    // CHANGE 4: measure from the LAST point (forward used x[0])
    double v = (xp - x[n - 1]) / h;

    // CHANGE 5: start from the LAST y value (forward used diff[0][0])
    double result = diff[n - 1][0];
    double term = 1;            // holds v(v+1)...(v+j-1) / j!

    for (int j = 1; j < n; j++) {
        // CHANGE 6: (v + (j-1)) instead of (u - (j-1))
        term = term * (v + (j - 1)) / j;
        // CHANGE 7: use the LAST row, diff[n-1][j] (forward used diff[0][j])
        result += term * diff[n - 1][j];
    }

    cout << "\nf(" << xp << ") = " << result << "\n";

    return 0;
}