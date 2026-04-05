#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll lm=1e16;
int a,b;
vector<pair<ll,ll>> pr;
void che(ll gc){
    ll lc=a*gc+b;
    if(__gcd(lc,gc)!=gc)return;
    pr.emplace_back(lc,gc);
}
ll ans;
map<ll,ll> ma;
set<ll> st;
void dfs(ll x){
    if(x>lm)return;
    ans^=x;
    st.insert(x);
    for(auto [lc,gc]:pr){
        if(x%gc)continue;
        if(lc%x)continue;
        ll y=lc/x*gc;
        if(st.count(y))continue;
        if(__gcd(x,y)!=gc)continue;
        dfs(y);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>a>>b;
    for(int i=1;i*i<=b;++i){
        if(b%i)continue;
        che(i);
        if(i*i!=b)che(b/i);
    }
    int q;
    cin>>q;
    while(q--){
        ll x;
        st.clear();
        ans=0;
        cin>>x;
        if(ma.count(x)){
            cout<<ma[x]<<'\n';
            continue;
        }
        dfs(x);
        cout<<ans<<'\n';
        for(ll vl:st)ma[vl]=ans;
    }
    return 0;
}