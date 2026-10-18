// Runge-Kutta 4th order (RK4) method for a first order ODE
//
//   dy/dx = f(x, y),   y(x0) = y0
//
// For each step of size h:
//   k1 = h * f(x,       y)
//   k2 = h * f(x + h/2, y + k1/2)
//   k3 = h * f(x + h/2, y + k2/2)
//   k4 = h * f(x + h,   y + k3)
//   y_new = y + (k1 + 2*k2 + 2*k3 + k4) / 6
//   x_new = x + h
//
// To solve a different equation, change the function f(x, y) below.

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Right-hand side of dy/dx = f(x, y)   (edit this for your problem)
double f(double x, double y) {
    return x + y;
}

int main() {
    double x0, y0, h, xn;

    cout << "===== Runge-Kutta 4th Order Method =====\n";
    cout << "Solving dy/dx = f(x, y)   (edit f() in the code)\n\n";
    cout << "Enter initial x0: ";
    cin >> x0;
    cout << "Enter initial y0: ";
    cin >> y0;
    cout << "Enter step size h: ";
    cin >> h;
    cout << "Enter x at which y is required: ";
    cin >> xn;

    if (h <= 0) {
        cout << "\nStep size must be positive.\n";
        return 1;
    }
    if (xn < x0) {
        cout << "\nTarget x must be greater than or equal to x0.\n";
        return 1;
    }

    int steps = (int)ceil((xn - x0) / h - 1e-9);   // number of steps needed
    double x = x0, y = y0;

    cout << fixed << setprecision(6);
    cout << "\n" << setw(4) << "i" << setw(12) << "x" << setw(12) << "k1"
         << setw(12) << "k2" << setw(12) << "k3" << setw(12) << "k4"
         << setw(14) << "y" << "\n";
    cout << setw(4) << 0 << setw(12) << x << setw(60) << y << "\n";

    for (int i = 1; i <= steps; i++) {
        // Last step is shortened if needed so we land exactly on xn
        double hh = h;
        if (x + hh > xn) hh = xn - x;

        double k1 = hh * f(x, y);
        double k2 = hh * f(x + hh / 2, y + k1 / 2);
        double k3 = hh * f(x + hh / 2, y + k2 / 2);
        double k4 = hh * f(x + hh, y + k3);

        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x += hh;

        cout << setw(4) << i << setw(12) << x << setw(12) << k1 << setw(12) << k2
             << setw(12) << k3 << setw(12) << k4 << setw(14) << y << "\n";
    }

    cout << "\nResult: y(" << x << ") = " << y << "\n";

    return 0;
}