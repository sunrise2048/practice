#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using L=__uint128_t;
struct FastMod{
    ull b,m;
    FastMod(ull b):b(b),m(ull((L(1)<<64)/b)){}
    ull operator()(ull a){
        ull q=(ull)((L(m)*a)>>64);
        ull r=a-q*b;
        return r>=b?r-b:r;
    }
};
FastMod md(2);
const int N=2e4+5;
int n,mod;
int f[2][3][N];
int g[N<<1][2];
ll jc[N<<1],ny[N<<1];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=md(an*x);
        x=md(x*x);
        y>>=1;
    }
    return an;
}
ll A(int x,int y){return md(jc[x]*ny[x-y]);}
ll sum;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>mod;
    md=FastMod(mod);
    sum=1;
    for(int i=1;i<=(n<<1);i+=2){
        sum=md(sum*i);
    }
    jc[0]=1;
    for(int i=1;i<=(n<<1);++i)jc[i]=md(jc[i-1]*i);
    ny[n<<1]=ksm(jc[n<<1]);
    for(int i=(n<<1);i;--i)ny[i-1]=md(ny[i]*i);
    f[0][0][0]=1;
    for(int i=0;i<(n<<1);++i){
        const int lop=i&1,op=lop^1;
        memset(f[op],0,sizeof(f[op]));
        f[lop][0][0]=md(f[lop][0][0]+g[i][0]);
        f[lop][1][0]=md(f[lop][1][0]+g[i][1]);
        for(int j=0;j<=i&&j+i<=(n<<1);++j){
            if(f[lop][0][j]){
                f[op][2][j+1]=f[lop][0][j];
            }
            if(f[lop][1][j]){
                f[op][0][j]=f[lop][1][j];
                f[op][1][j+1]=f[lop][1][j];
            }
            if(f[lop][2][j]){
                g[i+j][0]=md(g[i+j][0]+A((n<<1)-i-1,j-1)*f[lop][2][j]);
                if(j>1){
                    g[i+j-1][1]=md(g[i+j-1][1]+f[lop][2][j]*md(A((n<<1)-i-1,j-2)*(j-1)));
                }
                f[op][2][j+1]=md(f[op][2][j+1]+f[lop][2][j]);
            }
        }
    }
    cout<<md(sum-md(f[0][0][0]+g[n<<1][0])+mod)<<'\n';
    return 0;
}