#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2.5e5+5;
const ll inf=4e9+5;
int n,k;
pair<ll,ll> a[N];
multiset<ll> ans;
set<pair<ll,ll>> sty;
bool ch(ll x,bool fl=0){
    int no=1;
    int cn=0;
    sty.clear();
    for(int i=1;i<=n;++i){
        while(no<i&&a[no].first<a[i].first-x){
            sty.erase({a[no].second,a[no].first});
            ++no;
        }
        auto it=sty.lower_bound({a[i].second,0}),ti=it;
        while(it!=sty.end()&&it->first<=a[i].second+x){
            ++cn;
            if(cn==k)return 1;
            if(fl)ans.insert(max(it->first-a[i].second,abs(it->second-a[i].first)));
            ++it;
        }
        while(ti!=sty.begin()&&prev(ti)->first>=a[i].second-x){
            --ti;
            ++cn;
            if(cn==k)return 1;
            if(fl)ans.insert(max(a[i].second-ti->first,abs(ti->second-a[i].first)));
        }
        sty.emplace(a[i].second,a[i].first);
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        int x,y;
        cin>>x>>y;
        a[i]={x+y,x-y};
    }
    sort(a+1,a+n+1);
    ll l=0,r=inf;
    while(l<r-1){
        ll mid=(l+r>>1);
        if(ch(mid))r=mid;
        else l=mid;
    }
    ch(r-1,1);
    for(ll no:ans){
        cout<<no<<'\n';
    }
    int cn=k-ans.size();
    while(cn--){
        cout<<r<<'\n';
    }
    return 0;
}