#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
ll a,b,n,s;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a>>b>>n>>s;
        if(s%a<s%b)swap(a,b);
        if(s%a){
            cout<<"YES\n";
            for(int i=1;i<=n;++i)cout<<a<<' ';
            cout<<'\n';
            continue;
        }
        if(a>b)swap(a,b);
        if(s==b){
            if(n>=s/a){
                cout<<"NO\n";
                continue;
            }
            cout<<"YES\n";
            for(int i=1;i<=n;++i)cout<<a<<' ';
            cout<<'\n';
            continue;
        }
        ll gc=__gcd(a,b);
        a/=gc,b/=gc,s/=gc;
        if(a!=1||b!=2){
            cout<<"YES\n";
            ll ns=0;
            for(int i=1;i<=n;++i){
                if(ns+b==s){
                    cout<<a*gc<<' ';
                    ns=0;
                }
                else{
                    ns+=b;
                    cout<<b*gc<<' ';
                }
            }
            cout<<'\n';
            continue;
        }
        if((s/b-1)*2+1<n){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        ll len=s/b-1;
        while(n&&len){
            --n;--len;
            cout<<b*gc<<' ';
        }
        if(n){
            cout<<a*gc<<' ';
            --n;
        }
        len=s/b-1;
        while(n&&len){
            --n;--len;
            cout<<b*gc<<' ';
        }
        cout<<'\n';
    }
    return 0;
}