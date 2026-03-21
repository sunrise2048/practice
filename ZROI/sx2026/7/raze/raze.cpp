#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod=998244353;
constexpr int N=1<<18;
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
    Poly operator + (const Poly& B)const{
        Poly C=B;
        C.f.resize(max(f.size(), B.f.size()));
        for(int i = 0; i < f.size(); ++i) {
            C.f[i] = (C.f[i] + f[i]) % mod;
        }
        return C;
    }
    Poly operator - (const Poly& B)const{
        Poly C=B;
        C.f.resize(max(f.size(), B.f.size()));
        for(int i = 0; i < f.size(); ++i) {
            C.f[i] = (f[i] - C.f[i] + mod) % mod;
        }
        for(int i=f.size();i<B.f.size();++i){
            C.f[i]=(mod-C.f[i])%mod;
        }
        return C;
    }
    Poly operator*(const ll& c)const{
        Poly C;
        C.f=f;
        for(int i=0;i<f.size();++i)C.f[i]=C.f[i]*c%mod;
        return C;
    }
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
    Poly operator * (const Poly& y) const{
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
ll Poly::A[N],Poly::B[N],Poly::C[N];
ll n;
int m;
ll jc[N],ny[N];
ll C(int x,int y){
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
ll calc_S(){
    ll s=1;
    for(int i=1;i<=2*m;++i)s=s*i%mod;
    s=ksm(s);
    for(int i=0;i<2*m;++i){
        s=(n-i)%mod*s%mod;
    }
    return s;
}
void calc_G(){
    G.f.resize(m+1);
    for(int i=0;i<=m;i+=2){
        G.f[i]=C(m,i);
    }
    Poly ls;
    ls.f.resize(m+2);
    for(int i=0;i<=m+1;++i){
        ls.f[i]=C(m+1,i);
    }
    G=G*ls;
}
int main(){
    Poly::init();
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    jc[0]=1;
    for(int i=1;i<=m+1;++i)jc[i]=jc[i-1]*i%mod;
    ny[m+1]=ksm(jc[m+1]);
    for(int i=m+1;i;--i)ny[i-1]=ny[i]*i%mod;
    calc_G();
    F.f.resize(1);
    F.f[0]=1;
    for(int i=0;i<60;++i){
        Poly tF=F*G;
        int op=0;
        if((n-2*m)&(1ll<<i))op=1;
        F.f.clear();
        for(int j=0;j<tF.f.size();++j){
            if((j&1)!=op)continue;
            F.f.push_back(tF.f[j]);
        }
    }
    cout<<(calc_S()-F.f[0]+mod)%mod<<'\n';
    return 0;
}