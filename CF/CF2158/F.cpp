#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=50;
int T;
int n,m;
vector<ll> ve;
int gt(int x){
    if(x&1)return x*(x-1)/2+x+1;
    return x*(x-1)/2-x/2+1+x+1;
}
ll nv[N];
int e[N][N];
void dfs(int no){
    for(int i=1;i<=m;++i){
        if(!e[no][i])continue;
        e[no][i]=e[i][no]=0;
        dfs(i);
    }
    ve.push_back(nv[no]);
}
void solve(){
    m=2;
    while(gt(m)<n)++m;
    nv[1]=1;
    for(int i=1;i<m;++i){
        nv[1]*=3;
    }
    for(int i=2;i<=m;++i)nv[i]=nv[i-1]/3*2;
    for(int i=1;i<=m;++i){
        for(int j=1;j<=m;++j){
            e[i][j]=1;
        }
    }
    if(m%2==0){
        for(int i=3;i<=m;i+=2){
            e[i][i+1]=e[i+1][i]=0;
        }
    }
    ve.clear();
    dfs(1);
    ve.resize(n);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        if(n==2){
            cout<<"1 1\n";
            continue;
        }
        solve();
        for(ll vl:ve)cout<<vl<<' ';
        cout<<'\n';
    }
    return 0;
}