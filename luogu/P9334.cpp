#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2.5e5+5;
const int B=61;
int n,q;
int a[N];
int ne[N];
class SGT{
public:
    struct node{
        int len;
        vector<pair<int,int>> nxt;
        pair<int,int> get(const pair<int,int>& las)const{
            auto [id,cn]=las;
            if(id>len)return {id-len,cn};
            return {nxt[id].first,nxt[id].second+cn};
        }
        node operator+(const node& ls)const{
            node as;
            as.len=len+ls.len;
            as.nxt.resize(min(as.len,B)+1);
            for(int i=1;i<as.nxt.size();++i){
                as.nxt[i]=ls.get(get({i,0}));
            }
            return as;
        }
    }t[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void update(int l,int r,int k,int x,int y){
        if(l==r){
            t[k].len=1;
            t[k].nxt.resize(2);
            t[k].nxt[1]={ne[l]-l,1};
            return;
        }
        if(x<=mid)update(l,mid,ls,x,y);
        if(y>mid)update(mid+1,r,rs,x,y);
        t[k]=t[ls]+t[rs];
    }
    pair<int,int> query(int l,int r,int k,int x,int y,const pair<int,int>& las){
        if(x<=l&&r<=y)return t[k].get(las);
        if(y<=mid)return query(l,mid,ls,x,y,las);
        if(x>mid)return query(mid+1,r,rs,x,y,las);
        return query(mid+1,r,rs,x,y,query(l,mid,ls,x,y,las));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
void rebuild(int l,int r){
    for(int i=r;i>=l;--i){
        ne[i]=ne[i+1];
        ll s=0;
        for(int j=i+2;j<=n&&j<=ne[i]&&j<=i+B;++j){
            s+=a[j];
            if(s>a[i+1]&&s>a[j+1]){
                ne[i]=j;
                break;
            }
        }
    }
    sgt.update(0,n,1,l,r);
}
int query(int l,int r){
    if(l>r&&ne[l-1]>=r)return -n;
    return 2*(sgt.query(0,n,1,l-1,r-1,{1,0}).second-1)+1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    a[0]=0,a[n+1]=0;
    ne[n+1]=n+1;
    rebuild(0,n);
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        a[x]=y;
        rebuild(max(0,x-B),x);
        int l,r;
        cin>>l>>r;
        ++l;
        int ans=query(l,r);
        int pr=r,su=l;
        ll s=0;
        for(int i=l;i<r;++i){
            s+=a[i];
            if(s>a[i+1]){
                pr=i;
                break;
            }
        }
        s=0;
        for(int i=r;i>l;--i){
            s+=a[i];
            if(s>a[i-1]){
                su=i;
                break;
            }
        }
        ans=max({ans,query(pr+1,r)+1,query(l,su-1)+1,query(pr+1,su-1)+2});
        cout<<ans<<'\n';
    }
    return 0;
}