#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N],b[N];
map<int,int> mp[N];
vector<int> e[N];
bool fl[N];
int cn0[N],cn1[N];
int tp0[N],tp1[N];
void upd(int no,int c,int op){
    int lv=mp[no][c];
    if(lv>=0)cn0[no]-=lv;
    else cn1[no]+=lv;
    lv+=op;
    if(lv>=0)cn0[no]+=lv;
    else cn1[no]-=lv;
    mp[no][c]=lv;
}
void dfs(int no,int fa){
    cn0[no]=cn1[no]=0;
    tp0[no]=tp1[no]=0;
    if(a[no]){
        upd(no,a[no],1);
    }
    else tp0[no]++;
    if(b[no]){
        upd(no,b[no],-1);
    }
    else tp1[no]++;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        tp0[no]+=tp0[to];
        tp1[no]+=tp1[to];
        if(mp[no].size()<mp[to].size()){
            swap(mp[no],mp[to]);
            swap(cn0[no],cn0[to]);
            swap(cn1[no],cn1[to]);
        }
        for(auto [c,lv]:mp[to]){
            upd(no,c,lv);
        }
    }
    if(cn0[no]<=tp1[no]&&cn1[no]<=tp0[no]){
        fl[no]=1;
    }
    else fl[no]=0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            mp[i].clear();
            e[i].clear();
        }
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>b[i];
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
        for(int i=1;i<=n;++i){
            cout<<fl[i];
        }
        cout<<'\n';
    }
    return 0;
}