#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n,m;
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
class SGT_val{
public:
    int t[N<<2],lz[N<<2],tz[N<<2];
    void pushup(int k){
        if(t[ls]>t[rs]){
            t[k]=t[ls]+lz[k];
            tz[k]=tz[ls];
        }
        else{
            t[k]=t[rs]+lz[k];
            tz[k]=tz[rs];
        }
    }
    void build(int l,int r,int k){
        if(l==r){
            tz[k]=l;
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        pushup(k);
    }
    void update(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y){
            t[k]++;
            lz[k]++;
            return;
        }
        if(x<=mid)update(l,mid,ls,x,y);
        if(y>mid)update(mid+1,r,rs,x,y);
        pushup(k);
    }
}sgt1;
multiset<int> st[N];
class SGT{
public:
    pair<int,int> t[N<<2];
    void build(int l,int r,int k){
        if(l==r){
            if(st[l].empty())t[k]={n+1,0};
            else t[k]={*st[l].begin(),l};
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        t[k]=min(t[ls],t[rs]);
    }
    void update(int l,int r,int k,int x){
        if(l==r){
            if(st[l].empty())t[k]={n+1,0};
            else t[k]={*st[l].begin(),l};
            return;
        }
        if(x<=mid)update(l,mid,ls,x);
        else update(mid+1,r,rs,x);
        t[k]=min(t[ls],t[rs]);
    }
    pair<int,int> query(int l,int r,int k,int x){
        if(x<=l)return t[k];
        if(x>mid)return query(mid+1,r,rs,x);
        return min(query(l,mid,ls,x),query(mid+1,r,rs,x));
    }
}sgt2;
int ans[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int l,r;
        cin>>l>>r;
        st[l].insert(r);
    }
    sgt1.build(1,n,1);
    sgt2.build(1,n,1);
    for(int i=1;i<=m;++i){
        ans[i]=ans[i-1];
        auto [nr,nl]=sgt2.query(1,n,1,1);
        int no=1;
        while(nr<=n){
            st[nl].erase(st[nl].find(nr));
            ++ans[i];
            sgt1.update(1,n,1,nl,nr);
            sgt2.update(1,n,1,nl);
            no=sgt1.tz[1];
            if(no==n)break;
            auto [tr,tl]=sgt2.query(1,n,1,no+1);
            swap(nr,tr);swap(nl,tl);
        }
    }
    ll j=m;
    for(int i=1;i<=n;++i){
        while(j&&ans[j]-ans[j-1]<=i)--j;
        cout<<m-ans[j]+i*j<<'\n';
    }
    return 0;
}