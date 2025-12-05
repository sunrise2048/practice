#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=5e4+5;
const ll inf=1e16;
int n,q;
int a[N];
ll s[N];
ll st_mx[N][16],st_mn[N][16];
int lg[N];
inline ll get_mx(int l,int r){
    if(l>r)return -inf;
    int k=lg[r-l+1];
    return max(st_mx[l][k],st_mx[r-(1<<k)+1][k]);
}
inline ll get_mn(int l,int r){
    if(l>r)return inf;
    int k=lg[r-l+1];
    return min(st_mn[l][k],st_mn[r-(1<<k)+1][k]);
}
int L,R;
ll ans[N];
void solve(int l,int r){
    if(l>r)return;
    const int slen=r-l+1;
    const int mid=l+r>>1;
    if(slen<L)return;
    if(l==r){
        ans[l]=max(ans[l],(ll)a[l]);
        return;
    }
    ll las=-inf;
    for(int i=max(l,mid+1-R+1);i<=mid;++i){
        ll mx=get_mx(max(mid+1,i+L-1),min(r,i+R-1))-s[i-1];
        if(las<mx)las=mx;
        if(ans[i]<las)ans[i]=las;
    }
    las=-inf;
    for(int i=min(r,mid+R-1);i>mid;--i){
        ll mx=s[i]-get_mn(max(l,i-R+1)-1,min(mid,i-L+1)-1);
        if(las<mx)las=mx;
        if(ans[i]<las)ans[i]=las;
    }
    solve(l,mid);solve(mid+1,r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }
    for(int i=0;i<=n;++i){
        st_mx[i][0]=st_mn[i][0]=s[i];
    }
    for(int i=2;i<=n+1;++i)lg[i]=lg[i>>1]+1;
    for(int j=1;j<16;++j){
        for(int i=0;i+(1<<j)-1<=n;++i){
            st_mx[i][j]=max(st_mx[i][j-1],st_mx[i+(1<<j-1)][j-1]);
            st_mn[i][j]=min(st_mn[i][j-1],st_mn[i+(1<<j-1)][j-1]);
        }
    }
    cin>>q;
    while(q--){
        cin>>L>>R;
        memset(ans,~0x3f,sizeof(ans));
        solve(1,n);
        ull s=0;
        for(int i=1;i<=n;++i){
            s^=(ull)i*ans[i];
        }
        cout<<s<<'\n';
    }
    return 0;
}