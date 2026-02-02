#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int lm=1e9;
int n,m,q;
vector<int> e[N];
pair<int,int> ee[N];
vector<int> ad[N];
class SGT{
public:
    struct node{
        int cn;
        ll sum;
        int lson,rson;
    }t[N*31];
    int cn;
    #define mid (l+r>>1)
    #define ls(k) t[k].lson
    #define rs(k) t[k].rson
    void update(int l,int r,int& k,int k0,int x){
        k=++cn;
        t[k]=t[k0];
        t[k].cn++;t[k].sum+=x;
        if(l==r)return;
        if(x<=mid)update(l,mid,ls(k),ls(k0),x);
        else update(mid+1,r,rs(k),rs(k0),x);
    }
    int query(int l,int r,int kx,int ky,int kl,ll& d){
        if(d<l)return 0;
        if(t[kx].sum+t[ky].sum-2*t[kl].sum<=d){
            d-=t[kx].sum+t[ky].sum-2*t[kl].sum;
            return t[kx].cn+t[ky].cn-2*t[kl].cn;
        }
        if(l==r){
            ll nc=d/l;
            d-=nc*l;
            return nc;
        }
        int nc=query(l,mid,ls(kx),ls(ky),ls(kl),d);
        return nc+query(mid+1,r,rs(kx),rs(ky),rs(kl),d);
    }
    int query(int rtx,int rty,int rtl,ll d){
        return t[rtx].cn+t[rty].cn-2*t[rtl].cn-query(1,lm,rtx,rty,rtl,d);
    }
    #undef mid
    #undef ls
    #undef rs
}sgt;
int fa[N],d[N],si[N];
int zs[N],top[N];
int rt[N];
void dfs1(int no,int fa){
    ::fa[no]=fa;
    d[no]=d[fa]+1;
    si[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs1(to,no);
        si[no]+=si[to];
        if(si[to]>si[zs[no]])zs[no]=to;
    }
}
void dfs2(int no,int tp){
    top[no]=tp;
    if(!zs[no])return;
    dfs2(zs[no],tp);
    for(int to:e[no]){
        if(to==zs[no]||to==fa[no])continue;
        dfs2(to,to);
    }
}
void dfs(int no,int fa){
    rt[no]=rt[fa];
    for(int d:ad[no])sgt.update(1,lm,rt[no],rt[no],d);
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return d[x]<d[y]?x:y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
        ee[i]={u,v};
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<n;++i){
        if(d[ee[i].first]<d[ee[i].second])swap(ee[i].first,ee[i].second);
    }
    for(int i=1;i<=m;++i){
        int x,d;
        cin>>x>>d;
        ad[ee[x].first].push_back(d);
    }
    dfs(1,0);
    while(q--){
        int s,t,x;
        ll y;
        cin>>s>>t>>x>>y;
        int lc=lca(s,t);
        x-=sgt.query(rt[s],rt[t],rt[lc],y);
        if(x<0)x=-1;
        cout<<x<<'\n';
    }
    return 0;
}