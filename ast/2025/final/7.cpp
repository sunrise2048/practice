#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4e5+5;
int n;
int m;
pair<int,int> nd[N];
vector<pair<int,int>> td;
vector<int> e[N];
map<int,set<int>> zh,zl;
void adde(int u,int x,int y){
    int v=lower_bound(td.begin(),td.end(),make_pair(x,y))-td.begin();
    e[u].push_back(v);
}
int cn_dfn,cn_scc;
int low[N],dfn[N];
int scc[N];
int cn[N];
int mx[N];
int in[N];
vector<int> sfe[N];
stack<int> st;
void tarjan(int no){
    low[no]=dfn[no]=++cn_dfn;
    st.push(no);
    for(int to:e[no]){
        if(!dfn[to]){
            tarjan(to);
            low[no]=min(low[no],low[to]);
        }
        else if(!scc[to])low[no]=min(low[no],dfn[to]);
    }
    if(low[no]==dfn[no]){
        int nc=++cn_scc;
        while(!st.empty()&&dfn[st.top()]>=dfn[no]){
            int id=st.top();
            st.pop();
            scc[id]=nc;
            cn[nc]++;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    td.emplace_back(0,0);
    for(int i=1;i<=n;++i){
        cin>>nd[i].first>>nd[i].second;
        zh[nd[i].first].insert(nd[i].second);
        zl[nd[i].second].insert(nd[i].first);
    }
    for(int i=1;i<=n;++i){
        if(zh[nd[i].first+1].count(nd[i].second)==0)td.emplace_back(nd[i].first+1,nd[i].second);
        if(zh[nd[i].first-1].count(nd[i].second)==0)td.emplace_back(nd[i].first-1,nd[i].second);
        if(zh[nd[i].first].count(nd[i].second-1)==0)td.emplace_back(nd[i].first,nd[i].second-1);
        if(zh[nd[i].first].count(nd[i].second+1)==0)td.emplace_back(nd[i].first,nd[i].second+1);
    }
    sort(td.begin(),td.end());
    td.erase(unique(td.begin(),td.end()),td.end());
    m=td.size();
    for(int i=0;i<m;++i){
        auto [x,y]=td[i];
        auto it=zh[x].lower_bound(y);
        if(it!=zh[x].end()&&*it!=y+1){
            adde(i,x,(*it)-1);
        }
        if(it!=zh[x].begin()&&*prev(it)!=y-1){
            adde(i,x,(*prev(it))+1);
        }
        it=zl[y].lower_bound(x);
        if(it!=zl[y].end()&&*it!=x+1){
            adde(i,(*it)-1,y);
        }
        if(it!=zl[y].begin()&&*prev(it)!=x-1){
            adde(i,(*prev(it))+1,y);
        }
    }
    int rt=lower_bound(td.begin(),td.end(),make_pair(0,0))-td.begin();
    tarjan(rt);
    for(int i=0;i<m;++i){
        if(!scc[i])continue;
        for(int to:e[i]){
            if(scc[to]==scc[i])continue;
            sfe[scc[to]].push_back(scc[i]);
        }
    }
    for(int i=1;i<=cn_scc;++i){
        sort(sfe[i].begin(),sfe[i].end());
        sfe[i].erase(unique(sfe[i].begin(),sfe[i].end()),sfe[i].end());
        for(int to:sfe[i]){
            in[to]++;
        }
    }
    queue<int> q;
    for(int i=1;i<=cn_scc;++i){
        if(!in[i])q.push(i);
    }
    while(!q.empty()){
        int no=q.front();
        q.pop();
        cn[no]+=mx[no];
        for(int to:sfe[no]){
            mx[to]=max(mx[to],cn[no]);
            in[to]--;
            if(in[to]==0)q.push(to);
        }
    }
    cout<<cn[scc[rt]]<<'\n';
    return 0;
}