#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const ll inf=1e17;
int n;
vector<pair<int,int>> e[N];
int fl[N];
ll md[N];
int si[N];
int f[N][N];
pair<ll,ll> fz[N][N];
ll hb(ll zx,ll zy){
    if(zx>zy)swap(zx,zy);
    if(zy<0)return max(zx,zy);
    if(zx>0)return min(zx,zy);
    if(-zx-1>zy)return zy;
    return zx;
}
void dfs(int no,int fa){
    f[no][0]=0;
    fz[no][0]={inf,inf};
    if(!fl[no]){
        si[no]=1;
        f[no][1]=0;
        fz[no][1]={-md[no]-1,no};
    }
    for(auto [to,tw]:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        vector<int> nf(si[no]+si[to]+1,n+1);
        vector<pair<ll,ll>> nfz(si[no]+si[to]+1);
        auto add=[&](int cn,int x,ll y){
            if(y<0&&(-y-1)<=n)return;
            if(nf[cn]>x){
                if(nf[cn]==x+1)nfz[cn].second=nfz[cn].first;
                else nfz[cn].second=-1;
                nf[cn]=x;
                nfz[cn].first=y;
            }
            else if(nf[cn]==x){
                if(y>=0){
                    if(nfz[cn].first<0)nfz[cn].first=y;
                    else nfz[cn].first=min(nfz[cn].first,y);
                }
                else{
                    if(nfz[cn].first<0)nfz[cn].first=min(nfz[cn].first,y);
                }
            }
            else if(nf[cn]+1==x){
                if(y>=0){
                    if(nfz[cn].second<0)nfz[cn].second=y;
                    else nfz[cn].second=min(nfz[cn].second,y);
                }
                else{
                    if(nfz[cn].second<0)nfz[cn].second=min(nfz[cn].second,y);
                }
            }
        };
        for(int i=0;i<=si[no];++i){
            for(int j=0;j<=si[to];++j){
                if(fz[to][j].first<0){
                    ll ds=-fz[to][j].first-1;
                    ds-=tw*n;
                    if(ds>0){
                        add(i+j,f[no][i]+f[to][j],hb(-ds-1,fz[no][i].first));
                        add(i+j,f[no][i]+f[to][j]+1,hb(-ds-1,fz[no][i].second));
                    }
                }
                else{
                    ll ds=fz[to][j].first+tw*n;
                    add(i+j,f[no][i]+f[to][j],hb(ds,fz[no][i].first));
                    add(i+j,f[no][i]+f[to][j]+1,hb(ds,fz[no][i].second));
                }
                if(fz[to][j].second<0)exit(1);
                ll ds=fz[to][j].second+tw*n;
                add(i+j,f[no][i]+f[to][j]+1,hb(ds,fz[no][i].first));
                add(i+j,f[no][i]+f[to][j]+2,hb(ds,fz[no][i].second));
            }
        }
        si[no]+=si[to];
        for(int i=0;i<=si[no];++i){
            f[no][i]=nf[i];
            fz[no][i]=nfz[i];
        }
    }
}
int ans[N];
int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;++i){
        int u,v,w;
        cin>>u>>v>>w;
        e[u].emplace_back(v,w);
        e[v].emplace_back(u,w);
    }
    memset(md,0x3f,sizeof(md));
    for(int i=1;i<=n;++i){
        cin>>fl[i];
        if(!fl[i])continue;
        auto dfs=[&](int no,int fa,int d,auto&& dfs)->void {
            md[no]=min(md[no],(ll)d*n+i);
            for(auto [to,tw]:e[no]){
                if(to==fa)continue;
                dfs(to,no,d+tw,dfs);
            }
        };
        dfs(i,0,0,dfs);
    }
    memset(f,0x3f,sizeof(f));
    dfs(1,0);
    for(int i=1;i<=n;++i){
        if(f[1][i]<=n){
            if(fz[1][i].first>=0)ans[f[1][i]]=max(ans[f[1][i]],i);
            else ans[f[1][i]+1]=max(ans[f[1][i]+1],i);
        }
    }
    for(int i=1;i<=n;++i){
        ans[i]=max(ans[i],ans[i-1]);
        cout<<ans[i]<<' ';
    }
    return 0;
}