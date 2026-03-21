#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n,q;
ll a[N];
vector<int> lis;
struct node{
    ll sum;
    int lson,rson;
    int cn;
}t[N*20];
int cn;
int rt[N];
#define mid (l+r>>1)
#define rs(k) t[k].rson
#define ls(k) t[k].lson
void update(int l,int r,int& k,int k0,int x){
    k=++cn;t[k]=t[k0];
    t[k].cn++;t[k].sum+=lis[x];
    if(l==r)return;
    if(x<=mid)update(l,mid,ls(k),ls(k0),x);
    else update(mid+1,r,rs(k),rs(k0),x);
}
ll query(int l,int r,int k,int k0,int cn,ll sum){
    if(t[k].cn==t[k0].cn)return cn*sum;
    if(l==r){
        const int scn=t[k].cn-t[k0].cn;
        const ll val=lis[l];
        int cl=-1,cr=scn;
        while(cl<cr-1){
            ll md=cl+cr>>1;
            if((cn+scn-md)*(sum+md*val)<=(cn+scn-md-1)*(sum+(md+1)*val))cl=md;
            else cr=md;
        }
        return (cn+scn-cr)*(sum+cr*val);
    }
    int lcn=t[ls(k)].cn-t[ls(k0)].cn;
    ll rsm=t[rs(k)].sum-t[rs(k0)].sum;
    if((lcn+cn-1)*(rsm+sum+lis[mid])>(lcn+cn)*(rsm+sum))return query(l,mid,ls(k),ls(k0),cn,sum+rsm);
    return query(mid+1,r,rs(k),rs(k0),cn+lcn,sum);
}
#undef mid
#undef rs
#undef ls
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        lis.push_back(a[i]);
    }
    lis.push_back(0);
    sort(lis.begin(),lis.end());
    lis.erase(unique(lis.begin(),lis.end()),lis.end());
    const int lm=lis.size()-1;
    for(int i=1;i<=n;++i){
        a[i]=lower_bound(lis.begin(),lis.end(),a[i])-lis.begin();
        update(1,lm,rt[i],rt[i-1],a[i]);
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(1,lm,rt[r],rt[l-1],0,0)<<'\n';
    }
    return 0;
}