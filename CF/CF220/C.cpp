#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n;
int a[N];
int t[N];
vector<ll> bz[N],bf[N],ez[N],ef[N];
multiset<ll> xz,xf;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        t[a[i]]=i;
    }
    for(int i=1;i<=n;++i){
        int nb;
        cin>>nb;
        int ida=t[nb];
        if(ida>=i){
            int d=i-1;
            int dd=d+(n-ida+1);
            bz[0].push_back(ida-i);
            ez[d+1].push_back(ida-i);
            bf[d+1].push_back(n-ida+(d+1));
            ef[dd+1].push_back(n-ida+(d+1));
            bz[dd+1].push_back(-dd);
        }
        else{
            int d=i-ida;
            int dd=i-1;
            bf[0].push_back(i-ida);
            ef[d+1].push_back(i-ida);
            bz[d+1].push_back(-d);
            ez[dd+1].push_back(-d);
            bf[dd+1].push_back(n-ida+(dd+1));
        }
    }
    for(int i=0;i<n;++i){
        for(ll val:bz[i])xz.insert(val);
        for(ll val:ez[i])xz.erase(xz.find(val));
        for(ll val:bf[i])xf.insert(val);
        for(ll val:ef[i])xf.erase(xf.find(val));
        ll ans=n;
        if(xz.size())ans=min(ans,i+(*xz.begin()));
        if(xf.size())ans=min(ans,-i+(*xf.begin()));
        cout<<ans<<'\n';
    }
    return 0;
}