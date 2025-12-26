#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n;
struct node{
    int val;
    int s[2];
    int d;
    int fa;
}t[N];
int lz[N];
int merge(int x,int y){
    t[x].fa=t[y].fa=0;
    if(!x||!y)return x|y;
    if(t[x].val<t[y].val)swap(x,y);
    t[x].s[1]=merge(t[x].s[1],y);
    t[t[x].s[1]].fa=x;
    if(t[t[x].s[1]].d>t[t[x].s[0]].d){
        swap(t[x].s[0],t[x].s[1]);
        t[x].d=t[t[x].s[0]].d+1;
    }
    return x;
}
void dfs(int x,int d){
    if(!x)return;
    t[x].val+=d;
    dfs(t[x].s[0],d);dfs(t[x].s[1],d);
}
int erase(int x){
    if(t[x].fa==0){
        int rt=merge(t[x].s[0],t[x].s[1]);
        t[x].s[0]=t[x].s[1]=0;
        t[x].d=1;
        return rt;
    }
    int nf=t[x].fa;
    t[nf].s[t[nf].s[1]==x]=0;
    t[x].fa=0;
    while(nf){
        if(t[t[nf].s[1]].d>t[t[nf].s[0]].d){
            swap(t[nf].s[0],t[nf].s[1]);
            t[nf].d=t[t[nf].s[0]].d+1;
        }
        if(t[nf].fa)nf=t[nf].fa;
        else break;
    }
    int rt=merge(t[x].s[0],t[x].s[1]);
    t[x].s[0]=t[x].s[1]=0;
    t[x].d=1;
    return merge(rt,nf);
}
int rt[N];
int lzq;
int fa[N],si[N];
multiset<int> st;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>t[i].val;
        t[i].d=1;
        fa[i]=i;
        si[i]=1;
        rt[i]=i;
        st.insert(t[i].val);
    }
    int q;
    cin>>q;
    while(q--){
        string op;
        cin>>op;
        if(op=="U"){
            int x,y;
            cin>>x>>y;
            x=find(x),y=find(y);
            if(x==y)continue;
            if(si[x]<si[y])swap(x,y);
            st.erase(st.find(t[rt[x]].val+lz[x]));
            st.erase(st.find(t[rt[y]].val+lz[y]));
            dfs(rt[y],lz[y]-lz[x]);
            rt[x]=merge(rt[x],rt[y]);
            st.insert(t[rt[x]].val+lz[x]);
            fa[y]=x;
            si[x]+=si[y];
        }
        else if(op=="A1"){
            int x,d;
            cin>>x>>d;
            st.erase(st.find(t[rt[find(x)]].val+lz[find(x)]));
            rt[find(x)]=erase(x);
            t[x].val+=d;
            rt[find(x)]=merge(x,rt[find(x)]);
            st.insert(t[rt[find(x)]].val+lz[find(x)]);
        }
        else if(op=="A2"){
            int x,d;
            cin>>x>>d;
            x=find(x);
            st.erase(st.find(t[rt[x]].val+lz[x]));
            lz[x]+=d;
            st.insert(t[rt[x]].val+lz[x]);
        }
        else if(op=="A3"){
            int d;
            cin>>d;
            lzq+=d;
        }
        else if(op=="F1"){
            int x;
            cin>>x;
            cout<<lzq+t[x].val+lz[find(x)]<<'\n';
        }
        else if(op=="F2"){
            int x;
            cin>>x;
            x=find(x);
            cout<<lzq+t[rt[x]].val+lz[x]<<'\n';
        }
        else{
            cout<<(*st.rbegin())+lzq<<'\n';
        }
    }
    return 0;
}