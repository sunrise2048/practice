#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4e5+5;
int T;
int n;
int a[N],st[N][19];
int lg[N];
int get_gcd(int l,int r){
    int k=lg[r-l+1];
    return __gcd(st[l][k],st[r-(1<<k)+1][k]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;++i) {
            cin>>a[i];
        }
        for (int i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
        for (int i=1;i<n;++i) {
            int nv=abs(a[i]-a[i+1]);
            while (nv&&nv%2==0) nv/=2;
            st[i][0]=nv;
        }
        for (int j=1;j<19;++j) {
            for (int i=1;i+(1<<j)-1<n;++i) {
                st[i][j]=__gcd(st[i][j-1],st[i+(1<<j-1)][j-1]);
            }
        }
        ll ans=0;
        for (int l=1;l<=n;++l) {
            ++ans;
            int rl=l,rr=n+1;
            while (rl<rr-1) {
                int mid=(rl+rr)>>1;
                if (get_gcd(l,mid-1)==1) rr=mid;
                else rl=mid;
            }
            ans+=(n-rr+1);
            rl=l,rr=n+1;
            while (rl<rr-1) {
                int mid=(rl+rr)>>1;
                if (get_gcd(l,mid-1)==0) rl=mid;
                else rr=mid;
            }
            ans+=(rl-l);
        }
        cout<<ans<<'\n';
    }
    return 0;
}