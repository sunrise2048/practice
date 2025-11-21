#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T;
int n;
int a[N];
int t[N<<2],lz[N<<2];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void pushup(int k){t[k]=max(t[ls],t[rs]);}
void pushdown(int k){
    if (!lz[k]) return;
    t[ls]+=lz[k];
    t[rs]+=lz[k];
    lz[ls]+=lz[k];
    lz[rs]+=lz[k];
    lz[k]=0;
}
void update(int l,int r,int k,int x,int y,int d){
    if (x<=l&&r<=y) {
        t[k]+=d;
        lz[k]+=d;
        return;
    }
    pushdown(k);
    if (x<=mid) update(l,mid,ls,x,y,d);
    if (y>mid) update(mid+1,r,rs,x,y,d);
    pushup(k);
}
void update_c(int l,int r,int k,int x){
    if (l==r) {
        t[k]=0;
        return;
    }
    pushdown(k);
    if (x<=mid) update_c(l,mid,ls,x);
    else update_c(mid+1,r,rs,x);
    pushup(k);
}
#undef mid
#undef rs
#undef ls
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        memset(t,0,sizeof(int)*(n<<2));
        memset(lz,0,sizeof(int)*(n<<2));
        for (int i=1;i<=n;++i) {
            cin>>a[i];
            update_c(0,n,1,a[i]);
            if (a[i]) update(0,n,1,0,a[i]-1,1);
            cout<<t[1]<<' ';
        }cout<<'\n';
    }
    return 0;
}