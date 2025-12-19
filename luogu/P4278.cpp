#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=7e4+5;
const int M=7e4;
const int B=270;
const int K=272;
int n,q;
struct list_of_B{
    int ne,pr;
    int cnt;
    int head;
}listB[B];
int cn[B][N],cnB[B][B];
int vk[N];
struct list_of_a{
    int ne,pr;
    int val;
    int kid;
}lst[N];
int headB;
int cnt_of_a;
int cnt_of_B;
class INIT{
public:
    int a[N];
    int L[B],R[B];
    void sol(){
        headB=1;
        for(int i=0;i<=M;++i){
            vk[i]=i/B+1;
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        cnt_of_a=n;
        const int kc=(n+B-1)/B;
        for(int i=1;i<=kc;++i){
            L[i]=R[i-1]+1;
            R[i]=i*B;
        }
        R[kc]=n;
        cnt_of_B=kc;
        for(int i=1;i<=kc;++i){
            listB[i].cnt=R[i]-L[i]+1;
            listB[i].ne=(i==kc?0:i+1);
            listB[i].pr=(i==1?0:i-1);
            listB[i].head=L[i];
            memcpy(cn[i],cn[i-1],sizeof(cn[i]));
            memcpy(cnB[i],cnB[i-1],sizeof(cnB[i]));
            for(int j=L[i];j<=R[i];++j){
                lst[j].val=a[j];
                lst[j].pr=(j==L[i]?0:j-1);
                lst[j].ne=(j==R[i]?0:j+1);
                lst[j].kid=i;
                cn[i][a[j]]++;
                cnB[i][vk[a[j]]]++;
            }
        }
    }
}init;
int lans;
int qcn[N],qcnB[B];
int get_id(int rk){
    int no=headB;
    while(rk>listB[no].cnt){
        rk-=listB[no].cnt;
        no=listB[no].ne;
    }
    no=listB[no].head;
    while(rk>1){
        --rk;
        no=lst[no].ne;
    }
    return no;
}
void get_qcn(int idx,int idy,int op){
    int no_id=idx;
    while(no_id!=idy){
        qcn[lst[no_id].val]+=op;
        qcnB[vk[lst[no_id].val]]+=op;
        no_id=lst[no_id].ne;
    }
}
int query(int x,int y,int rk){
    int idx=get_id(x),idy=get_id(y);
    if(lst[idx].kid==lst[idy].kid){
        get_qcn(idx,lst[idy].ne,1);
        int ans=0;
        for(int i=1;i<=B;++i){
            if(rk>qcnB[i]){
                rk-=qcnB[i];
                continue;
            }
            for(int j=(i-1)*B;j<=i*B-1;++j){
                if(rk>qcn[j]){
                    rk-=qcn[j];
                    continue;
                }
                ans=j;
                break;
            }
            break;
        }
        get_qcn(idx,lst[idy].ne,-1);
        return ans;
    }
    get_qcn(idx,0,1);get_qcn(listB[lst[idy].kid].head,lst[idy].ne,1);
    const int kl=lst[idx].kid,kr=listB[lst[idy].kid].pr;
    int ans=0;
    for(int i=1;i<=B;++i){
        if(rk>cnB[kr][i]-cnB[kl][i]+qcnB[i]){
            rk-=cnB[kr][i]-cnB[kl][i]+qcnB[i];
            continue;
        }
        for(int j=(i-1)*B;j<=i*B-1;++j){
            if(rk>cn[kr][j]-cn[kl][j]+qcn[j]){
                rk-=cn[kr][j]-cn[kl][j]+qcn[j];
                continue;
            }
            ans=j;
            break;
        }
        break;
    }
    get_qcn(idx,0,-1);get_qcn(listB[lst[idy].kid].head,lst[idy].ne,-1);
    return ans;
}
void modify(int x,int y){
    int idx=get_id(x);
    int no=lst[idx].kid;
    const int ly=lst[idx].val;
    lst[idx].val=y;
    while(no){
        cn[no][ly]--;cn[no][y]++;
        cnB[no][vk[ly]]--;cnB[no][vk[y]]++;
        no=listB[no].ne;
    }
}
void cg(int nok){
    const int tk=++cnt_of_B;
    const int pr=listB[nok].pr;
    if(nok==headB)headB=tk;
    listB[tk].ne=nok;
    listB[nok].pr=tk;
    listB[tk].pr=pr;
    listB[pr].ne=tk;
    memcpy(cn[tk],cn[pr],sizeof(cn[tk]));
    memcpy(cnB[tk],cnB[pr],sizeof(cnB[tk]));
    int no_id=listB[nok].head;
    listB[tk].head=no_id;
    while(listB[tk].cnt<B){
        ++listB[tk].cnt;
        const int nv=lst[no_id].val;
        cn[tk][nv]++;
        cnB[tk][vk[nv]]++;
        lst[no_id].kid=tk;
        no_id=lst[no_id].ne;
    }
    lst[lst[no_id].pr].ne=0;
    lst[no_id].pr=0;
    listB[nok].head=no_id;
    listB[nok].cnt=B;
}
void insert(int x,int y){
    const int nid=++cnt_of_a;
    if(x==cnt_of_a){
        int nok=headB;
        while(listB[nok].ne){
            nok=listB[nok].ne;
        }
        int no_id=listB[nok].head;
        while(lst[no_id].ne)no_id=lst[no_id].ne;
        lst[nid].kid=nok;
        lst[nid].pr=no_id;
        lst[no_id].ne=nid;
        lst[nid].val=y;
        listB[nok].cnt++;
        cn[nok][y]++;
        cnB[nok][vk[y]]++;
        if(listB[nok].cnt==2*B){
            cg(nok);
        }
        return;
    }
    int id_ne=get_id(x);
    const int nok=lst[id_ne].kid;
    lst[nid].kid=nok;
    lst[nid].ne=id_ne;
    lst[nid].pr=lst[id_ne].pr;
    lst[lst[id_ne].pr].ne=nid;
    lst[id_ne].pr=nid;
    lst[nid].val=y;
    if(listB[nok].head==id_ne)listB[nok].head=nid;
    listB[nok].cnt++;
    int no_k=nok;
    while(no_k){
        cn[no_k][y]++;
        cnB[no_k][vk[y]]++;
        no_k=listB[no_k].ne;
    }
    if(listB[nok].cnt==2*B){
        cg(nok);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    init.sol();
    cin>>q;
    while(q--){
        char op;
        int x,y;
        cin>>op>>x>>y;
        x^=lans;y^=lans;
        if(op=='Q'){
            int k;
            cin>>k;
            k^=lans;
            cout<<(lans=query(x,y,k))<<'\n';
        }
        else if(op=='M'){
            modify(x,y);
        }
        else{
            insert(x,y);
        }
    }
    return 0;
}