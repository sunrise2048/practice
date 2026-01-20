#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1.5e6+5;
int n,m,q;
int cn;
struct node{
    int x,y;
}nd[N],ans[N];
struct ques{
    int op,x;
    int id;
}qs[N];
class BCJ{
public:
    int fa[N];
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void init(int no){
        fa[no]=no;
    }
    void merge(int x,int y){
        fa[find(y)]=find(x);
    }
}bcl,bcr;
bool fl_q[N];
int tml[N],tmr[N];
int tl_r[N],tr_l[N];
int nl[N],nr[N];
ques tql[N],tqr[N];
int cn_tql,cn_tqr;
void init(int id){
    tml[id]=tmr[id]=q+1;
    nl[id]=nd[id].x;nr[id]=nd[id].y;
    bcl.init(id);bcr.init(id);
}
void add_ql(int no){
    ++cn_tql;
    tql[cn_tql]=qs[no];
}
void add_qr(int no){
    ++cn_tqr;
    tqr[cn_tqr]=qs[no];
}
set<pair<int,int>> st_l,st_r;
void solve(int vl,int vr,int ql,int qr){
    int cnq=0,cnop=0;
    for(int i=ql;i<=qr;++i){
        fl_q[i]=0;
        if(qs[i].op==2||qs[i].op==3)++cnop;
        if(qs[i].op==1){
            ++cnq;
        }
    }
    if(cnq==0)return;
    if(cnop==0){
        for(int i=ql;i<=qr;++i){
            auto [op,x,qid]=qs[i];
            if(op==1)ans[qid]=nd[x];
        }
        return;
    }
    if(vl==vr){
        for(int i=ql;i<=qr;++i){
            if(qs[i].op==1){
                ans[qs[i].id].x=ans[qs[i].id].y=vl;
            }
        }
        return;
    }
    const int mid=(vl+vr)>>1;
    cn_tql=cn_tqr=0;
    st_l.clear();st_r.clear();
    for(int i=ql;i<=qr;++i){
        auto [op,x,qid]=qs[i];
        if(op==4){
            init(x);
            if(nr[x]<mid){
                tl_r[x]=nr[x];
                tml[x]=0;
            }
            else if(nl[x]>mid){
                tr_l[x]=nl[x];
                tmr[x]=0;
            }
            else{
                st_l.emplace(nl[x],x);
                st_r.emplace(nr[x],x);
            }
            continue;
        }
        if(op==2){
            if(x<=mid){
                int no=0;
                while(!st_l.empty()&&st_l.begin()->first<x){
                    if(!no)no=st_l.begin()->second;
                    else{
                        bcl.merge(no,st_l.begin()->second);
                    }
                    st_l.erase(st_l.begin());
                }
                if(no){
                    nl[no]=x;
                    st_l.emplace(x,no);
                }
                continue;
            }
            while(!st_r.empty()&&st_r.rbegin()->first>=x){
                int no=st_r.rbegin()->second;
                tr_l[no]=x;
                tmr[no]=qs[i].id;
                st_r.erase(*st_r.rbegin());
            }
            continue;
        }
        if(op==3){
            if(x>=mid){
                int no=0;
                while(!st_r.empty()&&st_r.rbegin()->first>x){
                    if(!no)no=st_r.rbegin()->second;
                    else{
                        bcr.merge(no,st_r.rbegin()->second);
                    }
                    st_r.erase(*st_r.rbegin());
                }
                if(no){
                    nr[no]=x;
                    st_r.emplace(x,no);
                }
                continue;
            }
            while(!st_l.empty()&&st_l.begin()->first<=x){
                int no=st_l.begin()->second;
                tl_r[no]=x;
                tml[no]=qs[i].id;
                st_l.erase(st_l.begin());
            }
            continue;
        }
        int lt=tml[bcl.find(x)],rt=tmr[bcr.find(x)];
        if(min(lt,rt)>q){
            ans[qid].x=nl[bcl.find(x)];
            ans[qid].y=nr[bcr.find(x)];
            fl_q[i]=1;
        }
    }
    for(int i=ql;i<=qr;++i){
        if(fl_q[i])continue;
        if(qs[i].op==4){
            int no=qs[i].x;
            int lt=tml[bcl.find(no)],rt=tmr[bcr.find(no)];
            if(min(lt,rt)>q)continue;
            if(lt<rt){
                nd[no].x=nl[bcl.find(no)];
                nd[no].y=tl_r[bcl.find(no)];
                add_ql(i);
            }
            else{
                nd[no].x=tr_l[bcr.find(no)];
                nd[no].y=nr[bcr.find(no)];
                add_qr(i);
            }
        }
        else if(qs[i].op==2){
            if(qs[i].x==mid)continue;
            if(qs[i].x<mid)add_ql(i);
            else add_qr(i);
        }
        else if(qs[i].op==3){
            if(qs[i].x==mid)continue;
            if(qs[i].x<mid)add_ql(i);
            else add_qr(i);
        }
        else{
            if(tml[bcl.find(qs[i].x)]<tmr[bcr.find(qs[i].x)])add_ql(i);
            else add_qr(i);
        }
    }
    int cnl=cn_tql,cnr=cn_tqr;
    for(int i=1;i<=cnl;++i)qs[ql+i-1]=tql[i];
    for(int i=1;i<=cnr;++i)qs[ql+cnl+i-1]=tqr[i];
    solve(vl,mid-1,ql,ql+cnl-1);
    solve(mid+1,vr,ql+cnl,ql+cnl+cnr-1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;++i){
        cin>>nd[i].x>>nd[i].y;
        nd[i].y=n-nd[i].y;
        qs[i].id=i;
        qs[i].op=4;
        qs[i].x=i;
    }
    cn=m;
    for(int i=m+1;i<=m+q;++i){
        ans[i].x=-1;
        cin>>qs[i].op;
        qs[i].id=i;
        if(qs[i].op==1){
            cin>>qs[i].x;
        }
        else if(qs[i].op==2){
            cin>>qs[i].x;
            qs[i].x=n-qs[i].x;
        }
        else if(qs[i].op==3){
            cin>>qs[i].x;
        }
        else{
            int x,y;
            cin>>x>>y;
            ++cn;
            nd[cn].x=x,nd[cn].y=n-y;
            qs[i].x=cn;
        }
    }
    q+=m;
    solve(0,n,1,q);
    for(int i=m+1;i<=q;++i){
        if(ans[i].x<0)continue;
        cout<<ans[i].x<<' '<<n-ans[i].y<<'\n';
    }
    return 0;
}