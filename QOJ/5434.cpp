#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=(1<<18)+5;
int n,k;
vector<int> nd;
bool vis[N];
class Get_hm{
public:
    vector<int> e[N];
    void dfs(int x){
        while(!e[x].empty()){
            int to=e[x].back();
            e[x].pop_back();
            dfs(to);
            nd.push_back(x<<1|(to&1));
        }
    }
    void sol(){
        if(k==1){
            nd.push_back(0);nd.push_back(1);
            return;
        }
        const int U=(1<<k-1)-1;
        for(int i=0;i<(1<<k-1);++i){
            e[i].push_back(U&(i<<1));
            e[i].push_back(U&(i<<1|1));
        }
        dfs(0);
        reverse(nd.begin(),nd.end());
    }
}get_hm;
int ne[N];
bool fl[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    if(n==1){
        cout<<"0\n";
        return 0;
    }
    while((1<<(k+1))+k<=n)++k;
    get_hm.sol();
    const int U=(1<<k)-1;
    for(int i=0;i<nd.size();++i){
        int x=nd[i];
        int nt=(x<<1)&U;
        if(nt==nd[(i+1)%nd.size()])nt|=1;
        ne[x]=nt;
    }
    int ls=n-U-k;
    int ed=0;
    for(int i=0;i<nd.size();++i){
        int x=nd[i];
        if(vis[x])continue;
        int cn=0;
        while(!vis[x]){
            vis[x]=1;
            ++cn;
            x=ne[x];
        }
        if(cn>=ls){
            ed=i;
            break;
        }
        fl[i]=1;
        ls-=cn;
    }
    int be=nd[(ed+1)%nd.size()];
    for(int i=k-1;i>=0;--i){
        if(be&(1<<i))cout<<1;
        else cout<<0;
    }
    for(int i=ed+2;i<nd.size();++i)cout<<(nd[i]&1);
    for(int i=0;i<=ed;++i){
        if(ed+1!=nd.size()||i)cout<<(nd[i]&1);
        if(!fl[i]||i==ed)continue;
        int x=nd[i];
        int y=x;
        do{
            y=ne[y];
            cout<<(y&1);
        }while(x!=y);
    }
    int x=nd[ed];
    while(ls--){
        x=ne[x];
        cout<<(x&1);
    }
    return 0;
}