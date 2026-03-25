#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e3+5;
int T;
int n;
vector<int> e[N];
bool vis[N];
int cn;
int si[N],mxs[N];
int drt;
void findrt(int no,int fa){
    si[no]=1;
    mxs[no]=0;
    for(int to:e[no]){
        if(to==fa)continue;
        if(vis[to])continue;
        findrt(to,no);
        si[no]+=si[to];
        mxs[no]=max(mxs[no],si[to]);
    }
    mxs[no]=max(mxs[no],cn-si[no]);
    if(mxs[no]<mxs[drt])drt=no;
}
int rt;
bool chk(vector<int>& ve,int x){
    if(ve.empty())return 0;
    cout<<"? 1 "<<ve.size()<<' ';
    for(int no:ve)cout<<no<<' ';
    cout<<endl;
    int ld;
    cin>>ld;
    cout<<"? 2 "<<x<<endl;
    cout<<"? 1 "<<ve.size()<<' ';
    for(int no:ve)cout<<no<<' ';
    cout<<endl;
    int nd;
    cin>>nd;
    if(abs(ld-nd)==2*ve.size())return 0;
    return 1;
}
void erf(vector<int>& ve,int x){
    while(ve.size()>1){
        vector<int> nv;
        for(int i=0;i<ve.size()/2;++i)nv.push_back(ve[i]);
        if(chk(nv,x)){
            swap(nv,ve);
        }
        else{
            nv.clear();
            for(int i=ve.size()/2;i<ve.size();++i){
                nv.push_back(ve[i]);
            }
            swap(nv,ve);
        }
    }
    if(!chk(ve,x))ve.clear();
}
void solve(){
    vis[drt]=1;
    vector<int> ee;
    for(int to:e[drt]){
        if(vis[to])continue;
        ee.push_back(to);
    }
    erf(ee,drt);
    if(ee.empty()){
        rt=drt;
        return;
    }
    for(int to:e[drt]){
        if(to!=ee[0])continue;
        cn=si[to];
        drt=0;
        findrt(to,0);findrt(drt,0);
        solve();
    }
}
int vl[N];
void dfs(int no,int fa,int ld){
    cout<<"? 1 1 "<<no<<endl;
    int nd;
    cin>>nd;
    vl[no]=nd-ld;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no,nd);
    }
}
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            e[i].clear();
            vis[i]=0;
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        mxs[0]=n+1;drt=0;
        cn=n;
        findrt(1,0);
        findrt(drt,0);
        solve();
        dfs(rt,0,0);
        cout<<"! ";
        for(int i=1;i<=n;++i){
            cout<<vl[i]<<' ';
        }cout<<endl;
    }
    return 0;
}