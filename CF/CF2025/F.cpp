#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n,q;
int idx[N],idy[N];
struct edge{
    int v,id,op;
};
vector<edge> e[N];
int d[N];
int vl[N];
int op1[N];
void dfs(int no,int fid){
    for(auto [to,id,op]:e[no]){
        if(id==fid)continue;
        if(d[to]){
            if(d[to]<d[no]){
                op1[id]=op^1;
                vl[to]^=1;
            }
            continue;
        }
        d[to]=d[no]+1;
        dfs(to,id);
        if(vl[to]){
            op1[id]=op^1;
            vl[to]^=1;
        }
        else{
            op1[id]=op;
            vl[no]^=1;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=q;++i){
        int x,y;
        cin>>x>>y;
        idx[i]=x;idy[i]=y;
        e[x].push_back({y,i,0});
        e[y].push_back({x,i,1});
    }
    for(int i=1;i<=n;++i){
        if(d[i])continue;
        d[i]=1;
        dfs(i,0);
    }
    memset(vl,0,sizeof(vl));
    for(int i=1;i<=q;++i){
        int id;
        if(op1[i]){
            id=idy[i];
            cout<<"y";
        }
        else{
            id=idx[i];
            cout<<"x";
        }
        if(vl[id]){
            vl[id]--;
            cout<<"-";
        }
        else{
            vl[id]++;
            cout<<"+";
        }
        cout<<'\n';
    }
    return 0;
}