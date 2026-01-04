#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T;
int n,m;
vector<int> e[N];
vector<int> id;
bool fl[N];
bool vis[N];
void dfs(int no){
    if(!fl[no]){
        id.push_back(no);
        for(int to:e[no])fl[to]=1;
    }
    vis[no]=1;
    for(int to:e[no]){
        if(vis[to])continue;
        dfs(to);
    }
}
bool ch(){
    for(int i=1;i<=n;++i){
        if(!vis[i])return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            e[i].clear();
            fl[i]=vis[i]=0;
        }
        id.clear();
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1);
        if(!ch()){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        cout<<id.size()<<'\n';
        for(int no:id)cout<<no<<' ';
        cout<<'\n';
    }
    return 0;
}