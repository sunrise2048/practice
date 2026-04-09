#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=65;
int T;
int n,m;
bool f[N][N*N];
vector<ll> dfs(int n,int m){
    if(m==2)return {0,(1ll<<n)-1};
    if(n==5&&m==15)return {0,1,3,5,7,8,9,11,13,15,24,25,27,29,31};
    if(f[n-1][m]){
        vector<ll> as=dfs(n-1,m);
        for(ll &no:as){
            if(no&(1ll<<n-2))no|=(1ll<<n-1);
        }
        return as;
    }
    if(f[n-1][m-1]){
        vector<ll> as=dfs(n-1,m-1);
        for(ll &no:as)no|=(1ll<<n-1);
        as.push_back(0);
        return as;
    }
    vector<ll> as=dfs(n-1,m/2);
    for(int i=0;i<m/2;++i)as.push_back(as[i]|(1ll<<n-1));
    return as;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    f[1][2]=1;
    for(int i=2;i<=60;++i){
        for(int j=2;j<=60*60;++j){
            f[i][j]=f[i-1][j]|f[i-1][j-1];
            if(j%2==0)f[i][j]|=f[i-1][j/2];
        }
    }
    cin>>T;
    while(T--){
        cin>>n>>m;
        vector<ll> as=dfs(n,m);
        for(auto no:as){
            cout<<no<<' ';
        }cout<<'\n';
    }
    return 0;
}