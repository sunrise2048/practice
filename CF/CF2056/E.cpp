#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int T;
int n,m;
set<pair<int,int>> st;
ll f[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int n=2e5;
    f[0]=1;
    for(int i=1;i<=n;++i)f[i]=f[i-1]*(4*i-2)%mod*ksm(i+1)%mod;
}
ll ans;
void dfs(int l,int r){
    st.erase({l,-r});
    if(l==r)return;
    auto it=st.lower_bound({l,-n});
    int d=0;
    while(it!=st.end()&&it->first<=r){
        ++d;
        auto [x,y]=*it;
        y=-y;
        dfs(x,y);
        it=st.lower_bound({y+1,-n});
    }
    if(d)ans=ans*f[d-1]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>n>>m;
        st.clear();
        for(int i=1;i<=m;++i){
            int l,r;
            cin>>l>>r;
            st.emplace(l,-r);
        }
        st.emplace(1,-n);
        for(int i=1;i<=n;++i)st.emplace(i,-i);
        ans=1;
        dfs(1,n);
        cout<<ans<<'\n';
    }
    return 0;
}