#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,k;
int c[N];
vector<int> e[N];
vector<int> id[N];
bool vis[N];
bool fl[N];
bool nv[N];
bool cv[N];
int ans;
int si[N],nn;
int rt;
int mxs[N];
int fa[N];
void findrt(int no,int fa){
    ::fa[no]=fa;
    si[no]=1;
    mxs[no]=0;
    for(int to:e[no]){
        if(to==fa)continue;
        if(vis[to])continue;
        findrt(to,no);
        mxs[no]=max(mxs[no],si[to]);
        si[no]+=si[to];
    }
    mxs[no]=max(mxs[no],nn-si[no]);
    if(mxs[rt]>mxs[no])rt=no;
}
void dfs_fl(int no,int fa){
    fl[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        if(vis[to])continue;
        dfs_fl(to,no);
    }
}
void dfs_nv(int no,int fa){
    nv[no]=0;
    cv[c[no]]=0;
    fl[no]=0;
    for(int to:e[no]){
        if(to==fa)continue;
        if(vis[to])continue;
        dfs_nv(to,no);
    }
}
int cn;
void solve(int no){
    vis[no]=1;
    dfs_fl(no,0);
    cn=0;
    queue<int> q;
    q.push(c[no]);
    cv[c[no]]=1;
    while(!q.empty()){
        int nc=q.front();
        q.pop();
        for(int no:id[nc]){
            if(!fl[no]){
                cn=n+1;
                break;
            }
            while(!nv[no]&&no){
                nv[no]=1;
                if(!cv[c[no]]){
                    cv[c[no]]=1;
                    ++cn;
                    q.push(c[no]);
                }
                no=fa[no];
            }
        }
        if(cn>n)break;
    }
    ans=min(ans,cn);
    dfs_nv(no,0);
    for(int to:e[no]){
        if(vis[to])continue;
        nn=si[to];
        rt=0;
        findrt(to,0);
        findrt(rt,0);
        solve(rt);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    ans=n;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;++i){
        cin>>c[i];
        id[c[i]].push_back(i);
    }
    nn=n;
    mxs[0]=n;
    findrt(1,0);
    findrt(rt,0);
    solve(rt);
    cout<<ans<<'\n';
    return 0;
}