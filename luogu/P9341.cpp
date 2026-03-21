#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,m,q;
int s[N];
ll ss;
int mxs;
int fa[N];
struct edge{
    int u,v,w;
    edge()=default;
    edge(int u,int v,int w):u(u),v(v),w(w){}
}e[N<<1];
int cn;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
set<pair<int,int>> st[N];
ll sum;
ll ans[N];
set<pair<int,int>> sp;
int rt;
bool ch(int no){
    auto [tw,to]=*st[no].begin();
    if(find(to)==find(no)){
        sp.erase({tw-s[rt]-s[no],no});
        st[no].erase(st[no].begin());
        sp.emplace(st[no].begin()->first-s[rt]-s[no],no);
        return 0;
    }
    return 1;
}
void era(){
    int no=sp.begin()->second;
    while(!ch(no)){
        no=sp.begin()->second;
    }
    sp.erase(sp.begin());
    sum+=st[no].begin()->first-s[rt]-s[no];
    int to=st[no].begin()->second;
    to=find(to);
    fa[no]=to;
    if(to==rt)return;
    sp.erase({st[to].begin()->first-s[rt]-s[to],to});
    if(st[no].size()>st[to].size())swap(st[no],st[to]);
    for(auto [tw,tt]:st[no]){
        if(find(tt)==find(to))continue;
        st[to].emplace(tw,tt);
    }
    sp.emplace(st[to].begin()->first-s[rt]-s[to],to);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    rt=1;
    for(int i=1;i<=n;++i){
        cin>>s[i];
        if(s[i]<s[rt])rt=i;
        ss+=s[i];
        mxs=max(mxs,s[i]);
    }
    iota(fa+1,fa+n+1,1);
    for(int i=1;i<=m;++i){
        cin>>e[i].u>>e[i].v;
        e[i].w=s[e[i].u]+s[e[i].v];
    }
    sort(e+1,e+m+1,[](const edge& x,const edge& y){
        return x.w<y.w;
    });
    for(int i=1;i<=m;++i){
        if(find(e[i].u)==find(e[i].v))continue;
        e[++cn]=e[i];
    }
    m=cn;
    for(int i=1;i<=n;++i){
        if(i==rt)continue;
        sum+=s[rt]+s[i];
    }
    for(int i=1;i<=m;++i){
        auto [u,v,w]=e[i];
        if(u!=rt)st[u].emplace(w,v);
        if(v!=rt)st[v].emplace(w,u);
    }
    for(int i=1;i<=n;++i){
        if(i==rt)continue;
        sp.emplace(st[i].begin()->first-s[rt]-s[i],i);
    }
    for(int i=n-1;i<=q;++i)ans[i]=sum-ss+mxs;
    for(int i=n-2;i>=0;--i){
        era();
        ans[i]=sum-ss+mxs;
    }
    for(int i=0;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}