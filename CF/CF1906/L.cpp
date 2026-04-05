#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
int n,k;
int main(){
    cin>>n>>k;
    if(k<n/2||k==n){
        cout<<"-1\n";
        return 0;
    }
    int cn=k-(n/2);
    for(int i=1;i<=cn/2;++i)cout<<"()";
    int len=(n-cn*2)/2;
    for(int i=1;i<=len;++i)cout<<"(";
    for(int i=1;i<=len;++i)cout<<")";
    for(int i=1;i<=(cn+1)/2;++i)cout<<"()";
    return 0;
}