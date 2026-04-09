#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2.5e5+5;
int n,m,k;
vector<int> e[N];
int d[N];
int fa[N];
vector<int> yz;
void dfs(int no,int fa){
    ::fa[no]=fa;
    d[no]=d[fa]+1;
    int son=0;
    for(int to:e[no]){
        if(to==fa)continue;
        if(d[to])continue;
        ++son;
        dfs(to,no);
    }
    if(!son)yz.push_back(no);
}
bool ch_d(){
    int len=(n+k-1)/k;
    for(int i=1;i<=n;++i){
        if(d[i]!=len)continue;
        cout<<"PATH\n";
        cout<<len<<'\n';
        int no=i;
        while(no){
            cout<<no<<' ';
            no=fa[no];
        }
        return 1;
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    if(ch_d())return 0;
    cout<<"CYCLES\n";
    yz.resize(k);
    for(int no:yz){
        int x=e[no][0],y=e[no][1];
        if(abs(d[x]-d[y])%3==1)y=e[no][2];
        if(abs(d[x]-d[y])%3==1)x=e[no][1];
        if(d[x]<d[y])swap(x,y);
        cout<<d[x]-d[y]+2<<'\n';
        cout<<no<<' ';
        while(x!=y){
            cout<<x<<' ';
            x=fa[x];
        }
        cout<<y<<'\n';
    }
    return 0;
}