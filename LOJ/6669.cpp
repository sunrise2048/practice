#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
int n;
int d[N];
int si[N],zs[N];
int top[N],ld[N];
vector<int> e[N];
int fa[N];
int id[N];
void dfs1(int no,int fa){
    si[no]=1;
    zs[no]=0;
    for(int to:e[no]){
        dfs1(to,no);
        si[no]+=si[to];
        if(si[to]>si[zs[no]])zs[no]=to;
    }
}
void dfs2(int no,int tp){
    top[no]=tp;
    ld[tp]=no;
    if(!zs[no])return;
    dfs2(zs[no],tp);
    for(int to:e[no]){
        if(to==zs[no])continue;
        dfs2(to,to);
    }
}
int main(){
    cin>>n;
    for(int i=2;i<=n;++i){
        cout<<"? "<<1<<' '<<i<<endl;
        cin>>d[i];
    }
    iota(id+1,id+n,2);
    sort(id+1,id+n,[](const int& x,const int& y){
        return d[x]<d[y];
    });
    for(int i=1;i<n;++i){
        int no=id[i];
        if(d[no]==1){
            e[1].push_back(no);
            fa[no]=1;
            continue;
        }
        dfs1(1,0);dfs2(1,1);
        int hd=1;
        while(true){
            int ds;
            cout<<"? "<<ld[hd]<<' '<<no<<endl;
            cin>>ds;
            int dlc=(d[no]+d[ld[hd]]-ds)/2;
            int lc=ld[hd];
            while(d[lc]>dlc)lc=fa[lc];
            int ts=0;
            for(int to:e[lc])ts+=to;
            ts-=zs[lc];
            if(!ts){
                fa[no]=lc;
                e[lc].push_back(no);
                break;
            }
            hd=ts;
        }
    }
    cout<<"! ";
    for(int i=2;i<=n;++i)cout<<fa[i]<<' ';
    cout<<endl;
    return 0;
}