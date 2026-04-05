#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
int a[N],b[N];
int t[N];
bool sol(){
    memset(t,0,sizeof(int)*(n+1));
    for(int i=1;i<=k;++i){
        t[a[i]]++;
        if(b[i]!=-1)t[b[i]]--;
    }
    for(int i=1;i<=n;++i){
        if(t[i]<0)return 0;
    }
    for(int i=k+1;i<=n;++i){
        int ls=a[i-k];
        int nw=a[i];
        t[ls]--;t[nw]++;
        if(ls!=nw){
            if(b[i-k]!=-1&&b[i-k]!=ls)return 0;
            if(b[i]==-1)b[i]=nw;
            if(b[i]!=nw)return 0;
            if(b[i-k]!=-1)t[ls]++;
            if(t[ls]<0)return 0;
            t[nw]--;
            continue;
        }
        if(b[i-k]!=-1){
            if(b[i]==-1)b[i]=b[i-k];
            if(b[i]!=b[i-k])return 0;
        }
        else if(b[i]!=-1){
            if(t[b[i]]==0)return 0;
            t[b[i]]--;
        }
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>b[i];
        if(sol())cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}