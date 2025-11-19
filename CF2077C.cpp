#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
ll ny4;
int T;
int n,q;
string s;
ll cn0,cn1;
ll er,er1;
ll ksm(ll x,int y=mod-2){
    if (y<0) return 0;
    ll an=1;
    while (y) {
        if (y&1) an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll calc(){
    return ny4*((cn0*(cn0+1)%mod*er1%mod+cn1*(cn1+1)%mod*er1%mod-cn0*cn1%mod*er%mod-er+2*mod)%mod)%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    ny4=ksm(4);
    while (T--) {
        cin>>n>>q;
        cin>>s;
        cn0=cn1=0;
        er=ksm(2,n-1);er1=ksm(2,n-2);
        for (char c:s) {
            if (c=='0')++cn0;
            else ++cn1;
        }
        while (q--) {
            int id;
            cin>>id;--id;
            if (s[id]=='0') {
                ++cn1;--cn0;
                s[id]='1';
            }
            else {
                ++cn0;--cn1;
                s[id]='0';
            }
            if (n==1) {
                cout<<"0\n";
                continue;
            }
            //cout<<cn0<<' '<<cn1<<'\n';
            cout<<calc()<<'\n';
        }
    }
    return 0;
}