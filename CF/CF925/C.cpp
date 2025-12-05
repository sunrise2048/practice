#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n;
vector<ll> ve[60];
ll s;
vector<ll> vl;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        ll v;
        cin>>v;
        for(int j=59;j>=0;--j){
            if(v&(1ll<<j)){
                ve[j].push_back(v);
                break;
            }
        }
    }
    while(vl.size()!=n){
        bool fl=0;
        for(int i=0;i<60;++i){
            if(s&(1ll<<i))continue;
            if(ve[i].empty())continue;
            fl=1;
            s^=ve[i].back();
            vl.push_back(ve[i].back());
            ve[i].pop_back();
            break;
        }
        if(!fl)break;
    }
    if(vl.size()!=n){
        cout<<"No\n";
    }
    else{
        cout<<"Yes\n";
        for(ll no:vl)cout<<no<<' ';
    }
    return 0;
}