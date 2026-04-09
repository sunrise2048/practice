#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using I128=__int128;
const int N=1e5+5;
const ll mod=(ll)1e18+3;
int n,m,k;
vector<char> c[N];
ll val[N],sum;
ll t[N][26];
mt19937_64 mt(time(0));
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        c[i].resize(m);
        val[i]=mt()%mod;
        sum=(sum+val[i])%mod;
        for(int j=0;j<m;++j){
            cin>>c[i][j];
            t[j][c[i][j]-'A']=(t[j][c[i][j]-'A']+val[i])%mod;
        }
    }
    for(int i=1;i<=n;++i){
        ll s=(mod-(I128)m*val[i]%mod)%mod;
        for(int j=0;j<m;++j){
            s=(s+t[j][c[i][j]-'A'])%mod;
        }
        if(s==(I128)(sum-val[i]+mod)%mod*(m-k)%mod){
            cout<<i<<'\n';
            return 0;
        }
    }
    return 0;
}