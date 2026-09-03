#include <bits/stdc++.h>
using namespace std;

double evaluate(vector<double>& co, double x){
    double res = 0;
    for(auto c : co){
        res = res * x + c;
    }
    return res;
}

void printterm(double co, int power){
    if (co == 0) return;
    if (co > 0) cout << " +" << co << "x^" << power;
    else cout << " -" << abs(co) << "x^" << power;
}

int main(){
    int d;
    double E = 0.0001;
    cout << "No. of degree of the equation : ";
    cin >> d;
    vector<double> coeff(d + 1);
    cout << "Coefficient of the equation: ";
    for (int i = 0; i <= d; i++){
        cin >> coeff[i];
    }

    // Print original equation
    cout << "f(x) = ";
    if (coeff[0] == 0) {
    } else if (coeff[0] == 1){
        cout << "x^" << d;
    } else {
        cout << coeff[0] << "x^" << d;
    }
    for(int i = 1; i < d; i++){
        printterm(coeff[i], (d - i));
    }
    if (coeff[d] == 0){
    } else if (coeff[d] > 0){
        cout << " +" << coeff[d];
    } else {
        cout << " -" << abs(coeff[d]);
    }
    cout << endl;

    // Compute derivative coefficients
    vector<double> der_coeff(d);
    for(int i = 0; i < d; i++){
        der_coeff[i] = coeff[i] * (d - i);
    }

    // Print derivative equation using the same simple logic
    int der_d = d - 1;
    cout << "f'(x) = ";
    if (der_d >= 0) {
        if (der_coeff[0] == 0) {
        } else if (der_coeff[0] == 1){
            if (der_d > 0) cout << "x^" << der_d;
            else cout << "1";
        } else {
            cout << der_coeff[0];
            if (der_d > 0) cout << "x^" << der_d;
        }
        for(int i = 1; i < der_d; i++){
            printterm(der_coeff[i], (der_d - i));
        }
        if (der_d > 0) {
            if (der_coeff[der_d] == 0){
            } else if (der_coeff[der_d] > 0){
                cout << " +" << der_coeff[der_d];
            } else {
                cout << " -" << abs(der_coeff[der_d]);
            }
        }
    }
    cout << endl;

    double maxx = 0.0;
    for(int i = 0; i <= d; i++){
        maxx = max(maxx, (fabs(coeff[i]/coeff[0])));
    }
    double xmax = 1 + maxx;

    cout << "\nInterval :[-" << xmax << "," << xmax << "]" << endl;

    double step = 0.5;
    cout << "\n--- Newton-Raphson Root Finding ---" << endl;

    for(double x0 = -xmax; x0 <= xmax; x0 += step){
        double y0 = evaluate(coeff, x0);
        double y1 = evaluate(coeff, x0 + step);

        if(y0 * y1 <= 0 || fabs(y0) < 1e-5){
            double x = x0;
            int iter = 0;
            int max_iter = 100;

            cout << "\nRoot search near initial guess x = " << x << endl;
            cout << left << setw(12) << "Iteration" << setw(15) << "x" << setw(15) << "f(x)" << endl;
            cout << string(42, '-') << endl;

            while(iter < max_iter){
                double fx = evaluate(coeff, x);
                double dfx = evaluate(der_coeff, x);

                cout << left << setw(12) << iter + 1 << setw(15) << fixed << setprecision(5) << x << setw(15) << fx << endl;

                if(fabs(fx) < E){
                    cout << "--> Converged to root: " << x << " in " << iter + 1 << " iterations.\n";
                    break;
                }

                if(fabs(dfx) < 1e-12){
                    cout << "--> Derivative too small. Stopping search in this interval.\n";
                    break;
                }

                double x_next = x - fx / dfx;
                if(fabs(x_next - x) < E){
                    cout << "--> Converged to root: " << x_next << " in " << iter + 2 << " iterations.\n";
                    break;
                }

                x = x_next;
                iter++;
            }
        }
    }

    return 0;
}