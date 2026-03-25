#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
ll l,r;
int a[N<<1],sa[N<<1];
int xa[N<<1];
ll get_sum(ll r){
    if(r<=2*n+1)return sa[r];
    ll sum=get_sum(n+2*((r-2*n-2)/4)+min(2ll,(r-2*n-2)%4+1))-sa[n];
    if(xa[n])sum=r-2*n-1-sum;
    return sum+sa[2*n+1];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>l>>r;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        if(n%2==0){
            ++n;
            a[n]=0;
            for(int i=1;i<=n/2;++i)a[n]^=a[i];
        }
        for(int i=1;i<=n;++i){
            sa[i]=sa[i-1]+a[i];
            xa[i]=xa[i-1]^a[i];
        }
        for(int i=n+1;i<=2*n+1;++i){
            a[i]=xa[i/2];
            xa[i]=xa[i-1]^a[i];
            sa[i]=sa[i-1]+a[i];
        }
        cout<<get_sum(r)-get_sum(l-1)<<'\n';
    }
    return 0;
}