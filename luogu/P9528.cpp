#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const ll inf=1e16;
int n,L;
struct ope{
    int op,x,d;
}qs[N];
vector<int> lis;
ll sa;
class SGT{
public:
    struct node{
        ll v00,v01,v10,v11;
        node()=default;
        node(ll v00,ll v01,ll v10,ll v11):v00(v00),v01(v01),v10(v10),v11(v11){}
    }t[N<<2];
    ll lz1[N<<2],lz2[N<<2],lz3[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){
        t[k]=node(max({t[ls].v00,t[rs].v00,t[ls].v00+t[rs].v10,t[ls].v01+t[rs].v00}),max({t[ls].v01,t[rs].v01,t[ls].v00+t[rs].v11,t[ls].v01+t[rs].v01}),max({t[ls].v10,t[rs].v10,t[ls].v10+t[rs].v10,t[ls].v11+t[rs].v00}),max({t[ls].v11,t[rs].v11,t[ls].v10+t[rs].v11,t[ls].v11+t[rs].v01}));
    }
    void upd1(int k,ll d){
        t[k].v00+=d;
        lz1[k]+=d;
    }
    void upd2(int k,ll d){
        t[k].v11+=d;
        lz2[k]+=d;
    }
    void upd3(int k,ll d){
        t[k].v01+=d;
        lz3[k]+=d;
    }
    void pushdown(int k){
        if(lz1[k]){
            upd1(ls,lz1[k]);
            upd1(rs,lz1[k]);
            lz1[k]=0;
        }
        if(lz2[k]){
            upd2(ls,lz2[k]);
            upd2(rs,lz2[k]);
            lz2[k]=0;
        }
        if(lz3[k]){
            upd3(ls,lz3[k]);
            upd3(rs,lz3[k]);
            lz3[k]=0;
        }
    }
    void update(int l,int r,int k,int x,int y,const vector<ll>& d){
        if(x<=l&&r<=y){
            upd1(k,d[0]);upd2(k,d[1]);upd3(k,d[2]);
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x,y,d);
        if(y>mid)update(mid+1,r,rs,x,y,d);
        pushup(k);
    }
    ll query(){
        return t[1].v01;
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int get_id(int x){
    return lower_bound(lis.begin(),lis.end(),x)-lis.begin()+1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>L;
    for(int i=1;i<=n;++i){
        cin>>qs[i].op>>qs[i].x>>qs[i].d;
        if(qs[i].op==1)lis.push_back(qs[i].x);
    }
    sort(lis.begin(),lis.end());
    lis.erase(unique(lis.begin(),lis.end()),lis.end());
    int m=lis.size();
    for(int i=1;i<=n;++i){
        auto [op,x,d]=qs[i];
        if(op==1){
            sa+=d;
            int idx=get_id(x);
            sgt.update(1,m,1,idx,idx,{0,d,d});
            if(idx<m)sgt.update(1,m,1,idx+1,m,{-d,d,0});
        }
        else{
            int idl=get_id(x-L),idr=get_id(x+L+1)-1;
            int idx=idr+1;
            if(idl<=idr)sgt.update(1,m,1,idl,idr,{0,-d,-d});
            if(idx<=m)sgt.update(1,m,1,idx,m,{d,-d,0});
        }
        cout<<sa-sgt.query()<<'\n';
    }
    return 0;
}