#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
int n,m;
int a[N],b[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    if(n<=2){
        if(n==1)a[1]=1;
        else a[1]=3,a[2]=4;
    }
    else{
        for(int i=1;i<n;++i)a[i]=2;
        a[n]=n-2;
    }
    if(m<=2){
        if(m==1)b[1]=1;
        else b[1]=3,b[2]=4;
    }
    else{
        for(int i=1;i<m;++i)b[i]=2;
        b[m]=m-2;
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cout<<a[i]*b[j]<<' ';
        }cout<<'\n';
    }
    return 0;
}