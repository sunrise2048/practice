#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int f[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int T;
int n,m;
vector<int> a[N],id[N];
int fa[N<<1],miv[N<<1],si[N<<1];
int nv[N<<1];
int cn,ans;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        cn=ans=0;
        for(int i=1;i<=n;++i){
            a[i].resize(m+1);
            id[i].resize(m+1);
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                cin>>a[i][j];
                id[i][j]=++cn;
                fa[cn]=cn,miv[cn]=a[i][j];
                nv[cn]=a[i][j];
                si[cn]=1;
                if(i>1&&a[i][j]==a[i-1][j]){
                    int t=id[i-1][j];
                    if(find(cn)!=find(t)){
                        si[find(t)]+=si[find(cn)];
                        fa[find(cn)]=find(t);
                    }
                }
                if(j>1&&a[i][j]==a[i][j-1]){
                    int t=id[i][j-1];
                    if(find(cn)!=find(t)){
                        si[find(t)]+=si[find(cn)];
                        fa[find(cn)]=find(t);
                    }
                }
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                for(auto [dx,dy]:f){
                    int ti=i+dx,tj=j+dy;
                    if(ti<1||ti>n||tj<1||tj>m)continue;
                    miv[find(id[ti][tj])]=min(miv[find(id[ti][tj])],a[i][j]);
                }
            }
        }
        for(int i=1;i<=cn;++i){
            if(fa[i]==i){
                ans+=nv[i]<=miv[i];
            }
        }
        cout<<ans<<'\n';
        int q;
        cin>>q;
        while(q--){
            int x,y,d;
            cin>>x>>y>>d;
            a[x][y]-=d;
            int lid=find(id[x][y]);
            si[lid]--;
            if(!si[lid]&&nv[lid]<=miv[lid])--ans;
            id[x][y]=++cn;
            fa[cn]=cn,nv[cn]=miv[cn]=a[x][y];
            si[cn]=1;
            for(auto [dx,dy]:f){
                int tx=x+dx,ty=y+dy;
                if(tx<1||tx>n||ty<1||ty>m)continue;
                int td=find(id[tx][ty]);
                if(nv[td]<=miv[td]&&a[x][y]<nv[td]){
                    --ans;
                }
                miv[td]=min(miv[td],a[x][y]);
                miv[cn]=min(miv[cn],a[tx][ty]);
            }
            for(auto [dx,dy]:f){
                int tx=x+dx,ty=y+dy;
                if(tx<1||tx>n||ty<1||ty>m)continue;
                if(a[tx][ty]!=a[x][y])continue;
                int td=find(id[tx][ty]);
                if(td==find(cn))continue;
                if(nv[td]<=miv[td])--ans;
                miv[td]=min(miv[td],miv[find(cn)]);
                si[td]+=si[find(cn)];
                fa[find(cn)]=td;
            }
            if(nv[find(cn)]<=miv[find(cn)])++ans;
            cout<<ans<<'\n';
        }
    }
    return 0;
}