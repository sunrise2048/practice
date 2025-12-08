#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=1e9+7;
int n;
ll pmi,pma;
ll inv_mi,inv_ma;
int a[N];
int id[N];
ll ans;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll st[N<<2],vl[N<<2],lz[N<<2];
ll mi[N];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void pushup(int k){
    st[k]=(st[ls]+st[rs])%mod;
}
void pushdown(int k){
    if(lz[k]==1)return;
    st[ls]=st[ls]*lz[k]%mod;
    vl[ls]=vl[ls]*lz[k]%mod;
    lz[ls]=lz[ls]*lz[k]%mod;
    st[rs]=st[rs]*lz[k]%mod;
    vl[rs]=vl[rs]*lz[k]%mod;
    lz[rs]=lz[rs]*lz[k]%mod;
    lz[k]=1;
}
void build(int l,int r,int k){
    lz[k]=1;
    if(l==r){
        vl[k]=mi[n-r];
        st[k]=vl[k];
        if(l!=1)st[k]=st[k]*pma%mod;
        return;
    }
    build(l,mid,ls);
    build(mid+1,r,rs);
    pushup(k);
}
void update(int l,int r,int k,int x,int y,ll d){
    if(x<=l&&r<=y){
        vl[k]=vl[k]*d%mod;
        st[k]=st[k]*d%mod;
        lz[k]=lz[k]*d%mod;
        return;
    }
    pushdown(k);
    if(x<=mid)update(l,mid,ls,x,y,d);
    if(y>mid)update(mid+1,r,rs,x,y,d);
    pushup(k);
}
void upd(int l,int r,int k,int x){
    if(l==r){
        st[k]=0;
        return;
    }
    pushdown(k);
    if(x<=mid)upd(l,mid,ls,x);
    else upd(mid+1,r,rs,x);
    pushup(k);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>pmi;
    pmi=ksm(100)*pmi%mod;
    pma=(1-pmi+mod)%mod;
    inv_ma=ksm(pma);
    inv_mi=ksm(pmi);
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    if(n==1){
        cout<<a[1]<<'\n';
        return 0;
    }
    iota(id+1,id+n+1,1);
    sort(id+1,id+n+1,[](const int& x,const int& y){
        return a[x]<a[y];
    });
    if(pmi==0){
        cout<<a[id[n]]<<'\n';
        return 0;
    }
    if(pma==0){
        cout<<a[id[1]]<<'\n';
        return 0;
    }
    mi[0]=1;
    for(int i=1;i<=n;++i){
        mi[i]=mi[i-1]*pmi%mod;
    }
    build(1,n,1);
    for(int i=0;i<n;++i){
        if(i){
            upd(1,n,1,id[i]);
            if(id[i]!=1)update(1,n,1,1,id[i]-1,pma*inv_mi%mod);
        }
        ans=(ans+st[1]*(a[id[i+1]]-a[id[i]]))%mod;
    }
    cout<<ans<<'\n';
    return 0;
}