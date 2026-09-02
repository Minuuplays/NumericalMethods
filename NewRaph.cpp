#include <bits/stdc++.h>
using namespace std;

// define f(x) here — edit this one function to solve a different equation
double f(double x) {
    return 3*x-cos(x)-1;   // example equation: x^3 - x - 2 = 0
}

// define f'(x) here — edit this one function to solve a different equation
double fder(double x) {
    return 3+sin(x);   // example equation: 3x^2 - 1 = 0
}

int main() {
    double x0, x1, E;
    int maxIter = 100;   // safety cap so a bad guess/derivative can't loop forever
    int iter = 0;

    // ---------- Step 1: choose ONE initial guess x0 and stopping criterion E ----------
    // (no bracket needed here — Newton-Raphson is an "open" method, unlike
    //  bisection/false position which needed f(x1)*f(x2) < 0)
    cout << "Enter initial guess x0: ";
    cin >> x0;
    cout << "Enter stopping criterion E: ";
    cin >> E;

    cout << "\nIter\tx0\t\tf(x0)\t\tf'(x0)\t\tx1\n";

    do {
        double f0  = f(x0);
        double fp0 = fder(x0);

        if (fp0 == 0.0) {
            cout << "\nf'(x0) = 0 -> tangent line is horizontal, method fails here. Try a different x0.\n";
            return 1;
        }

        // ---------- Step 2: x1 = x0 - f(x0)/f'(x0) ----------
        // (this is where the tangent line at (x0,f(x0)) crosses the x-axis —
        //  the "linear approximation" replacing the chord/midpoint used in bisection and false position)
       
        x1 = x0 - f0 / fp0;

        iter++;
        cout << iter << "\t" << x0 << "\t" << f0 << "\t" << fp0 << "\t" << x1 << "\n";

        // ---------- Step 3: test convergence, then move x0 forward ----------
        if (fabs(x1 - x0) < E) {
            x0 = x1;
            break;
        }
        x0 = x1;

    } while (iter < maxIter);// repeat from Step 2 until |x1 - x0| < E

    cout << "\nApproximate root = " << x0 << endl;
    cout << "Iterations taken = " << iter << endl;
    return 0;
}