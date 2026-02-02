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
    void read(int n){
        f.resize(n);
        for(int i=0;i<n;++i){
            cin>>f[i];
        }
    }
    static ll A[N],B[N],C[N];
    static void init(){
        memset(A,0,sizeof(A));memset(B,0,sizeof(B));memset(C,0,sizeof(C));
        for(int i = 1; i <= N; i <<= 1){
            gp[i]=ksm(g,(mod-1)/i);
            gip[i]=ksm(gi,(mod-1)/i);
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
    Poly operator*(const Poly& y)const{
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
};
ll Poly::A[N],Poly::B[N],Poly::C[N];
int n,k;
ll jc[N],ny[N];
ll f[N];
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
ll calc1(int x){
    ll x0=(x+1)/2;
    ll x1=x/2;
    return (x0*(x0-1)/2+x1*(x1-1)/2)%mod*jc[n-1]%mod*(ny[x]*jc[x-1]%mod)%mod;
}
ll calc2(int x){
    ll x0=(x+1)/2;
    ll x1=x/2;
    return (x0*(x0-1)/2+x1*(x1-1)/2)%mod*jc[n]%mod*(ny[x]*jc[x-1]%mod)%mod;
}
Poly A,B,a,b;
void solve(int l,int r){
    if(l>=r)return;
    const int mid=l+r>>1;
    a.f.resize(mid-l+1);
    for(int i=l;i<=mid;++i){
        a.f[i-l]=A.f[i];
    }
    b.f.resize(r-mid);
    for(int i=mid+1;i<=r;++i){
        b.f[i-mid-1]=B.f[i];
    }
    a=a*b;
    int nx=l+mid+1;
    for(int i=0;i<a.f.size();++i){
        if(!a.f[i])continue;
        f[i+nx+1]=(f[i+nx+1]+a.f[i])%mod;
    }
    solve(l,mid);solve(mid+1,r);
}
ll g[N];
int main(){
    Poly::init();
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
    A.f.resize(n);
    for(int i=0;i<n;++i){
        A.f[i]=C(k-1,i)*i%mod;
    }
    B.f.resize(n);
    for(int i=0;i<n;++i){
        B.f[i]=C(n-k,i);
    }
    solve(0,n-1);
    for(int i=0;i<n;++i){
        A.f[i]=C(n-k,i)*i%mod;
        B.f[i]=C(k-1,i);
    }
    solve(0,n-1);
    for(int i=1;i<=n;++i){
        if(i&1){
            f[i]=(f[i]+C(k-1,i/2)*C(n-k,i/2)%mod*(i/2))%mod;
        }
        f[i]=f[i]*jc[i-1]%mod*jc[n-i]%mod;
    }
    for(int i=1;i<=n;++i){
        g[i]=calc2(i);
    }
    ll sum=0;
    for(int i=n;i;--i){
        g[i]=(g[i]-f[i]-calc1(i)*(n-i)%mod+2*mod)%mod;
        g[i]=g[i]*(ny[i-1]*(i>=2?jc[i-2]:1)%mod)%mod;
        sum=(sum+g[i])%mod;
    }
    for(int i=1;i<=n;++i){
        cout<<(sum+f[i])%mod<<'\n';
        sum=(sum+calc1(i)-g[i+1]+mod)%mod;
    }
    return 0;
}