#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=998244353;
int n;
ll a[N];
vector<int> st;
bool ch(int z){
    int x=st[st.size()-2],y=st.back();
    return (a[y]-a[x])*(z-y)-(a[z]-a[y])*(y-x)<=0;
}
ll sum;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        while(st.size()>1&&ch(i))st.pop_back();
        st.push_back(i);
    }
    sum=(a[1]+a[n])%mod;
    for(int i=0;i+1<st.size();++i){
        int x=st[i],y=st[i+1];
        sum=(sum+(a[x]+a[y])*(y-x))%mod;
    }
    cout<<sum*ksm(2*n)%mod<<'\n';
    return 0;
}