#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const ll inf=2e9;
int T;
int n;
int a[N];
int b[N];
int ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        ans=inf;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            b[i]=a[i];
        }
        sort(b+1,b+n+1);
        for(int i=1;i<=n;++i){
            if(a[i]==b[i])continue;
            ans=min(ans,max(b[n]-a[i],a[i]-b[1]));
        }
        if(ans==inf)ans=-1;
        cout<<ans<<'\n';
    }
    return 0;
}