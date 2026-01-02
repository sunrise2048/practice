#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int d,mod;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int id0=5000,id1=4998;
int cn=2;
int add(int x,int y){
    if(x==5000)return y;
    if(y==5000)return x;
    int no=++cn;
    cout<<"+ "<<x<<' '<<y<<' '<<no<<'\n';
    return no;
}
int mul(int x,int bs){
    if(bs==0)return id0;
    if(bs==1)return x;
    int nb=++cn;
    cout<<"+ "<<x<<' '<<id0<<' '<<nb<<'\n';
    int no=++cn;
    cout<<"+ "<<id0<<' '<<id0<<' '<<no<<'\n';
    for(int i=0;(1<<i)<=bs;++i){
        if(bs&(1<<i)){
            cout<<"+ "<<nb<<' '<<no<<' '<<no<<'\n';
        }
        cout<<"+ "<<nb<<' '<<nb<<' '<<nb<<'\n';
    }
    return no;
}
const int N=15;
ll f[N][N];
ll xs[N][N];
ll C[N][N];
ll mi[N][N];
int id[N];
int gpow(int x){
    int no=++cn;
    cout<<"^ "<<x<<' '<<no<<'\n';
    return no;
}
int pow2(int x){
    int no=id0;
    for(int i=0;i<=d;++i){
        if(!xs[2][i])continue;
        int y=add(x,id[i]);
        no=add(no,mul(gpow(y),xs[2][i]));
    }
    return no;
}
int dec(int x,int y){
    int ny=mul(y,mod-1);
    return add(x,ny);
}
int main(){
    cin>>d>>mod;
    for(int i=0;(1<<i)<=mod-1;++i){
        if((mod-1)&(1<<i)){
            cout<<"+ "<<id0-1<<' '<<id0<<' '<<id0<<'\n';
        }
        cout<<"+ "<<id0-1<<' '<<id0-1<<' '<<id0-1<<'\n';
    }
    C[0][0]=1;
    for(int i=1;i<=d;++i){
        C[i][0]=1;
        for(int j=1;j<=i;++j){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    mi[0][0]=1;
    for(int i=1;i<=d;++i){
        mi[i][0]=1;
        for(int j=1;j<=d;++j){
            mi[i][j]=mi[i][j-1]*i%mod;
        }
    }
    for(int i=0;i<=d;++i){
        for(int j=0;j<=d;++j){
            f[i][j]=C[d][j]*mi[i][d-j]%mod;
        }
        xs[i][i]=1;
    }
    for(int i=0;i<=d;++i){
        if(!f[i][i]){
            for(int j=i+1;j<=d;++j){
                if(f[j][i]){
                    for(int k=0;k<=d;++k){
                        swap(f[i][k],f[j][k]);
                        swap(xs[i][k],xs[j][k]);
                    }
                    break;
                }
            }
        }
        ll bs=ksm(f[i][i]);
        for(int j=0;j<=d;++j){
            f[i][j]=f[i][j]*bs%mod;
            xs[i][j]=xs[i][j]*bs%mod;
        }
        for(int j=0;j<=d;++j){
            if(i==j)continue;
            bs=f[j][i];
            for(int k=0;k<=d;++k){
                f[j][k]=(f[j][k]-f[i][k]*bs%mod+mod)%mod;
                xs[j][k]=(xs[j][k]-xs[i][k]*bs%mod+mod)%mod;
            }
        }
    }
    id[0]=id0;
    id[1]=id1;
    for(int i=2;i<=d;++i){
        id[i]=add(id[i-1],id1);
    }
    int ans=mul(dec(dec(pow2(add(1,2)),pow2(1)),pow2(2)),ksm(2));
    cout<<"f "<<ans<<'\n';
    return 0;
}