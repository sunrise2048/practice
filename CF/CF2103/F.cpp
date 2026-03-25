#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n,k;
int a[N];
int ans[N];
bool fl[N];
bool vis[17];
int mx[N];
void solve(int l,int r){
    if(l==r)return;
    const int mid=l+r>>1;
    memset(vis,0,sizeof(vis));
    for(int i=mid;i>=l;--i){
        for(int j=0;j<k;++j){
            if((a[i]&(1<<j))&&!vis[j]){
                vis[j]=1;
                fl[i]=1;
            }
        }
        if(i==mid)fl[i]=1;
    }
    for(int i=mid;i>=l;--i){
        if(fl[i]||fl[i+1]||fl[i+2]){
            int s=a[i];
            const int U=(1<<k)-1;
            for(int j=i+1;j<=r;++j){
                s=(U^s)&(U^a[j]);
                if(j>mid){
                    mx[i]=max(mx[i],s);mx[j]=max(mx[j],s);
                }
            }
        }
        else mx[i]=mx[i+2];
    }
    fill(fl+l,fl+mid+1,0);
    for(int i=l;i<=mid;++i){
        mx[i]=max(mx[i],mx[i-1]);
        ans[i]=max(ans[i],mx[i]);
    }
    for(int i=r;i>mid;--i){
        mx[i]=max(mx[i],mx[i+1]);
        ans[i]=max(ans[i],mx[i]);
    }
    fill(mx+l,mx+r+1,0);
    solve(l,mid);solve(mid+1,r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            ans[i]=a[i];
        }
        solve(1,n);
        for(int i=1;i<=n;++i){
            cout<<ans[i]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}