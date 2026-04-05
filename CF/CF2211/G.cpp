#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n;
ll a[N],s[N];
bool fl[N];
bool ch(){
    for(int i=1;i<n;++i){
        if(s[i]*(n-i)<(s[n]-s[i])*i){
            return 1;
        }
        fl[i]=(s[i]*(n-i)==(s[n]-s[i])*i);
    }
    fl[n]=1;
    for(int i=1;i<n;++i){
        if(!fl[i]&&!fl[i+1])return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            s[i]=s[i-1]+a[i];
        }
        if(ch())cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}