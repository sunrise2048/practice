#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=24;
int n;
char c[N][N];
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
vector<int> t[N];
int col[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    int cnf=0,cns=0;
    iota(fa,fa+n,0);
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin>>c[i][j];
            if(c[i][j]=='F'||c[i][j]=='S'){
                fa[find(i)]=find(j);
                if(c[i][j]=='F')++cnf;
                else ++cns;
            }
        }
    }
    for(int i=0;i<n;++i)t[find(i)].push_back(i);
    sort(t,t+n,[](const vector<int>& x,const vector<int>& y){
        return x.size()>y.size();
    });
    int cc=(3*n+2)/4;
    for(int i=0;i<n;++i){
        if(t[i].size()>cc)continue;
        cc-=t[i].size();
        for(int no:t[i])col[no]=1;
    }
    int op=(cnf<cns);
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(c[i][j]!='?')continue;
            if(col[i]==col[j]){
                c[i][j]=(op?'S':'F');
            }
            else{
                c[i][j]=(op?'F':'S');
            }
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout<<c[i][j];
        }
        cout<<'\n';
    }
    return 0;
}