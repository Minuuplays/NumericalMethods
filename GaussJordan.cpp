#include<bits/stdc++.h>
using namespace std;

int rnk(vector<vector<double>>A){

int rows=A.size();
int cols=A[0].size();

int rank=0;

for(int col=0;col<cols && rank<rows;col++){
    int pivot=rank;
    for(int i=rank+1;i<rows;i++){
        if(fabs(A[i][col])>fabs(A[pivot][col])){
            pivot=i;
        }

    }
    if(fabs(A[pivot][col])<1e-12)
        continue;
    swap(A[rank],A[pivot]);
    for(int i=rank+1;i<rows;i++){
        double factor=A[i][col]/A[rank][col];
        for(int j=col;j<cols;j++){
            A[i][j]=A[i][j]-factor*A[rank][j];
        }
    }
    rank++;
}
return rank;
}

bool guss(vector<vector<double>>A,vector<double>B,vector<double> &X){

int n=A.size();

//for(int i=0;i<n;i++){
    //if(fabs(A[i][i])<1e-12){
       // return false;
   // }


for(int k=0;k<n-1;k++){
    for(int i=k+1;i<n;i++){
        double factor=A[i][k]/A[k][k];
        for(int j=k;j<n;j++){
            A[i][j]=A[i][j]-factor*A[k][j];
        }
        B[i]=B[i]-factor*B[k];
    }
}

for(int i=n-1;i>=0;i--){
        double sum=B[i];
    for(int j=i+1;j<n;j++){
        sum -= A[i][j]*X[j];
    }
X[i]=sum/A[i][i];
}
return true;
}

int main(){

int n;
cin>>n;

vector<vector<double>>A(n,vector<double>(n));
vector<double>B(n);

for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        cin>>A[i][j];
    }
}
for(int i=0;i<n;i++){
    cin>>B[i];
}
int rnkA=rnk(A);
cout<<"Rank of A: "<<rnkA<<endl;
cout<<"------------------\n";

vector<double>X(n,0);
if(guss(A,B,X)){
    cout<<"The solution:\n";
    for(int i=0;i<n;i++){
    cout<<"x"<<i+1<<" = "<<X[i]<<endl;
    }

}
else{
    cout<<"Not exist\n"<<endl;
}
return 0;
}
gauss eli eita