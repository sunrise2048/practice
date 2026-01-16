#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e7+5;
int n,m;
string s,t;
int lcp,lcs;
int kmp[N];
ll ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    cin>>s>>t;
    s="0"+s;t="0"+t;
    while(lcp!=n&&s[lcp+1]==t[lcp+1])++lcp;
    while(lcs!=n&&s[n-lcs]==t[m-lcs])++lcs;
    if(lcp+lcs<n){
        cout<<"0\n";
        return 0;
    }
    const int len=m-n;
    int l=lcp+1,r=lcp+len;
    kmp[l]=l-1;
    int j=l-1;
    for(int i=l+1;i<=r;++i){
        while(j>=l&&t[i]!=t[j+1])j=kmp[j];
        if(t[i]==t[j+1]){
            ++j;
        }
        kmp[i]=j;
    }
    int p=r-kmp[r];
    if(len%p)p=len;
    l=n-lcs+1;
    r=lcp;
    int lm=min(len,r-l+1);
    for(int i=p;i<=lm;i+=p){
        if(len%i)continue;
        ans+=(r-l+1)-i+1;
    }
    cout<<ans<<'\n';
    return 0;
}