#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=1e9+7;
int n,q;
ll a[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll ans[N];
vector<pair<int,int>> pre[N],suf[N];
ll ny[N];
ll calc(int l,int r){
    return (a[r]-a[l-1]+mod)%mod*(a[r]-a[l-1]+mod)%mod*ny[r-l+1]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    ny[0]=1;
    for(int i=1;i<=n;++i){
        ny[i]=ny[i-1]*i%mod*i%mod;
    }
    ny[n]=ksm(ny[n]);
    for(int i=n;i;--i){
        ll la=ny[i-1];
        ny[i-1]=ny[i]*i%mod*i%mod;
        ny[i]=ny[i]*la%mod;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        a[i]=(a[i-1]+a[i])%mod;
    }
    for(int t=1;t<=q;++t){
        int l,r;
        cin>>l>>r;
        int mx=n/l;
        if(1ll*mx*r<n){
            ans[t]=-1;
            continue;
        }
        if(n%l==0){
            pre[l].emplace_back(n,t);
            continue;
        }
        int md=r-l;
        int ts=(n-mx*l)/md;
        pre[r].emplace_back(ts*r,t);
        int ys=n-mx*l-ts*md;
        if(ys){
            suf[l].emplace_back((mx-ts-1)*l,t);
            int tl=ts*r+1,tr=ts*r+l+ys;
            ans[t]=calc(tl,tr);
        }
        else suf[l].emplace_back((mx-ts)*l,t);
    }
    for(int i=1;i<=n;++i){
        sort(pre[i].begin(),pre[i].end());
        sort(suf[i].begin(),suf[i].end());
        int no=0;
        ll s=0;
        while(no!=pre[i].size()&&pre[i][no].first==0)++no;
        for(int si=i;si<=n;si+=i){
            s=(s+calc(si-i+1,si))%mod;
            while(no!=pre[i].size()&&pre[i][no].first==si){
                ans[pre[i][no].second]=(ans[pre[i][no].second]+s)%mod;
                ++no;
            }
        }
        no=s=0;
        while(no!=suf[i].size()&&suf[i][no].first==0)++no;
        for(int si=i;si<=n;si+=i){
            s=(s+calc(n-si+1,n-si+i))%mod;
            while(no!=suf[i].size()&&suf[i][no].first==si){
                ans[suf[i][no].second]=(ans[suf[i][no].second]+s)%mod;
                ++no;
            }
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}