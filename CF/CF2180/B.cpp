#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e3+5;
int T;
int n;
string s[N];
string ts;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        ts.clear();
        for(int i=1;i<=n;++i){
            cin>>s[i];
            ts=min(ts+s[i],s[i]+ts);
        }
        cout<<ts<<'\n';
    }
    return 0;
}