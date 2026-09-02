#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to format and print the standard quartic equation string
void printEquation(double a4, double a3, double a2, double a1, double a0) {
    cout << "Equation: ";
    
    // Print term 4
    if (a4 == 1) cout << "x\u2074";
    else if (a4 == -1) cout << "-x\u2074";
    else cout << a4 << "x\u2074";

    // Helper lambda for print formatting
    auto printTerm = [](double coeff, int power) {
        if (coeff == 0) return;
        if (coeff > 0) cout << "+" << (coeff == 1 ? "" : to_string((int)coeff));
        else cout << "-" << (abs(coeff) == 1 ? "" : to_string((int)abs(coeff)));
        
        if (power == 3) cout << "x\u00B3";
        else if (power == 2) cout << "x\u00B2";
        else if (power == 1) cout << "x";
    };

    printTerm(a3, 3);
    printTerm(a2, 2);
    printTerm(a1, 1);

    if (a0 > 0) cout << "+" << a0;
    else if (a0 < 0) cout << a0;

    cout << "\n\n";
}

// Function to evaluate polynomial f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x + a0
double evaluatePolynomial(double x, double a4, double a3, double a2, double a1, double a0) {
    return a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
}

// False Position (Regula Falsi) Root Finder
double solveFalsePosition(double lower, double upper, double a4, double a3, double a2, double a1, double a0, double E, int &iterations) {
    double x1 = lower;
    double x2 = upper;
    double c_prev = x1;
    double c = x1;
    iterations = 0;

    while (true) {
        iterations++;
        double f1 = evaluatePolynomial(x1, a4, a3, a2, a1, a0);
        double f2 = evaluatePolynomial(x2, a4, a3, a2, a1, a0);

        // False Position Formula: x = x1 - f(x1)*(x2 - x1)/(f(x2) - f(x1))
        c = x1 - (f1 * (x2 - x1)) / (f2 - f1);
        double fc = evaluatePolynomial(c, a4, a3, a2, a1, a0);

        // Check relative error stopping condition: |(x2 - x1) / x2| < E
        if (iterations > 1 && abs((c - c_prev) / c) < E) {
            break;
        }

        // Bracket update
        if (f1 * fc < 0) {
            x2 = c;
        } else {
            x1 = c;
        }

        c_prev = c;

        // Guard against infinite loop
        if (iterations > 10000) break; 
    }

    return c;
}

int main() {
    // Parsing inputs: coefficients vector
    string inputStr;
    cout << "Enter the coefficients of a quadruple equation (e.g., 1.0 -5.0 4 or 1 -3 2 6 0):\n";
    getline(cin, inputStr);

    stringstream ss(inputStr);
    vector<double> coeffs;
    double temp;
    while (ss >> temp) {
        coeffs.push_back(temp);
    }

    // Standardize coefficients for degree-4 polynomial
    double a4 = 0, a3 = 0, a2 = 0, a1 = 0, a0 = 0;
    if (coeffs.size() == 5) {
        a4 = coeffs[0]; a3 = coeffs[1]; a2 = coeffs[2]; a1 = coeffs[3]; a0 = coeffs[4];
    } else if (coeffs.size() == 3) { // Reduced degree format like x^4 - 5x^2 + 4
        a4 = coeffs[0]; a3 = 0; a2 = coeffs[1]; a1 = 0; a0 = coeffs[2];
    } else {
        cout << "Invalid input format!" << endl;
        return 1;
    }

    // 1. Print formatted equation
    printEquation(a4, a3, a2, a1, a0);

    // 2. Calculate |xmax| bound formula: sqrt( (A_{n-1}/A_n)^2 - 2*(A_{n-2}/A_n) )
    double term1 = pow(a3 / a4, 2);
    double term2 = 2.0 * (a2 / a4);
    double xmax = sqrt(abs(term1 - term2));

    double E = 1e-3;
    double step = 0.4;

    string ordinals[] = {"First", "Second", "Third", "Fourth"};
    int rootCount = 0;

    // 3. Search intervals [-xmax, xmax] with step 0.4
    for (double i = -xmax; i < xmax; i += step) {
        double j = min(i + step, xmax);
        
        double f_i = evaluatePolynomial(i, a4, a3, a2, a1, a0);
        double f_j = evaluatePolynomial(j, a4, a3, a2, a1, a0);

        // Check for bracket root sign change: f(a) * f(b) <= 0
        if (f_i * f_j <= 0) {
            int iterations = 0;
            double root = solveFalsePosition(i, j, a4, a3, a2, a1, a0, E, iterations);

            string ordinal = (rootCount < 4) ? ordinals[rootCount] : to_string(rootCount + 1) + "th";

            cout << setprecision(4) << fixed;
            cout << ordinal << " root : x = " << root << endl;
            cout << "Search interval for " << ordinal << " root = [" << i << ", " << j << "]" << endl;
            cout << "Iteration needed for " << ordinal << " root = " << iterations << "\n\n";

            rootCount++;
        }
    }

    if (rootCount == 0) {
        cout << "No real roots found in the given range [-|xmax|, |xmax|]." << endl;
    }

    return 0;
}