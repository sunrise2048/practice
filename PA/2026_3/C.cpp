#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
int a[N],b[N],c[N];
int f[N][2];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    n=s.size();
    for(int i=1;i<=n;++i){
        char x=s[i-1];
        a[i]=x-'0';
    }
    cin>>s;
    for(int i=1;i<=n;++i){
        char x=s[i-1];
        b[i]=x-'0';
    }
    cin>>s;
    for(int i=1;i<=n;++i){
        char x=s[i-1];
        c[i]=x-'0';
    }
    ll ans=0;
    for(int i=1;i<=n;++i){
        if((a[i]+b[i])%10==c[i]){
            if((a[i]+b[i])>=10){
                f[i][0]=f[i-1][1];
            }
            else{
                f[i][0]=1+f[i-1][0];
            }
        }
        if((a[i]+b[i]+1)%10==c[i]){
            if((a[i]+b[i]+1)>=10){
                f[i][1]=f[i-1][1];
            }
            else{
                f[i][1]=1+f[i-1][0];
            }
        }
        ans+=f[i][0];
    }
    cout<<ans<<'\n';
    return 0;
}