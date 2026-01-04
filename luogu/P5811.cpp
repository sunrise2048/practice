#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m;
int id[3];
int cn[3];
vector<int> e[N];
vector<int> te[N];
bool vis[N];
int si[N];
int mxs[N];
int rt;
int fa[N];
void find_te(int no){
    vis[no]=1;
    si[no]=1;
    for(int to:e[no]){
        if(vis[to])continue;
        te[no].push_back(to);
        te[to].push_back(no);
        fa[to]=no;
        find_te(to);
        si[no]+=si[to];
        mxs[no]=max(mxs[no],si[to]);
    }
    mxs[no]=max(mxs[no],n-si[no]);
    if(mxs[rt]>mxs[no])rt=no;
}
int fl[N];
int ans[N];
void dfs_vis(int no){
    vis[no]=1;
    for(int to:te[no]){
        if(to==rt)continue;
        if(vis[to])continue;
        dfs_vis(to);
    }
}
void dfs_fl(int no){
    fl[no]=1;
    for(int to:e[no]){
        if(to==rt)continue;
        if(fl[to])continue;
        dfs_fl(to);
    }
}
void find_lt(int no,int cn,int c){
    queue<int> q;
    q.push(no);
    --cn;
    fl[no]=1;
    while(!q.empty()){
        int no=q.front();
        ans[no]=c;
        q.pop();
        for(int to:e[no]){
            if(!cn)break;
            if(!vis[to]||fl[to])continue;
            q.push(to);
            fl[to]=1;
            --cn;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    cin>>cn[0]>>cn[1]>>cn[2];
    id[0]=0,id[1]=1,id[2]=2;
    sort(id,id+3,[](const int& x,const int& y){
        return cn[x]<cn[y];
    });
    sort(cn,cn+3);
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        ++u;++v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    mxs[0]=n;
    find_te(1);
    si[fa[rt]]=n-si[rt];
    int mz=fa[rt];
    for(int no:te[rt]){
        if(si[mz]<si[no])mz=no;
    }
    memset(vis,0,sizeof(vis));
    if(si[mz]>=cn[0]){
        dfs_vis(mz);
        find_lt(mz,cn[0],id[0]+1);
        fill(vis+1,vis+n+1,1);
        find_lt(rt,cn[1],id[1]+1);
        for(int i=1;i<=n;++i){
            if(!ans[i])ans[i]=id[2]+1;
            cout<<ans[i]<<' ';
        }
        return 0;
    }
    dfs_fl(fa[rt]);
    int ns=si[fa[rt]];
    fl[fa[rt]]=2;
    for(int to:te[rt]){
        if(to==fa[rt])continue;
        if(!fl[to])continue;
        ns+=si[to];
        fl[to]=2;
        if(ns>=cn[0])break;
    }
    if(ns<cn[0]){
        for(int i=1;i<=n;++i)cout<<"0 ";
        return 0;
    }
    for(int to:te[rt]){
        if(fl[to]!=2)continue;
        dfs_vis(to);
    }
    memset(fl,0,sizeof(fl));
    find_lt(fa[rt],cn[0],id[0]+1);
    fill(vis+1,vis+n+1,1);
    find_lt(rt,cn[1],id[1]+1);
    for(int i=1;i<=n;++i){
        if(!ans[i])ans[i]=id[2]+1;
        cout<<ans[i]<<' ';
    }
    return 0;
}