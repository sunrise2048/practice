#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m,q;
vector<int> e[N];
int c[N];
int st[N],str;
int sd[N];
vector<pair<int,int>> qs[N];
int ans[N];
class BIT{
public:
    int t[N];
    void upd(int x,int d){
        while(x){
            t[x]+=d;
            x-=(x&-x);
        }
    }
    int qu(int x){
        int s=0;
        while(x<=m){
            s+=t[x];
            x+=(x&-x);
        }
        return s;
    }
}bit;
int si[N],d[N],fa[N];
int zs[N],top[N];
void dfs1(int no,int fa){
    ::fa[no]=fa;
    si[no]=1;
    d[no]=d[fa]+1;
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
        if(to==fa[no]||to==zs[no])continue;
        dfs2(to,to);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return d[x]<d[y]?x:y;
}
vector<pair<int,int>> ld[N];
void upd(int x,int c){
    bit.upd(c,d[x]);
    while(x){
        int tp=top[x];
        int td=d[x];
        int las=d[tp]-1;
        while(!ld[tp].empty()&&ld[tp].back().first<=td){
            auto [nd,co]=ld[tp].back();
            ld[tp].pop_back();
            bit.upd(co,-(nd-las));
            las=nd;
        }
        if(!ld[tp].empty()){
            auto [nd,co]=ld[tp].back();
            bit.upd(co,-(td-las));
        }
        ld[tp].emplace_back(td,c);
        x=fa[tp];
    }
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
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=m;++i){
        cin>>c[i];
    }
    for(int i=1;i<=q;++i){
        int l,r;
        cin>>l>>r;
        qs[r].emplace_back(l,i);
    }
    for(int r=1;r<=m;++r){
        if(r!=1){
            int nd=d[lca(c[r],c[r-1])];
            while(str&&sd[str]>=nd)--str;
            st[++str]=r;
            sd[str]=nd;
        }
        upd(c[r],r);
        for(auto [l,id]:qs[r]){
            int it;
            if(l==r)it=d[c[l]]-1;
            else it=sd[upper_bound(st+1,st+str+1,l)-st]-1;
            ans[id]=bit.qu(l)-it;
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}