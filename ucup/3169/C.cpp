#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
const int mod=998244353;
int n;
ll a[N];
ll ny[N*N];
ll jc[N*N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll C(ll x,int y){
    if(x<y)return 0;
    if(x<=n*n)return jc[x]*ny[y]%mod*ny[x-y]%mod;
    ll an=ny[y];
    for(int i=0;i<y;++i){
        an=(x-i)%mod*an%mod;
    }
    return an;
}
ll get_g(ll s,int n){
    return C(s+n-1,n-1);
}
ll get_f(int s,int n,int d){
    if(s<0)return 0;
    if(n==0)return s==0;
    ll an=0;
    for(int i=0;i*d<=s;++i){
        an=(an+(1+mod-2*(i&1))*C(n,i)%mod*get_g(s-i*d,n))%mod;
    }
    return an;
}
ll f[N][N],s[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    ll as=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        as+=a[i];
    }
    jc[0]=1;
    for(int i=1;i<=n*n;++i){
        jc[i]=jc[i-1]*i%mod;
    }
    ny[n*n]=ksm(jc[n*n]);
    for(int i=n*n;i;--i)ny[i-1]=ny[i]*i%mod;
    ll sum=get_g(as,n+1);
    if(as>=n*n){
        cout<<sum<<'\n';
        return 0;
    }
    sort(a+1,a+n+1);
    f[0][0]=1;
    for(int i=1;i<=n;++i){
        memset(s,0,sizeof(s));
        for(int j=0;j<=n;++j){
            s[j]=f[i-1][j];
            if(j)s[j]=(s[j]+s[j-1])%mod;
        }
        for(int j=0;j<=n;++j){
            f[i][j]=s[j];
            if(j>a[i])f[i][j]=(f[i][j]-s[j-a[i]-1]+mod)%mod;
        }
    }
    for(int d=0;d<n;++d){
        ll ns=get_f(as-d,n,n-d);
        int it=lower_bound(a+1,a+n+1,n-d)-a;
        ll sa=0;
        for(int i=it;i<=n;++i)sa+=a[i]-(n-d)+1;
        for(int d0=0;d0<=d;++d0){
            ns=(ns-f[it-1][d0]*get_f(d-sa-d0,n-it+1,n-d)%mod+mod)%mod;
        }
        sum=(sum-ns+mod)%mod;
    }
    cout<<sum<<'\n';
    return 0;
}