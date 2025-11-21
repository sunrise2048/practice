#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n,k;
ll a[N];
bool ch(int x) {
    ll sum=0;
    for (int i=1;i<=n;++i) {
        if (a[i]<=x) sum+=x-a[i];
        else if(a[i]>=x+k) sum-=a[i]-(x+k);
    }
    return sum>=0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n>>k;
        for (int i=1;i<=n;++i) {
            cin>>a[i];
        }
        ll l=0,r=1e6+5;
        while (l<r-1) {
            ll mid=l+r>>1;
            if (ch(mid)) r=mid;
            else l=mid;
        }
        ll sl=0,sr=0,sum=0;
        for (int i=1;i<=n;++i) {
            if (a[i]<=r) {
                sum+=r*(r+1)/2;
                sl+=r-a[i];
            }
            else if(a[i]>=r+k) {
                sum+=(r+k)*(r+k+1)/2;
                sr+=a[i]-(r+k);
            }
            else sum+=a[i]*(a[i]+1)/2;
        }
        sum+=k*sr-r*(sl-sr);
        cout<<sum<<'\n';
    }
    return 0;
}