#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int n,m;
map<int,pair<int,int>> f[N];
bool fl[N];
ll ans;
void adde(int x,int y,pair<int,int> p){
    if(f[x].count(y)){
        pair<int,int> lp=f[x][y];
        pair<int,int> np(((ll)p.first*lp.second+(ll)p.second*lp.first)%mod,(ll)p.second*lp.second%mod);
        f[x][y]=f[y][x]=np;
        return;
    }
    f[x][y]=f[y][x]=p;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        adde(u,v,{1,1});
    }
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(f[i].size()<=2){
            q.push(i);
            fl[i]=1;
        }
    }
    ans=1;
    while(!q.empty()){
        int no=q.front();
        q.pop();
        if(f[no].size()==0)continue;
        if(f[no].size()==1){
            auto [to,pr]=*f[no].begin();
            ans=ans*pr.first%mod;
            f[no].erase(to);f[to].erase(no);
            if(!fl[to]&&f[to].size()<=2){
                fl[to]=1;
                q.push(to);
            }
        }
        else{
            auto [t1,p1]=*f[no].begin();
            auto [t2,p2]=*f[no].rbegin();
            pair<int,int> tp((ll)p1.first*p2.first%mod,((ll)p1.first*p2.second+(ll)p1.second*p2.first)%mod);
            f[t1].erase(no);f[t2].erase(no);
            f[no].clear();
            adde(t1,t2,tp);
            if(f[t1].size()<=2&&!fl[t1]){
                fl[t1]=1;
                q.push(t1);
            }
            if(f[t2].size()<=2&&!fl[t2]){
                fl[t2]=1;
                q.push(t2);
            }
        }
    }
    cout<<ans<<'\n'; 
    return 0;
}