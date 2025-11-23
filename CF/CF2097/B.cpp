#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
const int mod=1e9+7;
int T;
int n,m,k;
pair<int,int> nd[N*N];
int id[N][N];
int fa[N*N],si[N*N],eg[N*N],val[N*N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void sol(){
    for(int i=0;i<=k;++i){
        if(!val[id[nd[i].first][nd[i].second]]){
            cout<<"0\n";
            return;
        }
        val[id[nd[i].first][nd[i].second]]=0;
    }
    for(int i=0;i<k;++i){
        if(abs(nd[i].first-nd[i+1].first)+abs(nd[i].second-nd[i+1].second)!=2){
            cout<<"0\n";
            return;
        }
        if(nd[i].first==nd[i+1].first){
            int x=nd[i].first,y=(nd[i].second+nd[i+1].second)/2;
            int no=find(id[x][y]);
            val[no]=1;
            eg[no]++;
        }
        else if(nd[i].second==nd[i+1].second){
            int x=(nd[i].first+nd[i+1].first)/2,y=nd[i].second;
            int no=find(id[x][y]);
            val[no]=1;
            eg[no]++;
        }
        else{
            int x1=nd[i].first,y1=nd[i+1].second,x2=nd[i+1].first,y2=nd[i].second;
            int id1=find(id[x1][y1]),id2=find(id[x2][y2]);
            if(id1==id2){
                ++eg[id1];
                continue;
            }
            val[id1]=min(val[id1],val[id2]);
            si[id1]+=si[id2];
            eg[id1]+=eg[id2]+1;
            fa[id2]=id1;
        }
    }
    ll ans=1;
    for(int i=1;i<=n*m;++i){
        if(fa[i]!=i)continue;
        if(eg[i]>si[i])ans=0;
        else if(eg[i]==si[i])ans=ans*val[i]%mod;
        else ans=ans*si[i]%mod;
    }
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n>>m>>k;
        for(int i=0;i<=k;++i){
            cin>>nd[i].first>>nd[i].second;
        }
        int cn=0;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                id[i][j]=++cn;
                fa[cn]=cn;
                si[cn]=1,eg[cn]=0;
                val[cn]=2;
            }
        }
        sol();
    }
    return 0;
}