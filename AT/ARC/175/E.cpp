#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
int n,k;
struct node{
    int x,y,z;
};
vector<node> v1,v3;
bool vis[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    bool fl=0;
    if(n%3&&k%3==2){
        v1.push_back({1,1,1});
        vis[1][1]=1;
        fl=1;
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            int k=(2*n-i-j)%n;
            if(vis[i][j]||vis[j][k]||vis[k][i])continue;
            vis[i][j]=vis[j][k]=vis[k][i]=1;
            if(i==j&&j==k)v1.push_back({i,j,k});
            else if(!fl||i!=1||j!=1)v3.push_back({i,j,k});
        }
    }
    while(k>=3&&!v3.empty()){
        auto [x,y,z]=v3.back();v3.pop_back();
        cout<<x<<' '<<y<<' '<<z<<'\n';
        cout<<y<<' '<<z<<' '<<x<<'\n';
        cout<<z<<' '<<x<<' '<<y<<'\n';
        k-=3;
    }
    while(k--){
        auto [x,y,z]=v1.back();v1.pop_back();
        cout<<x<<' '<<y<<' '<<z<<'\n';
    }
    return 0;
}