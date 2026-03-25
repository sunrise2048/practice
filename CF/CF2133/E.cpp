#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
vector<int> e[N];
bool fl[N],vis[N];
vector<pair<int,int>> ope;
int si[N];
void dfs(int no,int fa){
    si[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        si[no]+=si[to];
    }
    if(si[no]>3){
        si[no]=0;
        ope.emplace_back(2,no);
        fl[no]=1;
    }
}
void dfs1(int no,int fa){
    ope.emplace_back(1,no);
    vis[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs1(to,no);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        ope.clear();
        for(int i=1;i<=n;++i){
            e[i].clear();
            fl[i]=vis[i]=0;
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
        for(int i=1;i<=n;++i){
            vector<int> ne;
            for(int to:e[i]){
                if(fl[to]||fl[i])continue;
                ne.push_back(to);
            }
            swap(e[i],ne);
        }
        for(int i=1;i<=n;++i){
            if(vis[i])continue;
            if(e[i].size()<2)dfs1(i,0);
        }
        cout<<ope.size()<<'\n';
        for(auto [x,y]:ope)cout<<x<<' '<<y<<'\n';
    }
    return 0;
}