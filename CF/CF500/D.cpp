#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,q;
vector<pair<int,int>> e[N];
ll w[N];
int eid[N];
ll si[N];
double sum;
ll C(ll cn){
    return cn*(cn-1)/2;
}
double CC(){
    return 1ll*n*(n-1)*(n-2)/6;
}
void dfs(int no,int fa){
    si[no]=1;
    for(auto [to,id]:e[no]){
        if(to==fa)continue;
        eid[id]=to;
        dfs(to,no);
        sum+=C(si[to])*(n-si[to])*w[id]/CC();
        sum+=si[to]*C(n-si[to])*w[id]/CC();
        si[no]+=si[to];
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;++i){
        int u,v,w;
        cin>>u>>v>>w;
        e[u].emplace_back(v,i);
        e[v].emplace_back(u,i);
        ::w[i]=w;
    }
    dfs(1,0);
    cin>>q;
    while(q--){
        int id,tw;
        cin>>id>>tw;
        int rt=eid[id];
        sum-=(C(si[rt])*(n-si[rt])+si[rt]*C(n-si[rt]))*w[id]/CC();
        sum+=(C(si[rt])*(n-si[rt])+si[rt]*C(n-si[rt]))*tw/CC();
        w[id]=tw;
        printf("%.12f\n",2*sum);
    }
    return 0;
}