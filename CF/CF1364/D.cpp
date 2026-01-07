#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m,k;
vector<int> e[N];
bool fl[N];
int cn;
void dfs(int no){
    if(fl[no])return;
    if(cn==k)return;
    ++cn;
    fl[no]=1;
    for(int to:e[no]){
        dfs(to);
    }
}
int fa[N];
int d[N];
int t[2];
vector<int> id;
bool dfs1(int no,int nf){
    fa[no]=nf;
    d[no]=d[nf]+1;
    t[d[no]&1]++;
    for(int to:e[no]){
        if(!fl[to])continue;
        if(to==nf)continue;
        if(d[to]){
            while(no!=to){
                id.push_back(no);
                no=fa[no];
            }
            id.push_back(to);
            return 1;
        }
        if(dfs1(to,no))return 1;
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
    dfs(1);
    if(dfs1(1,0)){
        cout<<"2\n";
        cout<<id.size()<<'\n';
        for(int no:id){
            cout<<no<<' ';
        }
        return 0;
    }
    cout<<"1\n";
    if(t[0]>=(k+1)/2){
        int cn=(k+1)/2;
        for(int i=1;i<=n;++i){
            if(!fl[i])continue;
            if(d[i]&1)continue;
            --cn;
            cout<<i<<' ';
            if(cn==0)break;
        }
    }
    else{
        int cn=(k+1)/2;
        for(int i=1;i<=n;++i){
            if(!fl[i])continue;
            if(d[i]&1){
                --cn;
                cout<<i<<' ';
                if(cn==0)break;
            }
        }
    }
    return 0;
}