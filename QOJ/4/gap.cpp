#include"gap.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll lim=1e18;
ll findGap(int c,int n){
	if(c==1){
		vector<ll> a(n);
		ll x=0,y=lim+1;
		for(int i=0;i<n;++i){
			if(n-i-1<i)break;
			MinMax(x+1,y-1,&a[i],&a[n-i-1]);
			x=a[i],y=a[n-i-1];
		}
		ll ans=a[1]-a[0];
		for(int i=1;i+1<n;++i)ans=max(ans,a[i+1]-a[i]);
		return ans;
	}
	ll a1,an;
	MinMax(0,lim,&a1,&an);
	ll d=(an-a1)/(n-1);
	ll ans=d;
	ll ls=a1,be=a1;
	while(be<=an){
		ll x,y;
		MinMax(be,min(be+d,an),&x,&y);
		if(x!=-1){
			ans=max(ans,x-ls);
			ls=y;
		}
		be=min(be+d,an)+1;
	}
	return ans;
}
