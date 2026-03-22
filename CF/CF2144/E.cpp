#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int mod=998244353;
const int ny2=(mod+1)/2;
int T;
int n;
int a[N];
ll mi[N],ni[N];
ll f[N],g[N];
vector<int> sl,sr;
int mx;
class SGT{
public:
    ll t[N<<2],lz[N<<2];
    void init(){
        memset(t,0,sizeof(ll)*(n<<2));
        fill(lz+1,lz+(n<<2)+1,1);
    }
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){t[k]=(t[ls]+t[rs])%mod;}
    void mul(int k,ll d){
        t[k]=t[k]*d%mod;
        lz[k]=lz[k]*d%mod;
    }
    void pushdown(int k){
        if(lz[k]==1)return;
        mul(ls,lz[k]);mul(rs,lz[k]);
        lz[k]=1;
    }
    void update(int l,int r,int k,int x,ll d){
        if(l==r){
            t[k]=(t[k]+d)%mod;
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x,d);
        else update(mid+1,r,rs,x,d);
        pushup(k);
    }
    void update_mul(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y){
            t[k]=t[k]*2%mod;
            lz[k]=lz[k]*2%mod;
            return;
        }
        pushdown(k);
        if(x<=mid)update_mul(l,mid,ls,x,y);
        if(y>mid)update_mul(mid+1,r,rs,x,y);
        pushup(k);
    }
    ll query(int l,int r,int k,int x){
        if(l==r)return t[k];
        pushdown(k);
        if(x<=mid)return query(l,mid,ls,x);
        return query(mid+1,r,rs,x);
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    mi[0]=ni[0]=1;
    for(int i=1;i<=300000;++i){
        mi[i]=mi[i-1]*2%mod;
        ni[i]=ni[i-1]*ny2%mod;
    }
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        sl.clear();sr.clear();
        sl.push_back(0);
        for(int i=1;i<=n;++i){
            if(a[i]>sl.back())sl.push_back(a[i]);
        }
        sr.push_back(0);
        for(int i=n;i;--i){
            if(a[i]>sr.back())sr.push_back(a[i]);
        }
        int lm=sl.size()-1;
        sgt.init();
        sgt.update(0,lm,1,0,1);
        for(int i=1;i<=n;++i){
            int it=lower_bound(sl.begin(),sl.end(),a[i])-sl.begin();
            if(sl[it]==a[i]){
                f[i]=sgt.query(0,lm,1,it-1);
            }
            if(it!=sl.size())sgt.update_mul(0,lm,1,it,lm);
            if(sl[it]==a[i])sgt.update(0,lm,1,it,f[i]);
        }
        sgt.init();
        lm=sr.size()-1;
        sgt.update(0,lm,1,0,1);
        for(int i=n;i;--i){
            int it=lower_bound(sr.begin(),sr.end(),a[i])-sr.begin();
            if(sr[it]==a[i]){
                g[i]=sgt.query(0,lm,1,it-1);
            }
            if(it!=sr.size())sgt.update_mul(0,lm,1,it,lm);
            if(sr[it]==a[i])sgt.update(0,lm,1,it,g[i]);
        }
        ll sum=0;
        mx=sl.back();
        for(int i=n;i;--i){
            if(a[i]==mx)sum=(sum+mi[i-1]*g[i])%mod;
        }
        ll ans=0;
        for(int i=1;i<=n;++i){
            if(a[i]!=mx)continue;
            sum=(sum-mi[i-1]*g[i]%mod+mod)%mod;
            ans=(ans+f[i]*ni[i]%mod*sum+f[i]*g[i])%mod;
        }
        cout<<ans<<'\n';
    }
    return 0;
}