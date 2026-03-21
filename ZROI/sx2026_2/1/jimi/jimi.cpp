#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=20;
const int mod=1e9+7;
int n,m;
int a[1<<N];
struct mt{
    ll a[2][2];
    ll* operator[](const int& id){return a[id];}
    mt operator*(mt y){
        mt as;
        for(int i=0;i<2;++i){
            for(int j=0;j<2;++j){
                as[i][j]=0;
                for(int k=0;k<2;++k){
                    as[i][j]=(as[i][j]+a[i][k]*y[k][j])%mod;
                }
            }
        }
        return as;
    }
}xs;
int main(){
    freopen("jimi.in","r",stdin);
    freopen("jimi.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=0;i<(1<<n);++i){
        cin>>a[i];
    }
    xs[0][0]=xs[1][1]=1;
    cin>>m;
    while(m--){
        int op;
        cin>>op;
        mt zy;
        if(op==1){
            zy[0][0]=1;zy[0][1]=0;
            zy[1][0]=1;zy[1][1]=1;
        }
        else if(op==2){
            zy[0][0]=1;zy[0][1]=1;
            zy[1][0]=0;zy[1][1]=1;
        }
        else if(op==3){
            zy[0][0]=1;zy[0][1]=0;
            zy[1][0]=mod-1;zy[1][1]=1;
        }
        else{
            zy[0][0]=1;zy[0][1]=mod-1;
            zy[1][0]=0;zy[1][1]=1;
        }
        xs=zy*xs;
    }
    for(int k=1;k<(1<<n);k<<=1){
        for(int i=0;i<(1<<n);i+=(k<<1)){
            for(int j=0;j<k;++j){
                ll x=a[i+j],y=a[i+j+k];
                a[i+j]=(xs[0][0]*x+xs[0][1]*y)%mod;
                a[i+j+k]=(xs[1][0]*x+xs[1][1]*y)%mod;
            }
        }
    }
    for(int i=0;i<(1<<n);++i){
        cout<<a[i]<<' ';
    }
    return 0;
}