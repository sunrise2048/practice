#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
int a[N];
bool ch1(){
    for(int i=2;i<=n;++i){
        if(a[i-1]>a[i])return 0;
    }
    return 1;
}
map<int,int> mp;
int x,y;
bool ch2(){
    mp.clear();
    for(int i=1;i<=n;++i){
        if(mp.count(k-a[i])){
            x=mp[k-a[i]],y=i;
            return 0;
        }
        mp[a[i]]=i;
    }
    return 1;
}
struct ope{
    int x,y,d;
};
vector<ope> op;
int id[N];
bool vis[N];
void swp(int x,int y){
    op.push_back({1,n,a[1]-a[x]});
    op.push_back({x,n,a[x]-a[y]});
    op.push_back({y,n,a[y]-a[x]});
    a[1]=a[x],a[n]=a[y];
    swap(a[x],a[y]);
}
void dfs(int no){
    if(id[no]==no)return;
    if(vis[id[no]])return;
    swp(no,id[no]);
    vis[no]=1;
    dfs(id[no]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i)cin>>a[i];
        if(ch1()){
            cout<<"0\n";
            continue;
        }
        if(ch2()){
            cout<<"-1\n";
            continue;
        }
        op.clear();
        if(x!=1){
            op.push_back({x,y,a[x]-a[1]});
            a[x]=a[1],a[y]=k-a[1];
            x=1;
        }
        if(y!=n){
            op.push_back({y,x,a[y]-a[n]});
            a[y]=a[n],a[x]=k-a[n];
            y=n;
        }
        iota(id+1,id+n+1,1);
        sort(id+2,id+n,[](const int& x,const int& y){
            return a[x]<a[y];
        });
        memset(vis,0,sizeof(bool)*(n+1));
        for(int i=2;i<n;++i){
            if(vis[i])continue;
            dfs(i);
        }
        op.push_back({1,n,a[1]});
        cout<<op.size()<<'\n';
        for(auto [x,y,d]:op){
            cout<<x<<' '<<y<<' '<<d<<'\n';
        }
    }
    return 0;
}