#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
class LCT{
public:
    struct node{
        int six;
        int si;
        bool fl;
        int s[2];
        int fa;
    }t[N];
    void pushup(int x){
        t[x].si=t[x].six+1+t[t[x].s[0]].si+t[t[x].s[1]].si;
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
    bool is_root(int x){
        return t[t[x].fa].s[0]!=x&&t[t[x].fa].s[1]!=x;
    }
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
        if(t[x].s[xop^1]){
            t[t[x].s[xop^1]].fa=y;
        }
        t[x].s[xop^1]=y;
        t[y].fa=x;
        pushup(y);pushup(x);
    }
    int st[N],st_r;
    void splay(int x){
        int y=x;
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
            t[x].six+=t[t[x].s[1]].si;
            t[x].six-=t[y].si;
            t[x].s[1]=y;
            pushup(x);
            y=x;
            x=t[x].fa;
        }
        return y;
    }
    void make_root(int x){
        access(x);
        splay(x);
        upd_fl(x);
    }
    void link(int x,int y){
        make_root(x);make_root(y);
        t[y].six+=t[x].si;
        t[x].fa=y;
        pushup(y);
    }
    void split(int x,int y){
        make_root(x);
        access(y);
        splay(y);
    }
    ll query(int x,int y){
        split(x,y);
        return 1ll*(t[y].six+1)*(t[x].six+1);
    }
}lct;
int n,q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i)lct.t[i].si=1;
    while(q--){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='A')lct.link(x,y);
        else cout<<lct.query(x,y)<<'\n';
    }
    return 0;
}