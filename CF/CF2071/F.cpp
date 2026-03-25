#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
int a[N];
int lm;
class SGT{
public:
    int tl[N<<2],tr[N<<2],lz[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){
        tl[k]=tl[ls],tr[k]=tr[rs];
    }
    void upd(int k,int d){
        tl[k]+=d;tr[k]+=d;
        lz[k]+=d;
    }
    void pushdown(int k){
        if(!lz[k])return;
        upd(ls,lz[k]);upd(rs,lz[k]);
        lz[k]=0;
    }
    void clear(){
        memset(tl,0,sizeof(int)*(n<<2));
        memset(tr,0,sizeof(int)*(n<<2));
        memset(lz,0,sizeof(int)*(n<<2));
    }
    void update(int l,int r,int k,int x){
        if(x<=l){
            tl[k]++;tr[k]++;
            lz[k]++;
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x);
        update(mid+1,r,rs,x);
        pushup(k);
    }
    int query(int l,int r,int k,int d){
        if(l==r)return l;
        pushdown(k);
        if(lm-(mid-tr[ls]-1)<=d)return query(l,mid,ls,d);
        return query(mid+1,r,rs,d);
    }
    int qu(int l,int r,int k){
        if(l==r)return l;
        pushdown(k);
        if(tl[rs]>mid)return qu(mid+1,r,rs);
        return qu(l,mid,ls);
    }
    int gmi(){
        return lm-(n-tr[1]-1);
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int ps[N];
bool ch(int x){
    lm=x;
    sgt.clear();
    for(int i=1;i<=n;++i){
        ps[i]=0;
        if(a[i]<sgt.gmi())continue;
        int tm=sgt.query(1,n,1,a[i]);
        sgt.update(1,n,1,tm);
        if(a[i]>=x)ps[i]=sgt.qu(1,n,1);
    }
    sgt.clear();
    for(int i=n;i;--i){
        if(a[i]<sgt.gmi())continue;
        int tm=sgt.query(1,n,1,a[i]);
        sgt.update(1,n,1,tm);
        if(a[i]>=x){
            int len=ps[i]+sgt.qu(1,n,1)-1;
            if(len>=k)return 1;
        }
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        k=n-k;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        int l=0,r=1e9+1;
        while(l<r-1){
            int mid=l+r>>1;
            if(ch(mid))l=mid;
            else r=mid;
        }
        cout<<l<<'\n';
    }
    return 0;
}