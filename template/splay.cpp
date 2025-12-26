#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int inf=1e8;
class Splay{
public:
    struct node{
        int val;
        int cn;
        int vc;
        int s[2];
        int fa;
    }t[N];
    int cnt;
    int rt;
    void pushup(int x){
        t[x].cn=t[t[x].s[0]].cn+t[t[x].s[1]].cn+t[x].vc;
    }
    int get_op(int x){
        return t[t[x].fa].s[1]==x;
    }
    void rotate(int x){
        int y=t[x].fa;
        int z=t[y].fa;
        int xop=get_op(x),yop=get_op(y);
        t[y].s[xop]=t[x].s[xop^1];
        if(t[x].s[xop^1])t[t[x].s[xop^1]].fa=y;
        t[x].s[xop^1]=y;
        t[y].fa=x;
        if(z)t[z].s[yop]=x;
        t[x].fa=z;
        pushup(y);pushup(x);
    }
    void splay(int x,int z=0){
        int y;
        while((y=t[x].fa)!=z){
            if(t[y].fa!=z){
                rotate(get_op(x)==get_op(y)?y:x);
            }
            rotate(x);
        }
        if(!z)rt=x;
    }
    void insert(int no,int val){
        if(t[no].val==val){
            t[no].vc++;
            splay(no);
            return;
        }
        int op=val>t[no].val;
        if(!t[no].s[op]){
            t[no].s[op]=++cnt;
            t[cnt].val=val;
            t[cnt].vc=t[cnt].cn=1;
            t[cnt].fa=no;
            splay(cnt);
        }
        else{
            insert(t[no].s[op],val);
        }
    }
    void insert(int val){
        if(!rt){
            t[++cnt].val=val;
            t[cnt].cn=1;
            t[cnt].vc=1;
            rt=cnt;
            return;
        }
        insert(rt,val);
    }
    void erase(int no,int val){
        if(t[no].val==val){
            t[no].vc--;
            splay(no);
            if(t[no].vc==0){
                if(t[no].s[0]&&t[no].s[1]){
                    int x=t[no].s[0],y=t[no].s[1];
                    while(t[x].s[1])x=t[x].s[1];
                    while(t[y].s[0])y=t[y].s[0];
                    splay(x);
                    splay(y,x);
                    int fa=t[no].fa;
                    t[fa].s[get_op(no)]=0;
                    t[no].fa=0;
                    splay(fa);
                }
                else if(t[no].s[0]){
                    int x=t[no].s[0];
                    while(t[x].s[1])x=t[x].s[1];
                    splay(x);
                    int fa=t[no].fa;
                    t[fa].s[get_op(no)]=0;
                    t[no].fa=0;
                    splay(fa);
                }
                else if(t[no].s[1]){
                    int y=t[no].s[1];
                    while(t[y].s[0])y=t[y].s[0];
                    splay(y);
                    int fa=t[no].fa;
                    t[fa].s[get_op(no)]=0;
                    t[no].fa=0;
                    splay(fa);
                }
                else{
                    rt=0;
                }
            }
            return;
        }
        if(val<t[no].val)erase(t[no].s[0],val);
        else erase(t[no].s[1],val);
    }
    void erase(int val){
        erase(rt,val);
    }
    int query_rk(int no,int val){
        int ns=0;
        if(t[no].val<val){
            ns=t[no].cn-t[t[no].s[1]].cn;
            if(t[no].s[1])ns+=query_rk(t[no].s[1],val);
            else splay(no);
        }
        else{
            if(t[no].s[0])ns=query_rk(t[no].s[0],val);
            else splay(no);
        }
        return ns;
    }
    int query_rk(int val){
        if(!rt)return 1;
        return query_rk(rt,val)+1;
    }
    int query_by_rank(int no,int rk){
        if(rk<=t[t[no].s[0]].cn){
            return query_by_rank(t[no].s[0],rk);
        }
        if(rk<=t[t[no].s[0]].cn+t[no].vc){
            splay(no);
            return t[no].val;
        }
        return query_by_rank(t[no].s[1],rk-t[t[no].s[0]].cn-t[no].vc);
    }
    int query_by_rank(int rk){
        return query_by_rank(rt,rk);
    }
    int query_prev(int no,int val){
        if(t[no].val>=val){
            if(!t[no].s[0]){
                splay(no);
                return -inf;
            }
            return query_prev(t[no].s[0],val);
        }
        if(!t[no].s[1]){
            splay(no);
            return t[no].val;
        }
        return max(t[no].val,query_prev(t[no].s[1],val));
    }
    int query_prev(int val){
        return query_prev(rt,val);
    }
    int query_next(int no,int val){
        if(t[no].val<=val){
            if(!t[no].s[1]){
                splay(no);
                return inf;
            }
            return query_next(t[no].s[1],val);
        }
        if(!t[no].s[0]){
            splay(no);
            return t[no].val;
        }
        return min(t[no].val,query_next(t[no].s[0],val));
    }
    int query_next(int val){
        return query_next(rt,val);
    }
}splay;
int m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>m;
    while(m--){
        int op,x;
        cin>>op>>x;
        if(op==1)splay.insert(x);
        else if(op==2)splay.erase(x);
        else if(op==3)cout<<splay.query_rk(x)<<'\n';
        else if(op==4)cout<<splay.query_by_rank(x)<<'\n';
        else if(op==5)cout<<splay.query_prev(x)<<'\n';
        else cout<<splay.query_next(x)<<'\n';
    }
    return 0;
}