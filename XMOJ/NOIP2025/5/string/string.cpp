#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n,q;
int a[N];
struct node{
    int l,r;
    int cn;
    int s1,s2;
    int le,re;
}t[N<<2];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
int ch(int l,int r,int id){
    if(!a[id])return 0;
    if(id!=l&&a[id-1]==1)return 0;
    if(id!=r&&a[id+1]==1)return 0;
    return 1;
}
int ch1(int l,int r,int id){
    if(id-1<l||id+1>r)return 0;
    if(a[id])return 0;
    if(a[id-1]+a[id+1]!=2)return 0;
    if(ch(l,r,id-1)||ch(l,r,id+1))return 0;
    return 1;
}
node pushup(node x,node y){
    node as;
    as.l=x.l;
    as.r=y.r;
    as.cn=x.cn+y.cn;
    if(x.re&&y.le)as.cn--;
    as.s1=x.s1+y.s1;
    as.s2=x.s2+y.s2;
    as.le=x.le;
    as.re=y.re;
    as.s1+=ch1(as.l,as.r,x.r-1)+ch1(as.l,as.r,x.r)+ch1(as.l,as.r,y.l)+ch1(as.l,as.r,y.l+1)-ch1(x.l,x.r,x.r-1)-ch1(y.l,y.r,y.l+1);
    if(ch(y.l,y.r,y.l)&&!ch(as.l,as.r,y.l))--as.s2;
    if(ch(x.l,x.r,x.r)&&!ch(as.l,as.r,x.r))--as.s2;
    return as;
}
void build(int l,int r,int k){
    if(l==r){
        if(a[l]){
            t[k].l=l,t[k].r=r;
            t[k].cn=t[k].le=t[k].re=1;
            t[k].s1=0;t[k].s2=1;
        }
        else{
            t[k].l=l,t[k].r=r;
            t[k].cn=t[k].le=t[k].re=0;
            t[k].s1=0;t[k].s2=0;
        }
        return;
    }
    build(l,mid,ls);
    build(mid+1,r,rs);
    t[k]=pushup(t[ls],t[rs]);
}
void update(int l,int r,int k,int x,int y){
    if(l==r){
        a[l]=y;
        if(a[l]){
            t[k].l=l,t[k].r=r;
            t[k].cn=t[k].le=t[k].re=1;
            t[k].s1=0;t[k].s2=1;
        }
        else{
            t[k].l=l,t[k].r=r;
            t[k].cn=t[k].le=t[k].re=0;
            t[k].s1=0;t[k].s2=0;
        }
        return;
    }
    if(x<=mid)update(l,mid,ls,x,y);
    else update(mid+1,r,rs,x,y);
    t[k]=pushup(t[ls],t[rs]);
}
node query(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y)return t[k];
    if(y<=mid)return query(l,mid,ls,x,y);
    if(x>mid)return query(mid+1,r,rs,x,y);
    return pushup(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y));
}
int main(){
    freopen("string2.in","r",stdin);
    freopen("string.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%1d",&a[i]);
    build(1,n,1);
    scanf("%d",&q);
    while(q--){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            node as=query(1,n,1,x,y);
            printf("%d\n",as.cn*2-as.s1-as.s2);
        }
        else update(1,n,1,x,y);
    }
    return 0;
}