#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n,m;
vector<int> e[N];
bool vis[N];
bool fl[N];
int in[N];
vector<int> id;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
    }
    for(int i=1;i<=n;++i){
        if(vis[i])continue;
        fl[i]=vis[i]=1;
        for(int to:e[i]){
            vis[to]=1;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j:e[i]){
            if(fl[i]&&fl[j])in[j]++;
        }
    }
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(fl[i]&&in[i]==0)q.push(i);
    }
    memset(vis,0,sizeof(vis));
    while(!q.empty()){
        int no=q.front();
        q.pop();
        if(!vis[no]){
            id.push_back(no);
            for(int to:e[no]){
                vis[to]=1;
            }
        }
        for(int to:e[no]){
            if(!fl[to])continue;
            --in[to];
            if(!in[to])q.push(to);
        }
    }
    cout<<id.size()<<'\n';
    for(int no:id)cout<<no<<' ';
    cout<<'\n';
    return 0;
}