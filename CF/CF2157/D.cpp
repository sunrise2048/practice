#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
ll l,r;
ll a[N];
ll sa[N];
ll ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>l>>r;
        for(int i=1;i<=n;++i)cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)sa[i]=sa[i-1]+a[i];
        ans=0;
        for(ll k=-n;k<=n;++k){
            ll d=0;
            if(k<0){
                d=sa[n]-sa[n+k];
                int nl=n+k,cn=nl/2;;
                d+=(sa[nl]-sa[nl-cn])-sa[cn];
            }
            else{
                d=-sa[k];
                int nl=n-k,cn=nl/2;;
                d+=(sa[n]-sa[n-cn])-(sa[k+cn]-sa[k]);
            }
            if(k<0)ans=max(ans,k*r+d);
            else ans=max(ans,k*l+d);
        }
        cout<<ans<<'\n';
    }
    return 0;
}