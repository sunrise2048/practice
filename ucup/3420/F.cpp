#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,q;
int s[N];
int lg[N];
int st[18][N];
int gt(int l,int r){
    int k=lg[r-l+1];
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        char c;
        cin>>c;
        s[i]=s[i-1];
        if(c=='(')++s[i];
        else --s[i];
        st[0][i]=s[i];
    }
    for(int i=2;i<=n+1;++i)lg[i]=lg[i>>1]+1;
    for(int j=1;j<18;++j){
        for(int i=0;i+(1<<j)-1<=n;++i){
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
        }
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        if(s[r]-s[l-1]!=0){
            cout<<"Finite\n";
            continue;
        }
        int mi=gt(l-1,r)-s[l-1];
        int mx=s[r]-gt(l-1,r);
        if(mx+mi<0)cout<<"Finite\n";
        else cout<<"Infinite\n";
    }
    return 0;
}