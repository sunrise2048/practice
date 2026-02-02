#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const ll inf=1e17;
int n;
struct node{
    int val,op;
    int id;
}nd[N<<1];
int las[N];
struct zy{
    pair<int,ll> a[4];
    zy operator+(const zy& y)const{
        zy as;
        for(int i:{0,1,2,3}){
            as.a[i].first=y.a[a[i].first].first;
            as.a[i].second=a[i].second+y.a[a[i].first].second;
        }
        return as;
    }
}t[N<<3];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void build(int l,int r,int k){
    for(int op:{0,1,2,3})t[k].a[op]={op,0};
    if(l==r)return;
    build(l,mid,ls);build(mid+1,r,rs);
}
void update(int l,int r,int k,int x,zy& d){
    if(l==r){
        t[k]=d;
        return;
    }
    if(x<=mid)update(l,mid,ls,x,d);
    else update(mid+1,r,rs,x,d);
    t[k]=t[ls]+t[rs];
}
zy query(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y)return t[k];
    if(y<=mid)return query(l,mid,ls,x,y);
    if(x>mid)return query(mid+1,r,rs,x,y);
    return query(l,mid,ls,x,y)+query(mid+1,r,rs,x,y);
}
#undef mid
#undef rs
#undef ls
vector<ll> mx;
vector<ll> f[N<<1];
vector<ll> fh(vector<ll> f,zy z){
    vector<ll> as(4,inf);
    for(int i=0;i<4;++i){
        as[z.a[i].first]=min(as[z.a[i].first],f[i]+z.a[i].second);
    }
    return as;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>nd[i].val;
        nd[i].id=i;
    }
    for(int i=1;i<=n;++i){
        cin>>nd[i+n].val;
        nd[i+n].op=1;
        nd[i+n].id=i;
    }
    sort(nd+1,nd+2*n+1,[](const node& x,const node& y){
        return x.val>y.val;
    });
    build(1,2*n,1);
    mx.resize(4,inf);
    mx[0]=0;
    f[0]=mx;
    for(int i=1;i<=2*n;++i){
        auto [val,op,id]=nd[i];
        if(las[id]){
            zy nz;
            for(int j=0;j<4;++j){
                nz.a[j].first=j^(1<<op);
                if(!(j&(1<<op)))nz.a[j].second=val;
                else nz.a[j].second=0;
            }
            mx=fh(mx,nz);
            update(1,2*n,1,i,nz);
            vector<ll> nf=f[las[id]];
            nf=fh(nf,query(1,2*n,1,las[id],i-1));
            for(int j=0;j<4;++j)mx[j]=min(mx[j],nf[j]);
            f[i]=mx;
        }
        else{
            las[id]=i;
            zy nz;
            for(int j=0;j<4;++j){
                nz.a[j].first=j^(1<<op);
                if(!(j&(1<<op)))nz.a[j].second=val;
                else nz.a[j].second=0;
            }
            f[i]=fh(mx,nz);
        }
    }
    cout<<min({f[2*n][0],f[2*n][1],f[2*n][2],f[2*n][3]})<<'\n';
    return 0;
}