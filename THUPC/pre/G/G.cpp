#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int T;
int n;
string s;
int cn;
int sm[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        cin>>s;
        for(int i=1;i<=n;++i){
            sm[i]=0;
            sm[i]=s[n-i]-'0';
        }
        cn=0;
        for(int i=n;i>=1;--i){
            int nc=s[n-i]-'0';
            if(nc==0)continue;
            if(cn+1<i){
                ++cn;
                sm[cn]++;
                sm[i]--;
            }
        }
        for(int i=1;i<=n;++i){
            if(sm[i]>1){
                sm[i]-=2;
                sm[i+1]++;
            }
        }
        bool fl=0;
        for(int i=n;i;--i){
            if(sm[i])fl=1;
            if(fl)cout<<sm[i];
        }
        if(!fl)cout<<0;
        cout<<'\n';
    }
    return 0;
}