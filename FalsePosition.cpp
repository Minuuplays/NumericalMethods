#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;

// Define f(x) here — edit this one function to solve a different equation
double f(double x) {
    return 3*x-cos(x)-1;   // example equation: x^3 - x - 2 = 0
}

int main() {
    double x1, x2, x0, E;
    int maxIter = 100;   // safety cap so a bad input can't loop forever
    int iter = 0;

    // ---------- Step 1: choose x1, x2 with f(x1)*f(x2) < 0, and E ----------
    cout << "Enter x1 and x2: ";
    cin >> x1 >> x2;
    cout << "Enter stopping criterion E: ";
    cin >> E;

    if (f(x1) * f(x2) >= 0) {
        cout << "f(x1)*f(x2) is not < 0 -> no guaranteed root in [x1,x2]. Try different values.\n";
        return 1;
    }

    cout << "\nIter\tx1\t\tx2\t\tx0\t\tf(x0)\n";

    do {
        // ---------- Step 2: x0 = x1 - f(x1)*(x2-x1) / (f(x2)-f(x1)) ----------
        // (this is the "false position" formula — a weighted point on the chord 
        // joining (x1,f(x1)) and (x2,f(x2)), instead of the plain midpoint used in bisection)
        x0 = x1 - (f(x1) * (x2 - x1)) / (f(x2) - f(x1));

        // ---------- Step 3: find f(x0) ----------
        double f0 = f(x0);

        iter++;
        cout << iter << "\t" << x1 << "\t" << x2 << "\t" << x0 << "\t" << f0 << "\n";

        // ---------- Step 4: test f(x0) and update bracket ----------
        if (f0 == 0.0) {
            cout << "\nExact root found: x0 = " << x0 << endl;
            break;
        }
        if (f0 * f(x1) < 0) {
            x2 = x0;              // root is between x1 and x0
        }
        else if (f0 * f(x2) < 0) {
            x1 = x0;              // root is between x0 and x2
        }

    } while (fabs((x2 - x1) / x2) >= E && iter < maxIter);   // repeat from Step 2 until |(x2-x1)/x2| < E

    cout << "\nApproximate root = " << x0 << endl;
    cout << "Iterations taken = " << iter << endl;
    return 0;
}