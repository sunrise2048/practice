#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int inf=1e8;
int n,m;
struct node{
    int fa;
    int x[2];
    int l[2],r[2];
    int mi;
    int s[2];
}a[N];
int fl[N];
int ans[N];
struct tmp{
    int l[2],r[2];
    int z;
    int id;
}q[N];
int rt;
int id[N];
int build(int l,int r,int op=0){
    if(l>r)return 0;
    if(l==r){
        int no=id[l];
        a[no].l[0]=a[no].r[0]=a[no].x[0];
        a[no].l[1]=a[no].r[1]=a[no].x[1];
        a[no].mi=no;
        return no;
    }
    nth_element(id+l,id+(l+r>>1),id+r+1,[&](const int& x,const int& y){
        return a[x].x[op]<a[y].x[op];
    });
    const int no=id[(l+r)>>1];
    const int mid=l+r>>1;
    a[no].s[0]=build(l,mid-1,op^1);
    a[no].s[1]=build(mid+1,r,op^1);
    if(a[no].s[0])a[a[no].s[0]].fa=no;
    if(a[no].s[1])a[a[no].s[1]].fa=no;
    a[no].l[0]=min({a[no].x[0],a[a[no].s[0]].l[0],a[a[no].s[1]].l[0]});
    a[no].r[0]=max({a[no].x[0],a[a[no].s[0]].r[0],a[a[no].s[1]].r[0]});
    a[no].l[1]=min({a[no].x[1],a[a[no].s[0]].l[1],a[a[no].s[1]].l[1]});
    a[no].r[1]=max({a[no].x[1],a[a[no].s[0]].r[1],a[a[no].s[1]].r[1]});
    a[no].mi=min({no,a[a[no].s[0]].mi,a[a[no].s[1]].mi});
    return no;
}
int query(int no,int* l,int* r){
    if(!no)return inf;
    if(l[0]<=a[no].l[0]&&a[no].r[0]<=r[0]&&l[1]<=a[no].l[1]&&a[no].r[1]<=r[1]){
        return a[no].mi;
    }
    if(a[no].r[0]<l[0]||a[no].r[1]<l[1]||r[0]<a[no].l[0]||r[1]<a[no].l[1]){
        return inf;
    }
    int as=min(query(a[no].s[0],l,r),query(a[no].s[1],l,r));
    if(l[0]<=a[no].x[0]&&a[no].x[0]<=r[0]&&l[1]<=a[no].x[1]&&a[no].x[1]<=r[1]&&fl[no]){
        as=min(as,no);
    }
    return as;
}
void era(int no){
    fl[no]=0;
    while(no){
        a[no].mi=min(a[a[no].s[0]].mi,a[a[no].s[1]].mi);
        if(fl[no])a[no].mi=min(a[no].mi,no);
        no=a[no].fa;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>q[i].l[0]>>q[i].r[0]>>q[i].l[1]>>q[i].r[1]>>q[i].z;
        q[i].id=i;
    }
    cin>>m;
    for(int i=1;i<=m;++i){
        cin>>a[i].x[0]>>a[i].x[1];
        fl[i]=1;
    }
    a[0].l[0]=a[0].l[1]=inf;
    a[0].r[0]=a[0].r[1]=-inf;
    a[0].mi=inf;
    iota(id+1,id+m+1,1);
    rt=build(1,m);
    sort(q+1,q+n+1,[](const tmp& x,const tmp& y){
        return x.z<y.z;
    });
    for(int i=1;i<=n;++i){
        int mi=query(rt,q[i].l,q[i].r);
        if(mi>m)continue;
        ans[mi]=q[i].id;
        era(mi);
    }
    for(int i=1;i<=m;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}