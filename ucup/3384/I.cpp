#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
bool fl[N];
bool fl_mi[N],fl_ma[N];
int ne_mi[N],ne_ma[N];
pair<int,int> f[N];
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool ch(int x,int y){
    return min(f[x].second,f[y].second)+1==max(f[x].first,f[y].first);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        f[i]={i,i};
        fa[i]=i;
        fl[i]=1;
        fl_mi[i]=fl_ma[i]=1;
    }
    for(int tt=1;tt<n;++tt){
        int u,v;
        cin>>u>>v;
        if(!fl[v]){
            cout<<"Bad oriented forest"<<endl;
            break;
        }
        fl[v]=0;
        int fu=find(u);
        if(!ch(fu,v)){
            cout<<"Bad segment at "<<fu<<endl;
            break;
        }
        if(f[v].first<f[fu].first){
            if(!fl_mi[u]){
                cout<<"Bad segment at "<<u<<endl;
                break;
            }
            int no=ne_mi[u];
            while(no){
                fl_mi[no]=0;
                no=ne_mi[no];
            }
            ne_mi[u]=v;
        }
        else{
            if(!fl_ma[u]){
                cout<<"Bad segment at "<<u<<endl;
                break;
            }
            int no=ne_ma[u];
            while(no){
                fl_ma[no]=0;
                no=ne_ma[no];
            }
            ne_ma[u]=v;
        }
        fa[v]=fu;
        f[fu].first=min(f[fu].first,f[v].first);
        f[fu].second=max(f[fu].second,f[v].second);
        cout<<"Good"<<endl;
    }
    return 0;
}