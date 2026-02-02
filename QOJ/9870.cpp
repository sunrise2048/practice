#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod=998244353;
constexpr int N=1<<19;
ll ksm(ll x,ll y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int rev[N];
ll gp[N+1],gip[N+1];
ll iinv[N+1];
void bit_reverse(ll* f, int n){
    for(int i=1;i<n;++i){
        rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
        if(rev[i]<i)swap(f[i],f[rev[i]]);
    }
}
void NTT(ll* f,int n,int op){
    bit_reverse(f,n);
    for(int k=1;k<n;k<<=1){
        ll w=(op==1?gp[k<<1]:gip[k<<1]);
        for(int i=0;i<n;i+=(k<<1)){
            ll W=1;
            for(int j=0;j<k;++j){
                ll x=f[i+j],y=f[i+j+k]*W%mod;
                f[i+j]=(x+y)%mod;
                f[i+j+k]=(x-y+mod)%mod;
                W=W*w%mod;
            }
        }
    }
    if(op==-1){
        ll ny=iinv[n];
        for(int i=0;i<n;++i) {
            f[i]=f[i]*ny%mod;
        }
    }
}
class Poly{
public:
    static constexpr int g=3;
    static constexpr int gi=(mod+1)/g;
    vector<ll> f;
    static ll A[N],B[N],C[N];
    static void init(){
        memset(A,0,sizeof(A));memset(B,0,sizeof(B));memset(C,0,sizeof(C));
        for(int i = 1; i <= N; i <<= 1){
            gp[i] = ksm(g, (mod - 1) / i);
            gip[i] = ksm(gi, (mod - 1) / i);
        }
        iinv[0]=1;
        for(int i=1;i<=N;++i)iinv[i]=iinv[i-1]*i%mod;
        iinv[N]=ksm(iinv[N]);
        for(int i=N;i;--i){
            ll la=iinv[i-1];
            iinv[i-1]=iinv[i]*i%mod;
            iinv[i]=iinv[i]*la%mod;
        }
    }
    void cpy(ll* F)const{
        for(int i=0;i<f.size();++i)F[i]=f[i];
    }
    void clr(ll* f,int n)const{memset(f,0,sizeof(ll)*n);}
    Poly operator*(const Poly& y) const{
        cpy(A);y.cpy(B);
        int n=1,m=f.size()+y.f.size()-1;
        while(n<m)n<<=1;
        NTT(A,n,1);NTT(B,n,1);
        for(int i=0;i<n;++i)A[i]=A[i]*B[i]%mod;
        NTT(A,n,-1);
        Poly C;C.f.resize(m);
        for(int i=0;i<m;++i)C.f[i]=A[i];
        clr(A,n);clr(B,n);
        return C;
    }
}F,G;
int n;
ll m;
int a[N];
ll Poly::A[N],Poly::B[N],Poly::C[N];
Poly sol(Poly& x,Poly& y){
    Poly z=x*y;
    Poly as;
    as.f.resize(2*n+1);
    for(int i=-n;i<=n;++i){
        as.f[i+n]=z.f[i+2*n];
    }
    return as;
}
int main(){
    Poly::init();
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        F.f.clear();G.f.clear();
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            a[i]-=(m/n);
        }
        m-=(m/n)*n;
        F.f.resize(2*n+1);
        G.f.resize(2*n+1);
        G.f[n]=1;
        for(int i=1;i<=n;++i){
            F.f[a[i]+n]=1;
        }
        int t=n;
        while(t){
            if(t&1){
                G=sol(F,G);
            }
            F=sol(F,F);
            t>>=1;
        }
        if(G.f[m+n])cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}