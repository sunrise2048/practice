#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
int a[N];
int t[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        memset(t,0,sizeof(int)*(n+1));
        for(int i=1;i<=n;++i){
            cin>>a[i];
            t[a[i]]++;
        }
        int mx=0;
        for(int i=0;i<=n;++i){
            if(!t[i]){
                mx=i;
                break;
            }
        }
        cout<<min(mx,k-1)<<'\n';
    }
    return 0;
}