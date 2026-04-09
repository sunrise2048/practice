#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1505;
int T;
int n,m,k;
int K;
bool vis[N][N];
int a[N][N];
void prt(){
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cout<<a[i][j];
        }
        cout<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;K=k;
        for(int i=1;i<=n;++i){
            fill(vis[i]+1,vis[i]+m+1,0);
            fill(a[i]+1,a[i]+m+1,0);
        }
        if(k==2){
            a[1][1]=a[n][m]=1;
            prt();
            continue;
        }
        if(k==3){
            a[1][1]=a[1][2]=a[2][1]=1;
            prt();
            continue;
        }
        vector<vector<pair<int,int>>> ve;
        vis[1][1]=1;
        ve.push_back({{1,1}});
        if(m>2){
            vis[1][3]=1;
            ve.push_back({{1,3}});
        }
        vis[1][2]=vis[2][2]=1;
        ve.push_back({{1,2},{2,2}});
        if(n>2){
            vis[2][1]=vis[3][1]=1;
            ve.push_back({{2,1},{3,1}});
        }
        else{
            vis[2][1]=1;
            ve.push_back({{2,1}});
        }
        for(int i=1;i<=m;i+=2){
            if(vis[1][i])continue;
            ve.push_back({{1,i}});
            vis[1][i]=1;
        }
        for(int i=1;i<n;++i){
            for(int j=1;j<=m;++j){
                if(!vis[i][j]&&!vis[i+1][j]){
                    ve.push_back({{i,j},{i+1,j}});
                    vis[i][j]=vis[i+1][j]=1;
                }
            }
        }
        for(int i=1;i<=m;++i){
            if(!vis[n][i])ve.push_back({{n,i}});
        }
        for(auto nv:ve){
            if(k<=0)break;
            k-=nv.size();
            for(auto [x,y]:nv)a[x][y]=1;
        }
        if(k==-1)a[1][1]=0;
        prt();
    }
    return 0;
}