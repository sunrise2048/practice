#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e6+5;
int T;
int n,q;
ll s1,s2;
int th[N];
int s[N],ts[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        memset(th,0,sizeof(int)*(n+1));
        memset(s,0,sizeof(int)*(n+1));
        memset(ts,0,sizeof(int)*(n+1));
        s1=s2=0;
        while(q--){
            int x,y;
            cin>>x>>y;
            th[x]++;
            s1+=ts[th[x]];
            ts[th[x]]++;
            s2+=s[y];
            s[y]++;
            if(s1==s2)cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}