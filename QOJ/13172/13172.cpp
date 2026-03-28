#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int n;
class SOL1{
public:
    vector<int> e[N];
    int fa[N],d[N];
    void dfs(int no,int fa){
        SOL1::fa[no]=fa;
        d[no]=d[fa]+1;
        for(int to:e[no]){
            if(to==fa)continue;
            dfs(to,no);
        }
    }
    vector<int> td[N],son[N];
    bool fl[N];
    int las;
    void era(int no){
        fl[no]=1;
        cout<<no-1<<' ';
        las=fa[no];
        for(int to:son[fa[no]]){
            if(fl[to])continue;
            era(to);
        }
    }
    void sol(){
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            ++u;++v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
        int did=1;
        for(int i=2;i<=n;++i){
            if(d[i]>d[did])did=i;
        }
        dfs(did,0);
        for(int i=1;i<=n;++i){
            if(d[i]>d[did])did=i;
        }
        int zlen=d[did];
        vector<int> ve(zlen);
        for(int i=0;i<zlen;++i){
            ve[i]=did;did=fa[did];
        }
        if(zlen&1){
            dfs(ve[zlen/2],0);
        }
        else{
            int m1=ve[zlen/2-1],m2=ve[zlen/2];
            e[m1].erase(find(e[m1].begin(),e[m1].end(),m2)); 
            e[m2].erase(find(e[m2].begin(),e[m2].end(),m1));
            dfs(m1,0);dfs(m2,0);
        }
        for(int i=1;i<=n;++i){
            if(!fa[i])continue;
            td[d[i]].push_back(i);son[fa[i]].push_back(i);
            if(e[i].size()>1){
                fl[fa[i]]=1;
            }
        }
        vector<int> yd;
        for(int i=1;i<=n;++i){
            if(fa[i]&&!fl[fa[i]]){
                yd.push_back(i);
                fl[fa[i]]=1;
            }
        }
        sort(yd.begin(),yd.end(),[&](const int& x,const int& y){
            return min(x,fa[x])!=min(y,fa[y])?min(x,fa[x])<min(y,fa[y]):max(x,fa[x])<max(y,fa[y]);
        });
        for(int l=0;l<yd.size();++l){
            int r=l;
            while(r!=yd.size()&&(yd[l]<fa[yd[l]])==(yd[r]<fa[yd[r]]))++r;
            reverse(yd.begin()+l,yd.begin()+r);
            l=r-1;
        }
        cout<<(yd[0]>fa[yd[0]])<<endl;
        memset(fl,0,sizeof(fl));
        for(int no:yd){
            era(no);
        }
        for(int nd=n;nd>1;--nd){
            vector<int> id;
            for(int no:td[nd]){
                if(fl[no])continue;
                if(no==las)continue;
                id.push_back(no);
            }
            for(int no:td[nd]){
                if(fl[no])continue;
                if(no==las)id.push_back(no);
            }
            if(id.empty())continue;
            for(int no:id){
                if(fl[no])continue;
                era(no);
            }
        }
        if(zlen%2==0){
            cout<<(ve[zlen/2]==las?ve[zlen/2-1]:ve[zlen/2])-1<<' ';
        }cout<<endl;
    }
}sol1;
int la[N];
int main(){
    int ooo;
    cin>>ooo;
    cin>>n;
    if(ooo==1){
        sol1.sol();
        return 0; 
    }
    char c;
    cin>>c;
    int op=c-'0';
    vector<int> las(2);
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        if(i==1){
            las[0]=u,las[1]=v;
            if(op)swap(u,v);
        }
        else if(la[u]==i-1||la[v]==i-1){
            if(la[u]==i-1)swap(u,v);
        }
        else if(la[u]||la[v]){
            if(la[v])swap(u,v);
        }
        else{
            if(las[0]<u||(las[0]==u&&las[1]<v))op^=1;
            las[0]=u,las[1]=v;
            if(op)swap(u,v);
        }
        cout<<u<<endl;
        la[u]=la[v]=i;
    }
    return 0;
}