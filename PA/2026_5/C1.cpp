#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n;
ll a[N];
ll sum;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        sum+=a[i];
    }
    for(int i=n+1;i;--i)a[i]-=a[i-1];
    for(int i=n;i;--i){
        if(sum%i!=0)continue;
        bool nf=1;
        for(int y=1;y<=i;++y){
            ll ns=0;
            bool fl=1;
            for(int j=y;j<=n+1;j+=i){
                ns+=a[j];
                if(ns<0){
                    fl=0;
                    break;
                }
            }
            fl&=(ns==0);
            if(!fl){
                nf=0;
                break;
            }
        }
        if(nf){
            cout<<i<<'\n';
            break;
        }
    }
    return 0;
}