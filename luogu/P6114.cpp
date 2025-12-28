#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e6+5;
string s;
int n;
int ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>s;
    n=s.size();
    s="0"+s;
    int i=1;
    while(i<=n){
        int j=i,k=i+1;
        while(k<=n&&s[j]<=s[k]){
            if(s[j]<s[k])j=i;
            else ++j;
            ++k;
        }
        while(i<=j){
            ans^=i+k-j-1;
            i+=k-j;
        }
    }
    cout<<ans<<'\n';
    return 0;
}