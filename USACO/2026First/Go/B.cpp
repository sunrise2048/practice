#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m;
int a[N];
vector<int> lis;
int t[N];
int mi[N];
ll sum;
void up(int x){
    while(x<=m){
        t[x]++;
        x+=(x&-x);
    }
}
int qu(int x){
    int s=0;
    while(x){
        s+=t[x];
        x-=(x&-x);
    }
    return s;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        sum=0;
        lis.clear();
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            lis.push_back(a[i]);
        }
        sort(lis.begin(),lis.end());
        lis.erase(unique(lis.begin(),lis.end()),lis.end());
        m=lis.size();
        for(int i=1;i<=n;++i){
            a[i]=lower_bound(lis.begin(),lis.end(),a[i])-lis.begin()+1;
        }
        for(int i=1;i<=n;++i){
            mi[i]=qu(a[i]-1);
            up(a[i]);
        }
        memset(t,0,sizeof(int)*(m+1));
        for(int i=n;i;--i){
            sum+=min(mi[i],qu(a[i]-1));
            up(a[i]);
        }
        memset(t,0,sizeof(int)*(m+1));
        cout<<sum<<'\n';
    }
    return 0;
}