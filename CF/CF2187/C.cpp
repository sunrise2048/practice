#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m;
int fa[N];
vector<int> hs[N];
int si[N];
int mxd[N],d[N],zs[N];
vector<int> te[N];
int sid[N];
void dfs1(int no){
    si[no]=1;
    zs[no]=0;
    mxd[no]=d[no];
    for(int to:te[no]){
        d[to]=d[no]+1;
        dfs1(to);
        si[no]+=si[to];
        if(mxd[to]>mxd[no]){
            zs[no]=to;
            mxd[no]=mxd[to];
        }
    }
}
ll ans;
void dfs2(int no){
    ans-=1ll*d[no]*(si[no]-1);
    if(te[no].empty()){
        hs[no].push_back(1);
        return;
    }
    for(int to:te[no]){
        dfs2(to);
    }
    swap(hs[no],hs[zs[no]]);
    int nsi=si[zs[no]];
    for(int to:te[no]){
        if(to==zs[no])continue;
        ans-=1ll*nsi*si[to]*d[no];
        nsi+=si[to];
        for(int i=0;i<hs[to].size();++i){
            ans-=1ll*d[no]*hs[to][hs[to].size()-i-1]*hs[no][hs[no].size()-i-1];
            hs[no][hs[no].size()-i-1]+=hs[to][hs[to].size()-i-1];
        }
    }
    hs[no].push_back(1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        ans=0;
        for(int i=0;i<=n;++i){
            hs[i].clear();
            te[i].clear();
            mxd[i]=0;
            sid[i]=0;
        }
        fa[n]=n;
        for(int i=1;i<n;++i){
            fa[i]=i+1;
        }
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            fa[u]=max(fa[u],v);
        }
        for(int i=1;i<n;++i){
            te[fa[i]].push_back(i);
        }
        d[n]=0;
        dfs1(n);
        for(int i=1;i<=n;++i){
            sid[d[i]]++;
        }
        for(int i=1;i<=n;++i){
            ans+=1ll*i*sid[i]*(n-sid[i]-sid[i-1]);
            ans+=1ll*i*sid[i]*(sid[i]-1);
            sid[i]+=sid[i-1];
        }
        dfs2(n);
        cout<<ans<<'\n';
    }
    return 0;
}