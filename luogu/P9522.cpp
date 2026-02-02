#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=1e9+7;
int n,m;
ll f[N][26];
ll s[26];
int cn1[N],cn2[N];
vector<int> era1[N],era2[N];
multiset<int> st1,st2;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int l,r;
        cin>>l>>r;
        if(l<r){
            ++cn1[l];
            era1[r].push_back(l);
        }
        else{
            ++cn2[r];
            era2[l].push_back(r);
        }
    }
    st1.insert(0);st2.insert(0);
    for(int i=0;i<26;++i){
        f[1][i]=1;
    }
    while(cn1[1]--)st1.insert(1);
    while(cn2[1]--)st2.insert(1);
    for(int i=2;i<=n;++i){
        memset(s,0,sizeof(s));
        for(int j=0;j<26;++j){
            f[i][j]=f[i-1][j];
        }
        int la=*st2.rbegin();
        ll sm=0;
        for(int j=0;j<26;++j){
            s[j]=(f[i-1][j]-f[la][j]+mod)%mod;
        }
        for(int j=25;j>=0;--j){
            f[i][j]=(f[i][j]+sm)%mod;
            sm=(sm+s[j])%mod;
        }
        la=*st1.rbegin();
        sm=0;
        for(int j=0;j<26;++j){
            s[j]=(f[i-1][j]-f[la][j]+mod)%mod;
        }
        for(int j=0;j<26;++j){
            f[i][j]=(f[i][j]+sm)%mod;
            sm=(sm+s[j])%mod;
        }
        while(cn1[i]--)st1.insert(i);
        while(cn2[i]--)st2.insert(i);
        for(int j:era1[i])st1.erase(st1.find(j));
        for(int j:era2[i])st2.erase(st2.find(j));
    }
    ll ans=0;
    for(int i=0;i<26;++i)ans=(ans+f[n][i])%mod;
    cout<<ans<<'\n';
    return 0;
}