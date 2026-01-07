#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n,q;
int p[N],s[N];
int a[N];
class SGT{
public:
    struct node{
        int miv;
        int lm,rm;
        ll sum;
        int lz;
    }t[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){
        if(t[ls].miv<t[rs].miv){
            t[k].miv=t[ls].miv;
            t[k].lm=t[ls].lm;
            t[k].rm=t[ls].rm;
            t[k].sum=t[ls].sum;
            return;
        }
        if(t[ls].miv>t[rs].miv){
            t[k].miv=t[rs].miv;
            t[k].lm=t[rs].lm;
            t[k].rm=t[rs].rm;
            t[k].sum=t[rs].sum;
            return;
        }
        t[k].miv=t[ls].miv;
        t[k].lm=t[ls].lm;
        t[k].rm=t[rs].rm;
        t[k].sum=t[ls].sum+t[rs].sum-1ll*t[ls].rm*t[rs].lm;
    }
    void upd(int k,int d){
        t[k].miv+=d;
        t[k].lz+=d;
    }
    void pushdown(int k){
        if(!t[k].lz)return;
        upd(ls,t[k].lz);
        upd(rs,t[k].lz);
        t[k].lz=0;
    }
    void build(int l,int r,int k){
        t[k].lz=0;
        if(l==r){
            t[k].miv=l;
            t[k].lm=t[k].rm=l;
            t[k].sum=1ll*l*l;
            return;
        }
        build(l,mid,ls);
        build(mid+1,r,rs);
        pushup(k);
    }
    void update(int l,int r,int k,int x,int d){
        if(x<=l){
            upd(k,d);
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x,d);
        update(mid+1,r,rs,x,d);
        pushup(k);
    }
    ll query(){
        if(t[1].miv)return 0;
        return t[1].sum;
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;++i){
            cin>>p[i];
        }
        for(int i=1;i<=n;++i){
            cin>>s[i];
            a[p[i]]=s[i];
        }
        sgt.build(1,n,1);
        for(int i=1;i<=n;++i){
            sgt.update(1,n,1,max(a[i],i),-1);
        }
        while(q--){
            int op;
            int x,y;
            cin>>op>>x>>y;
            if(op==1){
                sgt.update(1,n,1,max(p[x],a[p[x]]),1);
                sgt.update(1,n,1,max(p[y],a[p[y]]),1);
                swap(a[p[x]],a[p[y]]);
                swap(p[x],p[y]);
                sgt.update(1,n,1,max(p[x],a[p[x]]),-1);
                sgt.update(1,n,1,max(p[y],a[p[y]]),-1);
            }
            else{
                sgt.update(1,n,1,max(p[x],a[p[x]]),1);
                sgt.update(1,n,1,max(p[y],a[p[y]]),1);
                swap(a[p[x]],a[p[y]]);
                swap(s[x],s[y]);
                sgt.update(1,n,1,max(p[x],a[p[x]]),-1);
                sgt.update(1,n,1,max(p[y],a[p[y]]),-1);
            }
            cout<<sgt.query()<<'\n';
        }
    }
    return 0;
}