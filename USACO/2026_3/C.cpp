#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int inf=1e9;
int T;
int n,q;
struct op{
    int l,r,val,id;
    op()=default;
    op(int l,int r,int val,int id):l(l),r(r),val(val),id(id){}
};
vector<op> op_mi,op_ma;
int nv[N];
int L[N],lid[N];
int R[N],rid[N];
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
vector<pair<int,int>> e[N];
int a[N];
bool vis[N],ve[N];
bool vis1[N];
int dfs(int no,int ls){
    vis1[no]=1;
    for(auto [to,td]:e[no]){
        if(td==ls)continue;
        if(vis1[td]){
            ve[td]=1;
            a[td]=nv[to];
            return to;
        }
        int la=dfs(to,td);
        if(la!=-1)return la;
    }
    return -1;
}
void solve(){
    for(int i=1;i<=n;++i){
        a[i]=L[i];
        if(L[i]>R[i]){
            cout<<"-1\n";
            return;
        }
    }
    for(int i=0;i<=q;++i)e[i].clear();
    for(int i=1;i<=n;++i){
        int x=lid[i],y=rid[i];
        e[x].emplace_back(y,i);
        if(x!=y)e[y].emplace_back(x,i);
    }
    memset(ve,0,sizeof(bool)*(n+2));
    memset(vis,0,sizeof(bool)*(q+1));
    queue<int> qu;
    qu.push(0);
    vis[0]=1;
    while(!qu.empty()){
        int no=qu.front();
        qu.pop();
        for(auto [to,td]:e[no]){
            if(ve[td])continue;
            ve[td]=1;
            if(!vis[to]){
                vis[to]=1;
                a[td]=nv[to];
                qu.push(to);
            }
        }
    }
    memset(vis1,0,sizeof(bool)*(q+1));
    for(int i=1;i<=q;++i){
        if(vis[i])continue;
        int rt=dfs(i,-1);
        if(rt==-1){
            cout<<"-1\n";
            return;
        }
        qu.push(rt);
        vis[rt]=1;
        while(!qu.empty()){
            int no=qu.front();
            qu.pop();
            for(auto [to,td]:e[no]){
                if(ve[td])continue;
                ve[td]=1;
                if(!vis[to]){
                    vis[to]=1;
                    a[td]=nv[to];
                    qu.push(to);
                }
            }
        }
    }
    for(int i=1;i<=n;++i){
        cout<<a[i];
        if(i!=n)cout<<' ';
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        op_mi.clear();op_ma.clear();
        for(int i=1;i<=q;++i){
            int t,l,r,k;
            cin>>t>>l>>r>>k;
            nv[i]=k;
            if(t==1)op_mi.emplace_back(l,r,k,i);
            else op_ma.emplace_back(l,r,k,i);
        }
        for(int i=1;i<=n;++i){
            L[i]=0;
            R[i]=inf;
            lid[i]=rid[i]=0;
        }
        sort(op_mi.begin(),op_mi.end(),[](const op& x,const op& y){
            return x.val>y.val;
        });
        sort(op_ma.begin(),op_ma.end(),[](const op& x,const op& y){
            return x.val<y.val;
        });
        iota(fa+1,fa+n+3,1);
        for(auto [l,r,k,id]:op_mi){
            int no=find(l);
            while(no<=r){
                L[no]=k;
                lid[no]=id;
                fa[find(no)]=find(no+1);
                no=find(no);
            }
        }
        iota(fa+1,fa+n+3,1);
        for(auto [l,r,k,id]:op_ma){
            int no=find(l);
            while(no<=r){
                R[no]=k;
                rid[no]=id;
                fa[find(no)]=find(no+1);
                no=find(no);
            }
        }
        solve();
    }
    return 0;
}