#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n;
int a[N];
int s[N][2];
bool ch(int x){
    int mis=0;
    for(int i=2;i<=n;i+=2){
        if(s[n][0]-s[i-1][0]+s[i][1]-mis>=x){
            mis=min(mis,s[i][1]-s[i][0]);
            if(s[i][0]+s[n][1]-s[i][1]>=x)return 1;
        }
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    if(n%2==0){
        vector<int> s(2);
        for(int i=1;i<=n;++i){
            s[i&1]+=a[i];
        }
        cout<<max(s[0],s[1])<<' '<<min(s[0],s[1])<<'\n';
        return 0;
    }
    int l=0,r=1e9;
    for(int i=1;i<=n;++i){
        s[i][0]=s[i-1][0],s[i][1]=s[i-1][1];
        s[i][i&1]+=a[i];
    }
    l=s[n][1];
    while(l<r-1){
        int mid=l+r>>1;
        if(ch(mid))l=mid;
        else r=mid;
    }
    cout<<l<<' '<<s[n][1]+s[n][0]-l<<'\n';
    return 0;
}