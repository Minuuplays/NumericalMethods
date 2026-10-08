#include<bits/stdc++.h> //70-75 //needs modification
using namespace std;


int main(){
    int n;
    cin >> n;
    int x[n];
    int diff[n+1][n+1];
    for(int i=0;i<n;i++){
            cin >> x[i];
    }
    for(int i=0;i<n;i++){
        cin >>diff[i][0];
    }

    for(int j=1;j<n;j++){
        for(int i=0;i<(n-j);i++){
            diff[i][j]=diff[i+1][j-1]-diff[i][j-1];
        }
    }

    cout << endl;
    cout << "Difference Table:" << endl;

    for(int i=0;i<n;i++){
            cout << x[i] << "  ";
        for(int j=0;j<(n-i);j++){
            cout << diff [i][j] << "  ";
        }
        cout << endl;
    }

    double xp;
    cout << endl << "Approximate value to calculate :";
    cin >> xp;
    double h=x[1]-x[0];
    double u=(xp-x[0])/h;
    double res=diff[0][0];
    double term=1;

    for(int k=1;k<n;k++){
        term=term*(u-(k-1))/k;
        res = res + term*diff[0][k];
    }

    cout << "Output: " << res << endl;

    char ch='x';
    cout << "f(x) = " << diff[0][0];
    for(int i=1;i<n;i++){
        if (diff [0][i] > 0) cout << "+";
        cout << diff[0][i] << ch << "^" << i;
    }
    cout << endl;

    cout << "Equation:" << endl;
    cout << "f(" << xp << ") = " << diff[0][0];
    for (int i=1;i<n;i++){
        cout << "+("<<diff[0][i]<<")";
        for(int j=0;j<i;j++){
            cout<<"(x-"<<x[j]<<")";
        }
        cout<<"/("<<i << "!*h^"<<i<<")";
    }
    cout<<endl;

 

    return 0;
}

/*
5
35 45 55 65 75
31 42 51 35 31
*/