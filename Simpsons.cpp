// Numerical integration: Simpson's 1/3 rule and Simpson's 3/8 rule
//
//   Integral of f(x) from a to b,   h = (b - a) / n
//
// Simpson's 1/3 rule  (n must be EVEN):
//   I = h/3 * [ y0 + 4*(y1 + y3 + y5 + ...) + 2*(y2 + y4 + ...) + yn ]
//
// Simpson's 3/8 rule  (n must be a MULTIPLE OF 3):
//   I = 3h/8 * [ y0 + 3*(y1 + y2 + y4 + y5 + ...) + 2*(y3 + y6 + ...) + yn ]
//
// To integrate a different function, change f(x) below.

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Function to integrate   (edit this for your problem)
double f(double x) {
    return 1.0 / (1.0 + x * x);
}

// Simpson's 1/3 rule. n must be even.
double simpson13(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) sum += 2 * f(x);
        else            sum += 4 * f(x);
    }

    return sum * h / 3.0;
}

// Simpson's 3/8 rule. n must be a multiple of 3.
double simpson38(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 3 == 0) sum += 2 * f(x);
        else            sum += 3 * f(x);
    }

    return sum * 3.0 * h / 8.0;
}

int main() {
label:
    int choice;
    cout << "\n===== Simpson's Rule Integration =====\n";
    cout << "1. Simpson's 1/3 rule  (n must be even)\n";
    cout << "2. Simpson's 3/8 rule  (n must be a multiple of 3)\n";
    cout << "Choose rule (1/2): ";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "Invalid choice!\n";
        goto label;
    }

    double a, b;
    int n;
    cout << "Enter lower limit a: ";
    cin >> a;
    cout << "Enter upper limit b: ";
    cin >> b;
    cout << "Enter number of sub-intervals n: ";
    cin >> n;

    cout << fixed << setprecision(8);

    if (choice == 1) {
        if (n <= 0 || n % 2 != 0)
            cout << "\nSimpson's 1/3 rule needs n to be a positive even number.\n";
        else
            cout << "\nSimpson's 1/3 rule:  integral = " << simpson13(a, b, n) << "\n";
    }
    else {
        if (n <= 0 || n % 3 != 0)
            cout << "\nSimpson's 3/8 rule needs n to be a positive multiple of 3.\n";
        else
            cout << "\nSimpson's 3/8 rule:  integral = " << simpson38(a, b, n) << "\n";
    }

    char ch;
    cout << "\nSolve another integral? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y') goto label;

    return 0;
}