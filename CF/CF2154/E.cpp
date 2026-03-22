#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
ll a[N];
ll s[N];
ll ans;
ll calc(int x,int len){
    ll sum=s[n]-s[min((ll)x-1,(ll)len*k)]+a[x]*min((ll)x-1,(ll)len*k)+len*a[x]-(s[x+len]-s[x]);
    ans=max(ans,sum);
    return sum;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
        ans=s[n];
        for(int i=2;i<n;++i){
            int l=0,r=min(i-1,n-i);
            ans=max(ans,calc(i,r));
            while(l<r-1){
                int mid=l+r>>1;
                if(calc(i,mid)>calc(i,mid+1)){
                    r=mid;
                }
                else{
                    l=mid+1;
                }
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}