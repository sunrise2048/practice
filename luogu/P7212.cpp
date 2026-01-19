#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m;
int fa[N];
ll si[N];
set<int> in[N],out[N],in_id[N],id[N];
ll cn;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
ll get_s(int x){
    return si[x]*(si[x]-1)+si[x]*in_id[x].size();
}
queue<pair<int,int>> q;
void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y)return;
    cn-=get_s(x)+get_s(y);
    if(id[x].size()<id[y].size())swap(x,y);
    in[x].erase(y);
    out[x].erase(y);
    for(int no:id[y]){
        id[x].insert(no);
        in_id[x].erase(no);
    }
    for(int no:in_id[y]){
        if(find(no)==x)continue;
        in_id[x].insert(no);
    }
    for(int no:in[y]){
        if(no==x)continue;
        in[x].insert(no);
        out[no].insert(x);
        out[no].erase(y);
        if(out[x].count(no)){
            q.emplace(x,no);
        }
    }
    for(int no:out[y]){
        if(no==x)continue;
        out[x].insert(no);
        in[no].insert(x);
        in[no].erase(y);
        if(in[x].count(no)){
            q.emplace(x,no);
        }
    }
    fa[y]=x;
    si[x]+=si[y];
    cn+=get_s(x);
}
void work(){
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();
        merge(x,y);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        fa[i]=i;
        si[i]=1;
        id[i].insert(i);
    }
    while(m--){
        int u,v;
        cin>>u>>v;
        if(in[find(u)].count(find(v))){
            q.emplace(u,v);
            work();
        }
        else if(find(u)!=find(v)){
            v=find(v);
            cn-=get_s(find(u))+get_s(v);
            in[v].insert(find(u));out[find(u)].insert(v);
            in_id[v].insert(u);
            cn+=get_s(find(u))+get_s(v);
        }
        cout<<cn<<'\n';
    }
    return 0;
}