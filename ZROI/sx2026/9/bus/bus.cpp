#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,m;
vector<int> e[N];
class SGT{
public:
    struct node{
        ll sum;
        int mi,ma;
        int lson,rson;
    }t[N*20];
    int cn;
    #define mid (l+r>>1)
    #define rs(k) t[k].rson
    #define ls(k) t[k].lson
    void clear(){
        for(int i=1;i<=cn;++i){
            t[i].sum=t[i].mi=t[i].ma=ls(i)=rs(i)=0;
        }
        cn=0;
    }
    void pushup(int k){
        t[k].sum=t[ls(k)].sum+t[rs(k)].sum;
        if(ls(k)&&rs(k)){
            t[k].sum-=lca(t[ls(k)].mi,t[rs(k)].ma);
            t[k].mi=t[ls(k)].mi,t[k].ma=t[rs(k)].ma;
        }
        else if(ls(k)){
            t[k].mi=t[ls(k)].mi,t[k].ma=t[ls(k)].ma;
        }
        else t[k].mi=t[rs(k)].mi,t[k].ma=t[rs(k)].ma;
    }
    void update(int l,int r,int& k,int x){
        if(!k)k=++cn;
        if(l==r){
            t[k].sum=gd[nfd[x]];
            t[k].mi=t[k].ma=x;
            return;
        }
        if(x<=mid)update(l,mid,ls(k),x);
        else update(mid+1,r,rs(k),x);
        pushup(k);
    }
    ll qu(int x){
        return t[x].sum;
    }
    int merge(int l,int r,int k0,int k1){
        if(!k0||!k1)return k0|k1;
        if(l==r)return k0;
        ls(k0)=merge(l,mid,ls(k0),ls(k1));
        rs(k0)=merge(mid+1,r,rs(k0),rs(k1));
        pushup(k0);
        return k0;
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    freopen("bus1.in","r",stdin);
    freopen("bus.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    cin>>n>>m;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=m;++i){
        int x,y;
        cin>>x>>y;
    }
    for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
    return 0;
}