#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
const int M=1e4+5;
int n,m,rt;
int fa[N];
int vis[N];
int sum;
class LT{
public:
    struct node{
        int s[2];
        int to,tw;
        int lz;
        int d;
    }t[M];
    void init(int id,int v,int w){
        t[id].d=1;
        t[id].to=v;
        t[id].tw=w;
    }
    void upd(int k,int d){
        if(!k)return;
        t[k].tw+=d;
        t[k].lz+=d;
    }
    void pushdown(int k){
        if(!t[k].lz)return;
        if(t[k].s[0])upd(t[k].s[0],t[k].lz);
        if(t[k].s[1])upd(t[k].s[1],t[k].lz);
        t[k].lz=0;
    }
    int merge(int x,int y){
        if(!x||!y)return x|y;
        if(t[x].tw>t[y].tw)swap(x,y);
        pushdown(x);
        t[x].s[1]=merge(t[x].s[1],y);
        if(t[t[x].s[1]].d>t[t[x].s[0]].d){
            swap(t[x].s[0],t[x].s[1]);
            t[x].d=t[t[x].s[0]].d+1;
        }
        return x;
    }
    int erase(int x){
        pushdown(x);
        return merge(t[x].s[0],t[x].s[1]);
    }
    pair<int,int> query(int x){
        return {t[x].to,t[x].tw};
    }
}lt;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int rte[N];
int pre[N],pw[N];
void dfs(int no){
    if(vis[no])return;
    vis[no]=1;
    if(no==rt){
        vis[no]=2;
        return;
    }
    auto [to,tw]=lt.query(rte[no]);
    to=find(to);
    rte[no]=lt.erase(rte[no]);
    while(to&&to==no){
        auto [tt,wt]=lt.query(rte[no]);
        rte[no]=lt.erase(rte[no]);
        swap(tt,to);swap(tw,wt);
        to=find(to);
    }
    if(!to){
        cout<<"-1\n";
        exit(0);
    }
    if(vis[to]!=1){
        pw[no]=tw;
        pre[no]=to;
        sum+=tw;
        dfs(to);
    }
    else{
        sum+=tw;
        lt.upd(rte[no],-tw);
        to=find(to);
        while(to!=no){
            vis[to]=2;
            lt.upd(rte[to],-pw[to]);
            fa[to]=no;
            rte[no]=lt.merge(rte[no],rte[to]);
            to=pre[to];
            to=find(to);
        }
        vis[no]=0;
        dfs(no);
    }
    vis[no]=2;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>rt;
    for(int i=1;i<=n;++i){
        fa[i]=i;
    }
    for(int i=1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        lt.init(i,u,w);
        rte[v]=lt.merge(rte[v],i);
    }
    for(int i=1;i<=n;++i){
        if(vis[i])continue;
        dfs(i);
    }
    cout<<sum<<'\n';
    return 0;
}