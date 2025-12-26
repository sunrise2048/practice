#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=51061;
int n;
class LCT{
public:
    struct node{
        ll val;
        ll sum;
        int si;
        ll lz1,lz2=1;
        bool fl;
        int s[2];
        int fa;
    }t[N];
    void pushup(int x){
        t[x].sum=(t[t[x].s[0]].sum+t[t[x].s[1]].sum+t[x].val)%mod;
        t[x].si=t[t[x].s[0]].si+t[t[x].s[1]].si+1;
    }
    void upd_fl(int x){
        if(!x)return;
        swap(t[x].s[0],t[x].s[1]);
        t[x].fl^=1;
    }
    void upd_mul(int x,ll val){
        if(!x)return;
        if(val==1)return;
        t[x].val=t[x].val*val%mod;
        t[x].sum=t[x].sum*val%mod;
        t[x].lz1=t[x].lz1*val%mod;
        t[x].lz2=t[x].lz2*val%mod;
    }
    void upd_add(int x,ll val){
        if(!x)return;
        if(val==0)return;
        t[x].val=(t[x].val+val)%mod;
        t[x].sum=(t[x].sum+val*t[x].si)%mod;
        t[x].lz1=(t[x].lz1+val)%mod;
    }
    void pushdown(int x){
        if(t[x].fl){
            upd_fl(t[x].s[0]);upd_fl(t[x].s[1]);
            t[x].fl=0;
        }
        upd_mul(t[x].s[0],t[x].lz2);upd_mul(t[x].s[1],t[x].lz2);
        t[x].lz2=1;
        upd_add(t[x].s[0],t[x].lz1);upd_add(t[x].s[1],t[x].lz1);
        t[x].lz1=0;
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
    void update_add(int x,int y,int d){
        split(x,y);
        upd_add(y,d);
    }
    void update_mul(int x,int y,int d){
        split(x,y);
        upd_mul(y,d);
    }
    ll query(int x,int y){
        split(x,y);
        return t[y].sum;
    }
}lct;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int q;
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        lct.t[i].si=lct.t[i].val=1;
        lct.t[i].sum=1;
    }
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        lct.link(u,v);
    }
    while(q--){
        char op;
        cin>>op;
        if(op=='+'){
            int x,y,d;
            cin>>x>>y>>d;
            lct.update_add(x,y,d);
        }
        else if(op=='-'){
            int u1,v1,u2,v2;
            cin>>u1>>v1>>u2>>v2;
            lct.cut(u1,v1);
            lct.link(u2,v2);
        }
        else if(op=='*'){
            int x,y,d;
            cin>>x>>y>>d;
            lct.update_mul(x,y,d);
        }
        else{
            int x,y;
            cin>>x>>y;
            cout<<lct.query(x,y)<<'\n';
        }
    }
    return 0;
}