#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,k;
vector<int> e[N];
int dfn[N],cn_dfn;
int nfd[N];
int d[N];
int st[N][18];
int lg[N];
void dfs(int no,int fa){
    dfn[no]=++cn_dfn;
    nfd[cn_dfn]=no;
    d[no]=d[fa]+1;
    st[dfn[no]][0]=d[fa];
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
    }
}
int get_dis(int x,int y){
    if(x==y)return 0;
    int ds=d[x]+d[y];
    x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    ++x;
    int k=lg[y-x+1];
    ds-=2*min(st[x][k],st[y-(1<<k)+1][k]);
    return ds;
}
set<int> sid;
int sum;
int ans;
void ins(int no){
    if(sid.empty()){
        sid.insert(dfn[no]);
        return;
    }
    auto it=sid.lower_bound(dfn[no]);
    int ne,la;
    if(it==sid.end())ne=*sid.begin();
    else ne=*it;
    if(it==sid.begin())la=*sid.rbegin();
    else la=*prev(it);
    ne=nfd[ne],la=nfd[la];
    sum+=get_dis(no,ne)+get_dis(no,la)-get_dis(la,ne);
    sid.insert(dfn[no]);
}
void era(int no){
    sid.erase(dfn[no]);
    if(sid.empty())return;
    auto it=sid.lower_bound(dfn[no]);
    int ne,la;
    if(it==sid.end())ne=*sid.begin();
    else ne=*it;
    if(it==sid.begin())la=*sid.rbegin();
    else la=*prev(it);
    ne=nfd[ne],la=nfd[la];
    sum-=get_dis(no,ne)+get_dis(no,la)-get_dis(la,ne);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
    for(int j=1;j<18;++j){
        for(int i=1;i+(1<<j)-1<=n;++i){
            st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
        }
    }
    int r=0;
    for(int l=1;l<=n;++l){
        while(r<n){
            ins(r+1);
            if(sum/2+1<=k){
                ++r;
                continue;
            }
            era(r+1);
            break;
        }
        ans=max(ans,r-l+1);
        era(l);
    }
    cout<<ans<<'\n';
    return 0;
}