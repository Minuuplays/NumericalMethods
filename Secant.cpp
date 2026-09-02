#include <iostream>
#include <cmath>
using namespace std;

// Define f(x) here — edit this one function to solve a different equation
double f(double x) {
    return 3*x-cos(x)-1;   // example equation: x^3 - x - 2 = 0
}

int main() {
    double x0, x1, x2, E;
    int maxIter = 100;   // safety cap so a bad pair of guesses can't loop forever
    int iter = 0;

    // ---------- Step 1: choose TWO initial guesses x0, x1 and stopping criterion E ----------
    cout << "Enter x0 and x1: ";
    cin >> x0 >> x1;
    cout << "Enter stopping criterion E: ";
    cin >> E;

    cout << "\nIter\tx0\t\tx1\t\tf(x1)\t\tx2\n";

    do {
        double f0 = f(x0);
        double f1 = f(x1);

        if (f1 - f0 == 0.0) {
            cout << "\nf(x1) - f(x0) = 0 -> slope estimate is zero, method fails here. Try different guesses.\n";
            return 1;
        }

        // ---------- Step 2: x2 = x1 - f(x1)*(x1-x0) / (f(x1)-f(x0)) ----------
        x2 = x1 - (f1 * (x1 - x0)) / (f1 - f0);

        iter++;
        cout << iter << "\t" << x0 << "\t" << x1 << "\t" << f1 << "\t" << x2 << "\n";

        // ---------- Step 3 & 4: test convergence, then slide the window forward ----------
        if (fabs(x2 - x1) < E) {
            x1 = x2;
            break;
        }
        x0 = x1;   // both points shift forward — no bracket to maintain
        x1 = x2;

    } while (iter < maxIter);  // repeat from Step 2 until |x2 - x1| < E

    cout << "\nApproximate root = " << x1 << endl;
    cout << "Iterations taken = " << iter << endl;
    return 0;
}