#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
int T;
int n,k;
int a[N];
int la[N];
vector<int> ne[N];
vector<pair<int,int>> ve;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        for(int i=1;i<=k;++i){
            ne[i].clear();
            ne[i].push_back(2*n);
        }
        for(int i=n;i;--i){
            ne[a[i]].push_back(i);
        }
        fill(la+1,la+k+1,-n);
        int ans=n*n;
        const int mid=(k+1)/2;
        for(int i=1;i<=n;++i){
            la[a[i]]=i;
            ne[a[i]].pop_back();
            ve.clear();
            for(int j=1;j<=k;++j){
                int l=i-la[j],r=ne[j].back()-i;
                ve.emplace_back(l-r,j);
            }
            sort(ve.begin(),ve.end());
            int s=0;
            for(int j=0;j<mid;++j){
                int c=ve[j].second;
                s+=i-la[c];
            }
            for(int j=mid;j<ve.size();++j){
                int c=ve[j].second;
                s+=ne[c].back()-i;
            }
            s-=mid*(mid-1)/2+(k-mid)*(k-mid+1)/2;
            ans=min(ans,s);
        }
        cout<<ans<<'\n';
    }
    return 0;
}