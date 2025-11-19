#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=1e9+7;
int T;
int n;
int a[N];
map<int,int> mp;
int tag;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;++i) cin>>a[i];
        mp.clear();tag=0;
        mp[0]=1;
        for (int i=1;i<=n;++i) {
            ll x=mp[tag],y=mp[tag^a[i]];
            mp[tag]=mp[tag^a[i]]=0;
            tag^=a[i];
            mp[tag]=y;
            mp[tag^a[i]]=(3*x+2*y)%mod;
        }
        ll ans=0;
        for (auto [val,cn]:mp) ans=(ans+cn)%mod;
        cout<<ans<<'\n';
    }
    return 0;
}