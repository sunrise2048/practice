#include<bits/stdc++.h>
using namespace std;
#define il inline
typedef long long ll;
const int mod=1e9+7;
int n;
ll x[60];
ll z[60];
bool b[60];
il bool insert(ll X){
    ll nz=0;
	for(int i=59;i>=0;i--){
		if(!((X>>i)&1))continue;
		if(x[i]){
            X^=x[i];
            nz^=z[i];
        }
		else{
			x[i]=X;
            z[i]=nz|(1ll<<i);
			return 1;
		}
	}
	return 0;
}
il void check(ll X){
    ll nz=0;
	for(int i=59;i>=0;i--){
		if(!((X>>i)&1))continue;
		if(x[i]){
            X^=x[i];
            nz^=z[i];
        }
	}
    for(int i=0;i<60;++i){
        if(nz&(1ll<<i))b[i]=1;
    }
}
int pw[200001];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	int cnt=0;
	pw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=(pw[i-1]+pw[i-1])%mod;
		ll a;
		cin>>a;
		if(!insert(a))cnt++,check(a);
		int ans=pw[i];
		if(cnt)ans=(ans+1ll*(mod-cnt)*pw[cnt-1])%mod;
		for(int i=59;i>=0;i--){
			if(!x[i])continue;
			if(b[i])ans=(ans+mod-pw[cnt-1])%mod;
			else ans=(ans+mod-pw[cnt])%mod;
		}
		cout<<ans<<'\n';
	}
	return 0;
}