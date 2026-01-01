#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
int a[N];
vector<int> h[N];
int cn;
bool vis[N];
vector<pair<int,int>> op;
int swp(int no){
    while(!vis[a[no]]){
        op.emplace_back(no,a[no]);
        swap(a[no],a[a[no]]);
    }
    return no;
}
void print(){
    cout<<op.size()<<'\n';
    for(auto [x,y]:op){
        cout<<x<<' '<<y<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        if(vis[i])continue;
        ++cn;
        int no=a[i];
        h[cn].push_back(i);
        while(no!=i){
            vis[no]=1;
            h[cn].push_back(no);
            no=a[no];
        }
    }
    if(cn==1){
        int x=h[1][0],y=h[1][1];
        op.emplace_back(x,y);
        swap(a[x],a[y]);
        if(a[y]==y)swap(x,y);
        while(a[x]!=x){
            op.emplace_back(x,a[x]);
            swap(a[x],a[a[x]]);
        }
        while(a[a[y]]!=y){
            op.emplace_back(y,a[y]);
            swap(a[y],a[a[y]]);
        }
        int z=a[y];
        op.emplace_back(x,z);
        op.emplace_back(y,z);
        op.emplace_back(x,y);
        print();
        return 0;
    }
    memset(vis,0,sizeof(vis));
    while(cn>2){
        if(h[cn].size()==1){
            --cn;
            continue;
        }
        vis[h[cn].back()]=1;
        vis[h[cn-1].back()]=1;
        op.emplace_back(h[cn].back(),h[cn-1].back());
        swap(a[h[cn].back()],a[h[cn-1].back()]);
        int x=swp(h[cn].back()),y=swp(h[cn-1].back());
        cn-=2;
        op.emplace_back(x,y);
    }
    if(cn){
        h[2].resize(1);
        vis[h[2].back()]=1;
        vis[h[1].back()]=1;
        op.emplace_back(h[2].back(),h[1].back());
        swap(a[h[2].back()],a[h[1].back()]);
        int x=swp(h[2].back()),y=swp(h[1].back());
        op.emplace_back(x,y);
    }
    print();
    return 0;
}