#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
const int N=3e5+5;
int n,q;
int a[N];
ull vl[N];
vector<int> e[N];
int dfn[N],si[N];
int d[N];
int zs[N],top[N];
int fa[N];
vector<int> at[N];
mt19937_64 mt(time(0));
class SGT{
public:
    struct node{
        ull s;
        int lson,rson;
    }t[N*40];
    int cn;
    #define mid (l+r>>1)
    #define ls(k) t[k].lson
    #define rs(k) t[k].rson
    void update(int l,int r,int k0,int& k,int x,ull d){
        k=++cn;
        t[k]=t[k0];
        t[k].s^=d;
        if(l==r)return;
        if(x<=mid)update(l,mid,ls(k0),ls(k),x,d);
        else update(mid+1,r,rs(k0),rs(k),x,d);
    }
    int query(int l,int r,int k0,int k1,int k2,int k3,int x,int y){
        if((t[k0].s^t[k1].s^t[k2].s^t[k3].s)==0)return -1;
        if(x<=l&&r<=y){
            if(l==r)return l;
            if((t[ls(k0)].s^t[ls(k1)].s^t[ls(k2)].s^t[ls(k3)].s))return query(l,mid,ls(k0),ls(k1),ls(k2),ls(k3),x,y);
            return query(mid+1,r,rs(k0),rs(k1),rs(k2),rs(k3),x,y);
        }
        if(y<=mid)return query(l,mid,ls(k0),ls(k1),ls(k2),ls(k3),x,y);
        if(x>mid)return query(mid+1,r,rs(k0),rs(k1),rs(k2),rs(k3),x,y);
        int as=query(l,mid,ls(k0),ls(k1),ls(k2),ls(k3),x,y);
        if(as==-1)as=query(mid+1,r,rs(k0),rs(k1),rs(k2),rs(k3),x,y);
        return as;
    }
    #undef mid
    #undef ls
    #undef rs
}sgt;
int rt[N];
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
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        vl[i]=mt();
        cin>>a[i];
    }
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    {
        int cn=0;
        auto dfs=[&](int no,int fa,auto&& dfs)->void {
            si[no]=1;
            d[no]=d[fa]+1;
            dfn[no]=++cn;
            ::fa[no]=fa;
            for(int to:e[no]){
                if(to==fa)continue;
                dfs(to,no,dfs);
                si[no]+=si[to];
                if(si[to]>si[zs[no]])zs[no]=to;
            }
        };
        dfs(1,0,dfs);
        auto dfs2=[&](int no,int tp,auto&& dfs2)->void {
            top[no]=tp;
            if(!zs[no])return;
            dfs2(zs[no],tp,dfs2);
            for(int to:e[no]){
                if(to==fa[no]||to==zs[no])continue;
                dfs2(to,to,dfs2);
            }
        };
        dfs2(1,1,dfs2);
        for(int i=1;i<=n;++i){
            at[dfn[i]].push_back(a[i]);
            at[dfn[i]+si[i]].push_back(a[i]);
        }
    }
    for(int i=1;i<=n;++i){
        rt[i]=rt[i-1];
        for(int no:at[i])sgt.update(1,n,rt[i],rt[i],no,vl[no]);
    }
    while(q--){
        int x,y,l,r;
        cin>>x>>y>>l>>r;
        int lc=lca(x,y),lc1=fa[lc];
        cout<<sgt.query(1,n,rt[dfn[x]],rt[dfn[y]],rt[dfn[lc]],rt[dfn[lc1]],l,r)<<'\n';
    }
    return 0;
}