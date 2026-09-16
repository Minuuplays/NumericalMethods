#include <bits/stdc++.h>
using namespace std;

void printEq(vector<vector<double>> &A, vector<double> &b, int n) {
    cout << "\nThe system of equations is:\n";
    for(int i=0;i<n;i++){
        int count = 0;
        for(int j=0;j<n;j++){
            char a = 'x' + j;
            if (A[i][j] == 0) {
                continue;
            } else if (A[i][j] ==1){
                if (count > 0) cout << "+ ";
                cout << a << " ";
                count++;
            } else if (A[i][j] == -1){
                cout << "- ";
                cout << a << " ";
                count++;
            } else if(A[i][j] <0){
                cout << "- ";
                cout << abs(A[i][j]) << a << " ";
                count++;
            } else {
                if (count > 0) cout << "+ ";
                cout << abs(A[i][j]) << a << " ";
                count++;
            } 
        }
        cout << "= " << b[i] << endl;
    }
    cout << endl;
}

int main(){
    int n;
    cout << "Number of unknowns: ";
    cin >> n;

    // A is the coefficient matrix and b is the constant vector
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    cout << "Enter the coefficients and constants of each equation:" << endl;
    for(int i=0 ;i<n;i++){
        cout << "Equation " << i + 1 << ":\n";
        for(int j=0;j<n;j++){
            cin >> A[i][j];
        }
        cin >> b[i];
    }

    printEq(A, b, n);

    vector<vector<double>> L(n, vector<double>(n,0));
    vector<vector<double>> U(n, vector<double>(n,0));

    //Crout's method - U has unit diagonal elements
    for(int j=0;j<n;j++){
        for(int i=j;i<n;i++){ // column of L
            double sum = 0;
            for(int k=0;k<j;k++){
                sum += L[i][k] * U[k][j];
            }
            L[i][j]= A[i][j] - sum;
        }
        U[j][j] = 1; // diagonal of U is always 1
        for(int i=j+1;i<n;i++){ // row of U
            double sum = 0;
            for(int k=0;k<j;k++){
                sum += L[j][k]*U [k][i];
            }
            U[j][i] = (A[j][i] - sum)/L[j][j];
        }
    }
    
    cout << "Lower Triangular Matrix L:\n";
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout << L[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "Upper Triangular Matrix U:\n";
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout << U[i][j] << "  ";
        }
        cout << endl;
    }

    return 0;
}