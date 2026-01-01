#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n;
int a[N];
int b[N];
bool vis[N];
int ans[N];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
int t[N<<2];
void pushup(int k){
    t[k]=max(t[ls],t[rs]);
}
void build(int l,int r,int k){
    if(l==r){
        t[k]=b[l];
        return;
    }
    build(l,mid,ls);build(mid+1,r,rs);
    pushup(k);
}
int query(int l,int r,int k,int x,int y,int d){
    if(t[k]<=d)return 0;
    if(l==r){
        t[k]=0;
        if(vis[l])return 0;
        return l;
    }
    int ans=0;
    if(x<=mid)ans=query(l,mid,ls,x,y,d);
    if(!ans&&y>mid)ans=query(mid+1,r,rs,x,y,d);
    pushup(k);
    return ans;
}
#undef mid
#undef rs
#undef ls
int cn;
void dfs(int no){
    if(vis[no])return;
    vis[no]=1;
    if(b[no]!=n+1&&!vis[b[no]]){
        dfs(b[no]);
    }
    int to;
    while((to=query(1,n,1,1,a[no]-1,no))!=0){
        dfs(to);
    }
    ans[no]=++cn;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        b[i]=n+1;
    }
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(a[i]==-1){
            a[i]=n+1;
        }
        b[a[i]]=i;
    }
    build(1,n,1);
    for(int i=1;i<=n;++i){
        if(vis[i])continue;
        dfs(i);
    }
    for(int i=1;i<=n;++i){
        cout<<ans[i]<<' ';
    }cout<<'\n';
    return 0;
}