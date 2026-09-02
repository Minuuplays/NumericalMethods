#include <iostream>
#include <cmath>

using namespace std;

// Function to evaluate the polynomial: f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x + a0
double evaluate(double x, double a4, double a3, double a2, double a1, double a0) {
    return a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
}

// Simple function to print terms with the correct sign (+ or -)
void printTerm(double coeff, int power) {
    if (coeff == 0) return; // Skip zero terms

    if (coeff > 0) {
        cout << " + " << coeff << "x^" << power;
    } else {
        cout << " - " << abs(coeff) << "x^" << power;
    }
}

int main() {
    double a4, a3, a2, a1, a0;

    cout << "Enter 5 coefficients (a4, a3, a2, a1, a0): ";
    cin >> a4 >> a3 >> a2 >> a1 >> a0;

    // 1. Print equation directly in a plain line checking signs
    cout << "\nEquation: " << a4 << "x^4";
    printTerm(a3, 3);
    printTerm(a2, 2);
    printTerm(a1, 1);
    
    if (a0 > 0) {
        cout << " + " << a0;
    } else if (a0 < 0) {
        cout << " - " << abs(a0);
    }
    cout << " = 0\n\n";

    // 2. Calculate xmax bound: sqrt( (a3/a4)^2 - 2*(a2/a4) )
    double term1 = pow(a3 / a4, 2);
    double term2 = 2.0 * (a2 / a4);
    double xmax = sqrt(abs(term1 - term2));

    double E = 0.001;      // Error tolerance 10^-3
    double step = 0.4;     // Step size
    int rootCount = 0;     // Counter for roots found

    // 3. Search intervals from -xmax to +xmax using step size 0.4
    for (double i = -xmax; i < xmax; i += step) {
        double j = i + step;
        if (j > xmax) j = xmax; // Don't exceed xmax

        double f_i = evaluate(i, a4, a3, a2, a1, a0);
        double f_j = evaluate(j, a4, a3, a2, a1, a0);

        // Sign change check: f(i) * f(j) <= 0
        if (f_i * f_j <= 0) {
            rootCount++;

            // --- False Position Loop ---
            double x1 = i;
            double x2 = j;
            double c = x1;
            double c_old = x1;
            int iterations = 0;

            do{
                // 1. Save the previous root estimate BEFORE computing the new one
                c_old = c;

                iterations++;

                // 2. Compute function values at bounds
                double f1 = evaluate(x1, a4, a3, a2, a1, a0);
                double f2 = evaluate(x2, a4, a3, a2, a1, a0);

                // 3. Compute new root estimate 'c' using False Position
                c = x1 - (f1 * (x2 - x1)) / (f2 - f1);
                double fc = evaluate(c, a4, a3, a2, a1, a0);

                // 4. Update the interval
                if (f1 * fc < 0)
                {
                    x2 = c;
                }
                else
                {
                    x1 = c;
                }

                // 5. Keep looping as long as error >= E AND iteration limit not hit
            } while (iterations == 1 || (abs((c - c_old) / c) >= E && iterations < 1000));

            /*while (true) {
                iterations++;

                double f1 = evaluate(x1, a4, a3, a2, a1, a0);
                double f2 = evaluate(x2, a4, a3, a2, a1, a0);

                // False position formula
                c = x1 - (f1 * (x2 - x1)) / (f2 - f1);
                double fc = evaluate(c, a4, a3, a2, a1, a0);

                // Stop condition: |(c_new - c_old) / c_new| < E
                if (iterations > 1 && abs((c - c_old) / c) < E) {
                    break;
                }

                // Update interval
                if (f1 * fc < 0) {
                    x2 = c;
                } else {
                    x1 = c;
                }

                c_old = c;

                // Safety guard against infinite loops
                if (iterations > 1000) break;
            }*/

            // Print output for this root
            cout << "Root " << rootCount << " : x = " << c << endl;
            cout << "Search interval for root " << rootCount << " = [" << i << ", " << j << "]" << endl;
            cout << "Iteration needed for root " << rootCount << " = " << iterations << "\n\n";
        }
    }

    if (rootCount == 0) {
        cout << "No real roots found in the range [-|xmax|, |xmax|]." << endl;
    }

    return 0;
}