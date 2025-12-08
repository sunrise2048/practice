#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
ll n,d,l;
ll calc0(){
    ll zs=l/d;
    zs=zs*n;
    if(l%d==0&&d!=n)zs++;
    else if(l%d<=n)zs+=l%d;
    else zs+=n+1;
    return zs-n;
}
ll calc1(){
    ll R=l-1;
    ll L=l-n;
    return (R+L)*(R-L+1)/2-n*(n+1)/2+1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld%lld",&n,&d,&l);
        printf("%lld %lld\n",calc0(),calc1());
    }
    return 0;
}