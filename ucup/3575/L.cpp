#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=998244353;
int n;
char c[N];
set<int> st[4];
ll ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>c[i];
        if(c[i]=='K')st[0].insert(i);
        else if(c[i]=='U')st[1].insert(i);
        else if(c[i]=='P')st[2].insert(i);
        else if(c[i]=='C')st[3].insert(i);
    }
    while(true){
        ll bs=1;
        int la=n+1;
        for(int i=3;i>=0;--i){
            while(!st[i].empty()&&*st[i].rbegin()>la){
                st[i].erase(*st[i].rbegin());
            }
            if(st[i].empty()){
                bs=0;
                break;
            }
            la=*st[i].rbegin();st[i].erase(la);
            bs=bs*la%mod;
        }
        if(!bs)break;
        ans=(ans+bs)%mod;
    }
    cout<<ans;
    return 0;
}