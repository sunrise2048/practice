#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e4+5,M=2e5+5;
int n,m;
pair<int,int> a[N];
struct node{
    int x[2];
    int l[2],r[2];
    int s[2];
    int id;
    int lz_add,lz0,lz_a0,lz_mx;
    int mx,nx;
}t[M];
int rt;
int build(int l,int r,int op=0){
    if(l>r)return 0;
    const int no=l+r>>1;
    nth_element(t+l,t+no,t+r+1,[&](const node& x,const node& y){
        return x.x[op]<y.x[op];
    });
    t[no].s[0]=build(l,no-1,op^1);
    t[no].s[1]=build(no+1,r,op^1);
    t[no].l[0]=t[no].r[0]=t[no].x[0];
    t[no].l[1]=t[no].r[1]=t[no].x[1];
    int ns;
    if(ns=t[no].s[0]){
        t[no].l[0]=min(t[no].l[0],t[ns].l[0]);
        t[no].r[0]=max(t[no].r[0],t[ns].r[0]);
        t[no].l[1]=min(t[no].l[1],t[ns].l[1]);
        t[no].r[1]=max(t[no].r[1],t[ns].r[1]);
    }
    if(ns=t[no].s[1]){
        t[no].l[0]=min(t[no].l[0],t[ns].l[0]);
        t[no].r[0]=max(t[no].r[0],t[ns].r[0]);
        t[no].l[1]=min(t[no].l[1],t[ns].l[1]);
        t[no].r[1]=max(t[no].r[1],t[ns].r[1]);
    }
    return no;
}
void upd_add(int no,int d){
    if(!no)return;
    if(t[no].lz0){
        t[no].lz_a0+=d;
        t[no].lz_mx=max(t[no].lz_mx,t[no].lz_a0);
    }
    else{
        t[no].lz_add+=d;
        t[no].lz_mx=max(t[no].lz_mx,t[no].lz_add);
    }
    t[no].nx+=d;
    t[no].mx=max(t[no].mx,t[no].nx);
}
void upd_0(int no){
    if(!no)return;
    t[no].lz_a0=0;
    t[no].lz0=1;
    t[no].nx=0;
}
void pushdown(int no){
    if(t[no].lz_add){
        upd_add(t[no].s[0],t[no].lz_add);
        upd_add(t[no].s[1],t[no].lz_add);
        t[no].lz_add=0;
    }
    if(t[no].lz0){
        upd_0(t[no].s[0]);upd_0(t[no].s[1]);
        t[no].lz0=0;
    }
    if(t[no].lz_a0){
        upd_add(t[no].s[0],t[no].lz_a0);
        upd_add(t[no].s[1],t[no].lz_a0);
        t[no].lz_a0=0;
    }
}
void update(int no,int* l,int* r){
    if(!no)return;
    if(l[0]<=t[no].l[0]&&t[no].r[0]<=r[0]&&l[1]<=t[no].l[1]&&t[no].r[1]<=r[1]){
        upd_add(no,1);
        return;
    }
    if(r[0]<t[no].l[0]||t[no].r[0]<l[0]||r[1]<t[no].l[1]||t[no].r[1]<l[1]){
        upd_0(no);
        return;
    }
    pushdown(no);
    update(t[no].s[0],l,r);update(t[no].s[1],l,r);
    if(l[0]<=t[no].x[0]&&t[no].x[0]<=r[0]&&l[1]<=t[no].x[1]&&t[no].x[1]<=r[1]){
        t[no].nx++;
        t[no].mx=max(t[no].mx,t[no].nx);
    }
    else{
        t[no].nx=0;
    }
}
int ans[M];
void upd_mx(int no,int d){
    if(!no)return;
    t[no].lz_mx=max(t[no].lz_mx,d);
    t[no].mx=max(t[no].mx,d);
}
void dfs(int no){
    if(!no)return;
    pushdown(no);
    ans[t[no].id]=t[no].mx;
    upd_mx(t[no].s[0],t[no].lz_mx);
    upd_mx(t[no].s[1],t[no].lz_mx);
    dfs(t[no].s[0]);dfs(t[no].s[1]);
}
int l[2],r[2];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i].first>>a[i].second;
    }
    for(int i=1;i<=m;++i){
        cin>>t[i].x[0]>>t[i].x[1];
        t[i].id=i;
    }
    rt=build(1,m);
    for(int i=1;i<=n;++i){
        l[0]=1,r[0]=a[i].second;
        l[1]=a[i].first,r[1]=1e9+1;
        update(rt,l,r);
    }
    dfs(rt);
    for(int i=1;i<=m;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}