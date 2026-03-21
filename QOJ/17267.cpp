#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int M=1e6;
const double qf=1e-3;
const double inf=1e18;
int T;
int n,m,q,b;
vector<double> vl;
int id[M+5];
vector<pair<int,double>> e[N];
int fa[N];
double d[N];
bool vis[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int no){
    if(!vis[no])return;
    d[no]=inf;
    vis[no]=0;
    for(auto [to,tw]:e[no]){
        dfs(to);
    }
}
int main(){
    double las=-1;
    for(int i=1;i<=M;++i){
        if(las<i*(1-qf)){
            las=i*(1+qf);
            vl.push_back(las);
        }
        id[i]=vl.size()-1;
    }
    cin>>T;
    if(T<0){
        T=-T;
        while(T--){
            cin>>m;
            string s;
            for(int i=1;i<=m;++i){
                int w;
                cin>>w;
                w=id[w];
                for(int j=0;j<12;++j){
                    if(w&(1<<j))s+="1";
                    else s+="0";
                }
            }
            cout<<s.size()<<endl;
            cout<<s<<endl;
        }
        return 0;
    }
    while(T--){
        cin>>n>>m>>q>>b;
        iota(fa+1,fa+n+1,1);
        for(int i=1;i<=n;++i){
            e[i].clear();
        }
        string s;
        cin>>s;
        for(int i=0;i<m;++i){
            int u,v;
            cin>>u>>v;
            int be=i*12;
            int w=0;
            for(int j=0;j<12;++j){
                if(s[be+j]=='1')w+=(1<<j);
            }
            e[u].emplace_back(v,vl[w]);
            e[v].emplace_back(u,vl[w]);
            fa[find(u)]=find(v);
        }
        fill(d+1,d+n+1,inf);
        while(q--){
            int x,y;
            cin>>x>>y;
            if(find(x)!=find(y)){
                cout<<"-1"<<endl;
                continue;
            }
            priority_queue<pair<double,int>> q;
            q.emplace(0,x);
            d[x]=0;
            while(!q.empty()){
                int no=q.top().second;
                q.pop();
                if(vis[no])continue;
                vis[no]=1;
                for(auto [to,tw]:e[no]){
                    if(d[to]<=d[no]+tw)continue;
                    d[to]=d[no]+tw;
                    q.emplace(-d[to],to);
                }
            }
            printf("%.15f",d[y]);
            cout<<endl;
            dfs(x);
        }
    }
    return 0;
}