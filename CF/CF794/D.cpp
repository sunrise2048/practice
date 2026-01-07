#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n,m;
vector<int> e[N];
int d[N],mxd;
bool fl[N];
int d1[N],mxd1;
int c[N];
int si[N];
int mc;
void bfs(int z){
    memset(d,0,sizeof(d));
    mxd=1;
    queue<int> q;
    q.push(z);
    d[z]=1;
    while(!q.empty()){
        int no=q.front();
        q.pop();
        mxd=d[no];
        for(int to:e[no]){
            if(fl[to])continue;
            if(d[to])continue;
            d[to]=d[no]+1;
            q.push(to);
        }
    }
    for(int i=1;i<=n;++i){
        if(d[i]){
            if(i!=z)d[i]--;
        }
    }
    if(mxd>1)mxd--;
}
void prt(){
    ll s=0;
    for(int i=1;i<=mc;++i){
        s+=1ll*si[i]*(si[i]-1)/2;
        if(i!=mc){
            s+=1ll*si[i]*si[i+1];
        }
    }
    if(s!=m){
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n";
    for(int i=1;i<=n;++i){
        cout<<c[i]<<' ';
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    if(m==1ll*n*(n-1)/2){
        cout<<"YES\n";
        for(int i=1;i<=n;++i)cout<<"1 ";
        return 0;
    }
    bfs(1);
    int z1=1;
    for(int i=2;i<=n;++i){
        if(d[i]>d[z1])z1=i;
    }
    if(d[z1]==1){
        for(int i=1;i<=n;++i){
            if(e[i].size()==n-1){
                fl[i]=1;
            }
        }
        for(int i=1;i<=n;++i){
            if(fl[i])continue;
            bfs(i);
            break;
        }
        for(int i=1;i<=n;++i){
            if(fl[i])c[i]=2;
            else if(d[i])c[i]=1;
            else c[i]=3;
        }
        for(int i=1;i<=n;++i){
            si[c[i]]++;
        }
        mc=3;
        prt();
        return 0;
    }
    bfs(z1);
    memcpy(d1,d,sizeof(d1));
    mxd1=mxd;
    z1=1;
    for(int i=2;i<=n;++i){
        if(d[i]>d[z1])z1=i;
    }
    bfs(z1);
    for(int i=1;i<=n;++i){
        if(d[i]==1)c[i]=d[i]+(d1[i]!=mxd1);
        else c[i]=d[i]+1;
        si[c[i]]++;
        mc=max(mc,c[i]);
    }
    prt();
    return 0;
}