#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,m;
int e[N];
int fa[N],si[N];
int col[N];
struct ope{
    int x,lc;
}q[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int ans[N][3];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>e[i];
        fa[i]=i;
        si[i]=1;
    }
    cin>>m;
    for(int i=1;i<=m;++i){
        char c;
        cin>>q[i].x>>c;
        int tc=0;
        if(c=='C')tc=1;
        else if(c=='O')tc=2;
        else tc=3;
        q[i].lc=col[q[i].x];
        col[q[i].x]=tc;
    }
    for(int i=1;i<=n;++i){
        if(col[i])continue;
        si[find(e[i])]+=si[i];
        fa[i]=find(e[i]);
    }
    for(int i=1;i<=n;++i){
        if(!col[i])continue;
        ans[m][col[i]-1]+=si[i];
    }
    for(int i=m;i;--i){
        auto [x,c]=q[i];
        memcpy(ans[i-1],ans[i],sizeof(ans[i]));
        if(c){
            ans[i-1][col[x]-1]-=si[x];
            col[x]=c;
            ans[i-1][col[x]-1]+=si[x];
        }
        else{
            ans[i-1][col[x]-1]-=si[x];
            int fd=find(e[x]);
            fa[x]=fd;
            si[fd]+=si[x];
            col[x]=c;
            if(col[fd])ans[i-1][col[fd]-1]+=si[x];
        }
    }
    for(int i=1;i<=m;++i){
        cout<<ans[i][0]<<' '<<ans[i][1]<<' '<<ans[i][2]<<'\n';
    }
    return 0;
}