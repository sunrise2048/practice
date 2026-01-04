#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m;
vector<int> e[N];
int col[N];
int in[N];
vector<int> id;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        id.clear();
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            e[i].clear();
            in[i]=0;
            col[i]=0;
        }
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            in[v]++;
        }
        for(int i=1;i<=n;++i){
            if(in[i]==0||col[i]==0){
                col[i]=1;
                for(int to:e[i]){
                    if(col[to]==0)col[to]=2;
                }
            }
            if(col[i]==2){
                for(int to:e[i]){
                    col[to]=3;
                }
            }
        }
        for(int i=1;i<=n;++i){
            if(col[i]==3){
                id.push_back(i);
            }
        }
        cout<<id.size()<<'\n';
        for(int no:id){
            cout<<no<<' ';
        }cout<<'\n';
    }
    return 0;
}