#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll n,m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    if(n>m)swap(n,m);
    if(n==1){
        cout<<(m/6*6+max(0ll,(m%6-3)*2))<<'\n';
    }
    else if(m==2){
        cout<<"0\n";
    }
    else if(n%2==0&&m>=3){
        if(n==2){
            if(m==3||m==7)cout<<n*m-2<<'\n';
            else cout<<n*m<<'\n';
        }
        else cout<<n*m<<'\n';
    }
    else if(m%2==0&&n>=3){
        if(m==2){
            if(n==3||n==7)cout<<n*m-2<<'\n';
            else cout<<n*m<<'\n';
        }
        else cout<<n*m<<'\n';
    }
    else cout<<n*m/2*2<<'\n';
    return 0;
}