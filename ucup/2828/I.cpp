#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e3+5;
int n,m;
int c[N];
vector<int> e[N];
vector<int> ct[N];
int rt[N];
int tc[N][N];
int d[N];
int cng;
bool vis[N];
void add(int x,int y){
    d[x]++;
    tc[x][c[y]]=y;
    rt[y]=x;
}
void era(int x,int y){
    d[x]--;
    tc[x][c[y]]=0;
    rt[y]=0;
}
bool dfs(int no){
    if(vis[no])return 0;
    vis[no]=1;
    for(int to:e[no]){
        if(!rt[to]){
            rt[no]=no;
            add(no,to);
            return 1;
        }
        if(rt[to]!=to){
            int trt=rt[to];
            if(d[trt]==1){
                era(trt,to);add(to,trt);
                rt[to]=to;
            }
            else{
                era(trt,to);
                rt[no]=no;
                add(no,to);
                return 1;
            }
        }
        int cs=tc[to][c[no]];
        if(!cs){
            add(to,no);
            return 1;
        }
        era(to,cs);add(to,no);
        if(dfs(cs))return 1;
        era(to,no);add(to,cs);
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>c[i];
        ct[c[i]].push_back(i);
    }
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        if(c[u]==c[v])continue;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int nc=1;nc<=n;++nc){
        for(int no:ct[nc]){
            if(rt[no])continue;
            memset(vis,0,sizeof(vis));
            if(!dfs(no))++cng;
        }
    }
    vector<pair<int,int>> ed;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(tc[i][j])ed.emplace_back(i,tc[i][j]);
        }
    }
    cout<<cng<<'\n';
    cout<<ed.size()<<'\n';
    for(auto [u,v]:ed){
        cout<<u<<' '<<v<<'\n';
    }
    return 0;
}