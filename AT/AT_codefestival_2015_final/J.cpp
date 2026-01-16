#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,q;
int s[N];
struct node{
    int f[2][2];
    int sum;
    int* operator[](const int& id){return f[id];}
}t[N<<2];
node pushup(node x,node y){
    node ans;
    ans.sum=x.sum+y.sum;
    for(int opl:{0,1}){
        for(int opr:{0,1}){
            ans[opl][opr]=max({x[opl][0]+y[0][opr],x[opl][0]+y[1][opr],x[opl][1]+y[0][opr]});
        }
    }
    return ans;
}
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void build(int l,int r,int k){
    if(l==r){
        t[k].sum=s[l];
        t[k][1][1]=s[l];
        return;
    }
    build(l,mid,ls);build(mid+1,r,rs);
    t[k]=pushup(t[ls],t[rs]);
}
void update(int l,int r,int k,int x){
    if(l==r){
        t[k].sum=s[l];
        t[k][1][1]=s[l];
        return;
    }
    if(x<=mid)update(l,mid,ls,x);
    else update(mid+1,r,rs,x);
    t[k]=pushup(t[ls],t[rs]);
}
#undef mid
#undef rs
#undef ls
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>s[i];
    }
    build(1,n,1);
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        s[x]=y;
        update(1,n,1,x);
        cout<<(t[1].sum-max({t[1][0][0],t[1][1][0],t[1][0][1]}))*2<<'\n';
    }
    return 0;
}