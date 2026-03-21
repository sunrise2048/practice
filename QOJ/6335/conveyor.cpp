#include "conveyor.h"
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n;
vector<int> e[N],le[N];
vector<pair<int,int>> E;
int d[N];
int de[N];
vector<int> dc[3];
bool fl[N];
bool nfl[N];
vector<int> ans;
void dfs_d(int no,int fa){
    d[no]=d[fa]+1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs_d(to,no);
    }
}
bool qu(){
    vector<int> fz(n),fe(n-1);
    memset(nfl,0,sizeof(nfl));
    for(int op:{0,1,2})dc[op].clear();
    for(int i=0;i<n;++i){
        if(de[i])dc[d[i]%3].push_back(i);
    }
    int nd=0;
    for(int op:{1,2})if(dc[op].size()>dc[nd].size())nd=op;
    if(dc[nd].empty())return 0;
    for(int no:dc[nd])nfl[no]=fz[no]=1;
    for(int i=0;i<n-1;++i){
        auto [u,v]=E[i];
        if(fl[i]){
            if(ans[i]==0&&nfl[u])fe[i]=1;
            if(ans[i]&&nfl[v])fe[i]=1;
        }
    }
    vector<int> nz=Query(fe,fz);
    for(int i=0;i<n;++i){
        if(!nfl[i])continue;
        if(nz[i]){
            for(int id:le[i]){
                if(fl[id])continue;
                auto [u,v]=E[id];
                fl[id]=1;
                de[u]--,de[v]--;
                if(u==i){
                    ans[id]=1;
                }
            }
            continue;
        }
        bool fd=0;
        int fid=0;
        for(int id:le[i]){
            if(fl[id])continue;
            auto [u,v]=E[id];
            if(!nz[u+v-i])continue;
            if(d[u]+d[v]-d[i]<d[i]){
                fid=id;
                continue;
            }
            fl[id]=1;
            de[u]--,de[v]--;
            if(v==i)ans[id]=1;
            fd=1;
            break;
        }
        if(!fd){
            if(fl[fid])exit(1);
            auto [u,v]=E[fid];
            fl[fid]=1;
            de[u]--,de[v]--;
            if(v==i)ans[fid]=1;
        }
    }
    return 1;
}
void Solve(int n,vector<int> a,vector<int> b){
    ::n=n;
    ans.resize(n-1);
    for(int i=0;i<n-1;++i){
        int u=a[i],v=b[i];
        E.emplace_back(u,v);
        e[u].push_back(v);
        le[u].push_back(i);
        e[v].push_back(u);
        le[v].push_back(i);
    }
    for(int i=0;i<n;++i){
        de[i]=e[i].size();
    }
    dfs_d(0,0);
    while(qu());
    Answer(ans);
}