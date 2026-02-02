#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
vector<int> e[N];
int si[N];
int d[N];
int top[N],zs[N],fa[N];
void dfs(int no,int fa){
    ::fa[no]=fa;
    si[no]=1;
    zs[no]=0;
    d[no]=d[fa]+1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        si[no]+=si[to];
        if(si[to]>si[zs[no]])zs[no]=to;
    }
}
int rt;
void dfs1(int no,int tp){
    top[no]=tp;
    if(!zs[no])return;
    dfs1(zs[no],tp);
    for(int to:e[no]){
        if(to==fa[no]||to==zs[no])continue;
        dfs1(to,to);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return d[x]<d[y]?x:y;
}
int dis(int x,int y){
    return d[x]+d[y]-2*d[lca(x,y)]+1;
}
int id[N];
int ans[N];
pair<int,int> z;
int nd;
void add(int no){
    int td;
    if((td=dis(no,z.first))>nd){
        nd=td;
        z.second=no;
    }
    else if((td=dis(no,z.second))>nd){
        nd=td;
        z.first=no;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i){
        int mxs=n-si[i];
        for(int j:e[i]){
            if(j==fa[i])continue;
            mxs=max(mxs,si[j]);
        }
        if(mxs<=n/2){
            rt=i;
        }
    }
    dfs(rt,0);
    dfs1(rt,rt);
    iota(id+1,id+n+1,1);
    sort(id+1,id+n+1,[](const int& x,const int& y){
        return si[x]>si[y];
    });
    z={rt,rt};
    int id0=1;
    int mxd=0;
    for(int i=n;i>=1;--i){
        if(i&1){
            ans[i]=1;
            continue;
        }
        int ns=i/2;
        while(id0<=n&&si[id[id0]]>=ns){
            add(id[id0]);
            mxd=max(mxd,d[id[id0]]);
            ++id0;
        }
        ans[i]=max(mxd,nd);
    }
    for(int i=1;i<=n;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}