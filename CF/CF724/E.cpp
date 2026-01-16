#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e4+5;
int n;
ll c;
ll a[N];
int p[N];
ll ans,sum;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>c;
    for(int i=1;i<=n;++i){
        cin>>p[i];
        sum+=p[i];
    }
    for(int i=1;i<=n;++i){
        int s;
        cin>>s;
        a[i]=c*(n-i)+s-p[i];
    }
    ans=sum;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        sum+=a[i]-c*(i-1);
        ans=min(ans,sum);
    }
    cout<<ans<<'\n';
    return 0;
}