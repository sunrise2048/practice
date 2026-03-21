#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int T;
int n;
int a[N],s[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            char c;
            cin>>c;a[i]=c-'0';
            s[i]=s[i-1]+2*a[i]-1;
        }
        if(n==1){
            if(a[1])cout<<"0\n";
            else cout<<"-1\n";
            continue;
        }
        if(s[n]==-n){
            cout<<"-1\n";
            continue;
        }
        if(s[n]>=0){
            cout<<n<<'\n';
            continue;
        }
        int mx=1;
        int ma=0;
        for(int i=1;i<=n;++i){
            ma=max(ma,s[i]);
            mx=max(mx,-(s[i]-ma)-1);
        }
        if(s[n]+mx>=0){
            cout<<n+1<<'\n';
            continue;
        }
        bool fl=0;
        for(int i=1;i<n;++i){
            if(a[i]&&a[i+1]){
                fl=1;
                break;
            }
            if(s[i]>=0||s[n]-s[i]>=0){
                fl=1;
                break;
            }
        }
        if(fl)cout<<n+2<<'\n';
        else cout<<n+3<<'\n';
    }
    return 0;
}