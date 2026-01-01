#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n,k;
int cn[N];
vector<int> ans,id;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        for(int j=2*i;j<=n;j+=i){
            cn[j]++;
        }
    }
    int s=0;
    for(int i=1;i<=n;++i){
        s+=cn[i];
        if(s>=k){
            n=i;
            break;
        }
    }
    if(s<k){
        cout<<"No\n";
        return 0;
    }
    for(int i=1;i<=n/2;++i){
        ans.push_back(i);
        k-=cn[i];
    }
    for(int i=n/2+1;i<=n;++i){
        id.push_back(i);
    }
    sort(id.begin(),id.end(),[](const int& x,const int& y){
        return cn[x]>cn[y];
    });
    for(int no:id){
        if(k>=cn[no]){
            ans.push_back(no);
            k-=cn[no];
        }
    }
    cout<<"Yes\n";
    cout<<ans.size()<<'\n';
    for(int no:ans)cout<<no<<' ';
    return 0;
}