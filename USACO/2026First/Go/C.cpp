#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int mod=1e9+7;
int n,d;
pair<int,int> a[N];
ll f[N];
ll s1[N],s2[N];
ll er[N],ne[N];
int cn0[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>d;
    er[0]=1;ne[0]=1;
    for(int i=1;i<=n;++i){
        er[i]=er[i-1]*2%mod;
        ne[i]=ne[i-1]*((mod+1)/2)%mod;
        cin>>a[i].first>>a[i].second;
        cn0[i]=cn0[i-1];
        if(a[i].second==0){
            cn0[i]++;
        }
    }
    for(int i=1;i<=n;++i){
        s1[i]=s1[i-1];
        s2[i]=s2[i-1];
        if(a[i].second==0)continue;
        auto it=lower_bound(a+1,a+n+1,make_pair(a[i].first-d,0))-a;
        f[i]=((s2[i-1]-s2[it-1]+mod)*er[cn0[i]]+s1[it-1]+1)%mod;
        s2[i]=(s2[i]+f[i]*ne[cn0[i]])%mod;
        it=lower_bound(a+1,a+n+1,make_pair(a[i].first+d+1,0))-a-1;
        s1[i]=(s1[i]+f[i]*er[cn0[it]-cn0[i]])%mod;
    }
    cout<<s1[n];
    return 0;
}