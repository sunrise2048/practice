#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int mod=1e9+7;
int n;
int al[N],ar[N];
pair<int,int> f[N];
pair<int,int> t[N<<2];
pair<int,int> upd(pair<int,int> x,pair<int,int> y){
    if(x.first==y.first)return {x.first,(x.second+y.second)%mod};
    if(x.first>y.first)return x;
    return y;
}
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void pushup(int k){
    t[k]=upd(t[ls],t[rs]);
}
void update(int l,int r,int k,int x,int fl){
    if(l==r){
        if(fl&&f[l-1].second)t[k]={f[l-1].first+1,f[l-1].second};
        else t[k]={-N,0};
        return;
    }
    if(x<=mid)update(l,mid,ls,x,fl);
    else update(mid+1,r,rs,x,fl);
    pushup(k);
}
pair<int,int> query(int l,int r,int k,int x,int y){
    if(x<=l&r<=y)return t[k];
    if(y<=mid)return query(l,mid,ls,x,y);
    if(x>mid)return query(mid+1,r,rs,x,y);
    return upd(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y));
}
#undef mid
#undef rs
#undef ls
vector<int> add[N],era[N];
void solve(int l,int r){
    if(l>r)return;
    if(l==r){
        if(al[l]!=1||!f[l-1].second)return;
        f[l]=upd(f[l],make_pair(f[l-1].first+1,f[l-1].second));
        return;
    }
    const int mid=(l+r>>1);
    solve(l,mid);
    int mi=0,ma=n;
    for(int i=mid;i>=l;--i){
        mi=max(mi,al[i]);ma=min(ma,ar[i]);
        int tl=max(i+mi-1,mid+1),tr=min(i+ma-1,r);
        if(tl>tr)continue;
        add[tl].push_back(i);era[tr+1].push_back(i);
    }
    mi=0,ma=n;
    for(int i=mid+1;i<=r;++i){
        for(int no:add[i])update(1,n,1,no,1);
        for(int no:era[i])update(1,n,1,no,0);
        add[i].clear();era[i].clear();
        mi=max(mi,al[i]);ma=min(ma,ar[i]);
        int tl=max(l,i-ma+1),tr=min(mid,i-mi+1);
        if(tl>tr)continue;
        f[i]=upd(f[i],query(1,n,1,tl,tr));
    }
    for(int no:era[r+1])update(1,n,1,no,0);
    era[r+1].clear();
    solve(mid+1,r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>al[i]>>ar[i];
    }
    for(int i=1;i<=n;++i){
        f[i]={-N,0};
    }
    f[0]={0,1};
    solve(1,n);
    if(f[n].first<1){
        cout<<"NIE\n";
        return 0;
    }
    cout<<f[n].first<<' '<<f[n].second<<'\n';
    return 0;
}