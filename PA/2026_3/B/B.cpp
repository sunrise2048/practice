#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n,m,k;
int a[N];
int t[N];
vector<int> e[N],tc[N];;
bool vis[N];
class BCJ{
public:
    int fa[N];
    void cl(){
        iota(fa+1,fa+n+1,1);
    }
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void merge(int x,int y){
        fa[find(x)]=find(y);
    }
}bcc,bcf;
map<int,int> ve[N];
vector<int> st;
void era(int no){
    vis[no]=1;
    for(int to:e[no]){
        if(vis[to])continue;
        int x=ve[no][a[to]];
        if(!x){
            ve[no][a[to]]=to;
            continue;
        }
        if(bcc.find(x)==bcc.find(to))continue;
        --t[a[to]];
        if(t[a[to]]==1)st.push_back(a[to]);
        bcc.merge(x,to);
    }
    for(int to:e[no]){
        if(!vis[to])continue;
        if(bcf.find(no)==bcf.find(to))continue;
        to=bcf.find(to);
        if(ve[no].size()<ve[to].size()){
            swap(ve[no],ve[to]);
        }
        bcf.merge(to,no);
        for(auto [c,x]:ve[to]){
            if(ve[no].count(c)){
                int y=ve[no][c];
                if(bcc.find(x)!=bcc.find(y)){
                    --t[c];
                    if(t[c]==1)st.push_back(c);
                    bcc.merge(x,y);
                }
            }
            else{
                ve[no][c]=x;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        fill(vis+1,vis+n+1,0);
        fill(t+1,t+k+1,0);
        for(int i=1;i<=k;++i)tc[i].clear();
        st.clear();
        for(int i=1;i<=n;++i){
            e[i].clear();
            ve[i].clear();
        }
        bcc.cl();bcf.cl();
        for(int i=1;i<=n;++i){
            cin>>a[i];
            t[a[i]]++;
            tc[a[i]].push_back(i);
        }
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for(int x=1;x<=n;++x){
            for(int y:e[x]){
                if(a[x]!=a[y])continue;
                if(bcc.find(x)!=bcc.find(y)){
                    bcc.merge(x,y);
                    --t[a[x]];
                }
            }
        }
        int nc=0;
        for(int i=1;i<=k;++i){
            if(t[i]==0)++nc;
            if(t[i]==1)st.push_back(i);
        }
        while(!st.empty()){
            ++nc;
            int nc=st.back();st.pop_back();
            for(int no:tc[nc]){
                era(no);
            }
        }
        if(nc==k)cout<<"TAK\n";
        else cout<<"NIE\n";
    }
    return 0;
}