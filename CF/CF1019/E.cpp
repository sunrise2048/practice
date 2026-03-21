#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1.2e5+5;
int n,q;
int a[N];
class SGT{
public:
    int t[N<<2],lz[N<<2];
    ll ts[N<<2],tc[N<<2];
    int t_fl[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void upd_val(int k,int d){
        t[k]+=d;
        lz[k]+=d;
    }
    void upd_ad(int k,ll d){
        ts[k]+=d*t_fl[k];
        tc[k]+=d;
    }
    void pushdown(int k){
        if(lz[k]){
            upd_val(ls,lz[k]);upd_val(rs,lz[k]);
            lz[k]=0;
        }
        if(tc[k]){
            if(t[k]==t[ls])upd_ad(ls,tc[k]);
            if(t[k]==t[rs])upd_ad(rs,tc[k]);
            tc[k]=0;
        }
    }
    void pushup(int k){
        t[k]=min(t[ls],t[rs]);
        ts[k]=ts[ls]+ts[rs];
        t_fl[k]=(t[k]==t[ls])*t_fl[ls]+(t[k]==t[rs])*t_fl[rs];
    }
    void build(int l,int r,int k){
        if(l==r){
            t_fl[k]=1;
            t[k]=n;
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        pushup(k);
    }
    void update_val(int l,int r,int k,int x,int y,int d){
        if(x<=l&&r<=y){
            upd_val(k,d);
            return;
        }
        pushdown(k);
        if(x<=mid)update_val(l,mid,ls,x,y,d);
        if(y>mid)update_val(mid+1,r,rs,x,y,d);
        pushup(k);
    }
    ll query(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y)return ts[k];
        pushdown(k);
        if(y<=mid)return query(l,mid,ls,x,y);
        if(x>mid)return query(mid+1,r,rs,x,y);
        return query(l,mid,ls,x,y)+query(mid+1,r,rs,x,y);
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
stack<int> st_mi,st_ma;
ll ans[N];
vector<pair<int,int>> qs[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    sgt.build(1,n,1);
    cin>>q;
    for(int i=1;i<=q;++i){
        int l,r;
        cin>>l>>r;
        qs[r].emplace_back(l,i);
    }
    for(int i=1;i<=n;++i){
        sgt.update_val(1,n,1,i,i,-n);
        if(i!=1)sgt.update_val(1,n,1,1,i-1,-1);
        while(!st_mi.empty()&&a[st_mi.top()]>a[i]){
            int no=st_mi.top();st_mi.pop();
            int la=(st_mi.empty()?1:st_mi.top()+1);
            sgt.update_val(1,n,1,la,no,a[no]);
        }
        sgt.update_val(1,n,1,(st_mi.empty()?1:st_mi.top()+1),i,-a[i]);
        st_mi.push(i);
        while(!st_ma.empty()&&a[st_ma.top()]<a[i]){
            int no=st_ma.top();st_ma.pop();
            int la=(st_ma.empty()?1:st_ma.top()+1);
            sgt.update_val(1,n,1,la,no,-a[no]);
        }
        sgt.update_val(1,n,1,(st_ma.empty()?1:st_ma.top()+1),i,a[i]);
        st_ma.push(i);
        if(sgt.t[1]==0)sgt.upd_ad(1,1);
        for(auto [l,id]:qs[i]){
            ans[id]=sgt.query(1,n,1,l,i);
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}