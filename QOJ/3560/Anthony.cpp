#include"Anthony.h"
#include<bits/stdc++.h>
using namespace std;
const int N=2e4+5;
const int inf=1e9+7;
int n,m,a,b;
vector<pair<int,int>> e[N];
int d[N];
void cl(){
    for(int i=0;i<n;++i){
        e[i].clear();
        d[i]=inf;
    }
}
vector<int> w;
void dfs(int no,int fa,int ld){
    int scn=0;
    for(auto [to,eid]:e[no]){
        if(to==fa)continue;
        ++scn;
    }
    if(scn>1||scn==0){
        if(ld==0||ld==2||ld==5)ld=0;
        else ld=1;
        for(auto [to,id]:e[no]){
            if(to==fa)continue;
            w[id]=ld^1;
            dfs(to,no,ld^1);
        }
        return;
    }
    if(ld==0||ld==2||ld==3){
        for(auto [to,id]:e[no]){
            if(to==fa)continue;
            w[id]=1;
            dfs(to,no,(ld+1)%6);
        }
    }
    else{
        for(auto [to,id]:e[no]){
            if(to==fa)continue;
            w[id]=0;
            dfs(to,no,(ld+1)%6);
        }
    }
}
vector<int> Mark(int n,int m,int a,int b,vector<int> u,vector<int> v){
    ::n=n;
    ::m=m;
    ::a=a;
    ::b=b;
    w.resize(m);
    cl();
    for(int i=0;i<m;++i){
        e[u[i]].emplace_back(v[i],i);
        e[v[i]].emplace_back(u[i],i);
    }
    queue<int> q;
    d[0]=0;
    q.push(0);
    while(!q.empty()){
        int no=q.front();
        q.pop();
        for(auto [to,tid]:e[no]){
            if(d[to]<=d[no]+1)continue;
            d[to]=d[no]+1;
            q.push(to);
        }
    }
    if(a>=3){
        for(int i=0;i<m;++i){
            int x=u[i],y=v[i];
            w[i]=min(d[x],d[y])%3;
        }
        return w;
    }
    dfs(0,0,0);
    return w;
}
