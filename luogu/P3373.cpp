#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=571373;
int n,q;
int a[N];
class SGT{
public:
    struct node{
        ll sum;
        ll lz_add,lz_mul=1;
    }t[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){
        t[k].sum=(t[ls].sum+t[rs].sum)%mod;
    }
    void upd_add(int l,int r,int k,ll d){
        t[k].sum=(t[k].sum+(r-l+1)*d)%mod;
        t[k].lz_add=(t[k].lz_add+d)%mod;
    }
    void upd_mul(int k,ll d){
        t[k].sum=t[k].sum*d%mod;
        t[k].lz_add=t[k].lz_add*d%mod;
        t[k].lz_mul=t[k].lz_mul*d%mod;
    }
    void pushdown(int l,int r,int k){
        if(t[k].lz_mul!=1){
            upd_mul(ls,t[k].lz_mul);
            upd_mul(rs,t[k].lz_mul);
            t[k].lz_mul=1;
        }
        if(t[k].lz_add){
            upd_add(l,mid,ls,t[k].lz_add);
            upd_add(mid+1,r,rs,t[k].lz_add);
            t[k].lz_add=0;
        }
    }
    void build(int l,int r,int k){
        if(l==r){
            t[k].sum=a[l];
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        pushup(k);
    }
    void update_add(int l,int r,int k,int x,int y,ll d){
        if(x<=l&&r<=y){
            upd_add(l,r,k,d);
            return;
        }
        pushdown(l,r,k);
        if(x<=mid)update_add(l,mid,ls,x,y,d);
        if(y>mid)update_add(mid+1,r,rs,x,y,d);
        pushup(k);
    }
    void update_mul(int l,int r,int k,int x,int y,ll d){
        if(x<=l&&r<=y){
            upd_mul(k,d);
            return;
        }
        pushdown(l,r,k);
        if(x<=mid)update_mul(l,mid,ls,x,y,d);
        if(y>mid)update_mul(mid+1,r,rs,x,y,d);
        pushup(k);
    }
    ll query(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y)return t[k].sum;
        pushdown(l,r,k);
        if(y<=mid)return query(l,mid,ls,x,y);
        if(x>mid)return query(mid+1,r,rs,x,y);
        return (query(l,mid,ls,x,y)+query(mid+1,r,rs,x,y))%mod;
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q>>a[1];
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    sgt.build(1,n,1);
    while(q--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            ll d;
            cin>>d;
            sgt.update_mul(1,n,1,x,y,d);
        }
        else if(op==2){
            ll d;
            cin>>d;
            sgt.update_add(1,n,1,x,y,d);
        }
        else{
            cout<<sgt.query(1,n,1,x,y)<<'\n';
        }
    }
    return 0;
}