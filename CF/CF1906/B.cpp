#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N],b[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        int cna=0;
        for(int i=1;i<=n;++i){
            char c;
            cin>>c;a[i]=c-'0';
            a[i]^=a[i-1];cna+=a[i];
        }
        int cnb=0;
        for(int i=1;i<=n;++i){
            char c;
            cin>>c;b[i]=c-'0';
            b[i]^=b[i-1];cnb+=b[i];
        }
        if(min(cna,n-cna+1)==min(cnb,n-cnb+1))cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}