#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int B=450;
int n,m;
struct node{
    int x[2];
    int l[2],r[2];
    int s[2];
    int val;
    int sum;
}t[N];
int rt;
int l[2],r[2];
int lans;
int build(int l,int r,int op=0){
    if(l>r)return 0;
    if(l==r){
        t[l].l[0]=t[l].r[0]=t[l].x[0];
        t[l].l[1]=t[l].r[1]=t[l].x[1];
        t[l].sum=t[l].val;
        t[l].s[0]=t[l].s[1]=0;
        return l;
    }
    nth_element(t+l,t+(l+r>>1),t+r+1,[&](const node& x,const node& y){
        return x.x[op]<y.x[op];
    });
    const int no=l+r>>1;
    int ls=t[no].s[0]=build(l,no-1,op^1);
    int rs=t[no].s[1]=build(no+1,r,op^1);
    t[no].sum=t[no].val;
    t[no].l[0]=t[no].r[0]=t[no].x[0];
    t[no].l[1]=t[no].r[1]=t[no].x[1];
    if(ls){
        t[no].sum+=t[ls].sum;
        t[no].l[0]=min(t[no].l[0],t[ls].l[0]);
        t[no].r[0]=max(t[no].r[0],t[ls].r[0]);
        t[no].l[1]=min(t[no].l[1],t[ls].l[1]);
        t[no].r[1]=max(t[no].r[1],t[ls].r[1]);
    }
    if(rs){
        t[no].sum+=t[rs].sum;
        t[no].l[0]=min(t[no].l[0],t[rs].l[0]);
        t[no].r[0]=max(t[no].r[0],t[rs].r[0]);
        t[no].l[1]=min(t[no].l[1],t[rs].l[1]);
        t[no].r[1]=max(t[no].r[1],t[rs].r[1]);
    }
    return no;
}
int query(int no,int* l,int* r){
    if(!no)return 0;
    if(l[0]<=t[no].l[0]&&t[no].r[0]<=r[0]&&l[1]<=t[no].l[1]&&t[no].r[1]<=r[1]){
        return t[no].sum;
    }
    if(r[0]<t[no].l[0]||t[no].r[0]<l[0]||r[1]<t[no].l[1]||t[no].r[1]<l[1])return 0;
    int sum=query(t[no].s[0],l,r)+query(t[no].s[1],l,r);
    if(l[0]<=t[no].x[0]&&t[no].x[0]<=r[0]&&l[1]<=t[no].x[1]&&t[no].x[1]<=r[1]){
        sum+=t[no].val;
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;n=0;
    int op;
    while(cin>>op){
        if(op==3)break;
        if(op==1){
            ++m;
            cin>>t[m].x[0]>>t[m].x[1];
            cin>>t[m].val;
            t[m].x[0]^=lans;t[m].x[1]^=lans;t[m].val^=lans;
            t[m].sum=t[m].val;
            if(m%B==0){
                n=m;
                rt=build(1,n);
            }
        }
        else{
            cin>>l[0]>>l[1]>>r[0]>>r[1];
            l[0]^=lans;l[1]^=lans;r[0]^=lans;r[1]^=lans;
            lans=query(rt,l,r);
            for(int i=n+1;i<=m;++i){
                if(l[0]<=t[i].x[0]&&t[i].x[0]<=r[0]&&l[1]<=t[i].x[1]&&t[i].x[1]<=r[1]){
                    lans+=t[i].val;
                }
            }
            cout<<lans<<'\n';
        }
    }
    return 0;
}