#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e3+5,M=1e5+5;
int n,m,q;
pair<int,int> e[M];
int w[N+M];
int tim[M];
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
map<pair<int,int>,int> mp;
int eid[M];
class LCT{
public:
    struct node{
        int mxv;
        bool fl;
        int s[2];
        int fa;
    }t[N+M];
    void pushup(int x){
        if(w[t[t[x].s[0]].mxv]>w[t[t[x].s[1]].mxv])t[x].mxv=t[t[x].s[0]].mxv;
        else t[x].mxv=t[t[x].s[1]].mxv;
        if(w[x]>w[t[x].mxv])t[x].mxv=x;
    }
    void upd_fl(int x){
        if(!x)return;
        swap(t[x].s[0],t[x].s[1]);
        t[x].fl^=1;
    }
    void pushdown(int x){
        if(t[x].fl){
            upd_fl(t[x].s[0]);upd_fl(t[x].s[1]);
            t[x].fl=0;
        }
    }
    bool is_root(int x){return t[t[x].fa].s[0]!=x&&t[t[x].fa].s[1]!=x;}
    int get_op(int x){return t[t[x].fa].s[1]==x;}
    void rotate(int x){
        int y=t[x].fa;
        int z=t[y].fa;
        int xop=get_op(x);
        if(!is_root(y)){
            t[z].s[get_op(y)]=x;
        }
        t[x].fa=z;
        t[y].s[xop]=t[x].s[xop^1];
        if(t[x].s[xop^1])t[t[x].s[xop^1]].fa=y;
        t[x].s[xop^1]=y;
        t[y].fa=x;
        pushup(y);pushup(x);
    }
    int st[N],st_r;
    void splay(int x){
        int y;
        y=x;
        while(!is_root(y)){
            st[++st_r]=y;
            y=t[y].fa;
        }
        st[++st_r]=y;
        while(st_r){
            pushdown(st[st_r]);
            --st_r;
        }
        while(!is_root(x)&&(y=t[x].fa)){
            if(!is_root(y))rotate(get_op(x)==get_op(y)?y:x);
            rotate(x);
        }
    }
    int access(int x){
        int y=0;
        while(x){
            splay(x);
            t[x].s[1]=y;
            pushup(x);
            y=x;
            x=t[x].fa;
        }
        return x;
    }
    void make_root(int x){
        access(x);
        splay(x);
        upd_fl(x);
    }
    void split(int x,int y){
        make_root(x);
        access(y);
        splay(y);
    }
    void link(int x,int y){
        make_root(x);
        t[x].fa=y;
    }
    void cut(int x,int y){
        split(x,y);
        t[x].fa=0;
        t[y].s[0]=0;
    }
    void ins(int id){
        auto [u,v]=e[id];
        if(find(u)!=find(v)){
            link(id+n,u);
            link(id+n,v);
            fa[find(u)]=find(v);
            return;
        }
        split(u,v);
        if(w[t[v].mxv]<=w[n+id])return;
        int le=t[v].mxv-n;
        cut(le+n,e[le].first);cut(le+n,e[le].second);
        link(id+n,u);link(id+n,v);
    }
    ll query(int x,int y){
        split(x,y);
        return w[t[y].mxv];
    }
}lct;
vector<int> ans;
struct ope{
    int op,x,y;
}op[M];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;++i){
        fa[i]=i;
    }
    for(int i=1;i<=n+m;++i)lct.t[i].mxv=i;
    for(int i=1;i<=m;++i){
        cin>>e[i].first>>e[i].second>>w[n+i];
        if(e[i].first>e[i].second)swap(e[i].first,e[i].second);
        mp[e[i]]=i;
        tim[i]=q;
        eid[i]=i;
    }
    for(int i=1;i<=q;++i){
        cin>>op[i].op>>op[i].x>>op[i].y;
        if(op[i].x>op[i].y)swap(op[i].x,op[i].y);
        if(op[i].op==2){
            tim[mp[{op[i].x,op[i].y}]]=i;
        }
    }
    sort(eid+1,eid+m+1,[](const int& x,const int& y){
        return tim[x]>tim[y];
    });
    int no=0;
    for(int i=q;i;--i){
        while(no!=m&&tim[eid[no+1]]>=i){
            lct.ins(eid[no+1]);
            ++no;
        }
        if(op[i].op==1)ans.push_back(lct.query(op[i].x,op[i].y));
    }
    reverse(ans.begin(),ans.end());
    for(int as:ans)cout<<as<<'\n';
    return 0;
}