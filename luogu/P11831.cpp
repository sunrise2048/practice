#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=1e5+5;
const int B=320;
const int K=325;
int T;
int n,m,q;
vector<int> e[N];
int a[N],b[N];
int ta[N],tb[N];
class Bitset{
public:
    ull f[N/64+1];
    void cl(){memset(f,0,sizeof(f));}
    void operator^=(const Bitset& y){
        for(int i=0;i<=N/64;++i){
            f[i]^=y.f[i];
        }
    }
    void operator&=(const Bitset& y){
        for(int i=0;i<=N/64;++i){
            f[i]&=y.f[i];
        }
    }
    void operator|=(const Bitset& y){
        for(int i=0;i<=N/64;++i){
            f[i]|=y.f[i];
        }
    }
    void upd(int id){
        f[id>>6]^=(1ull<<(id&63));
    }
    int get(int id){
        return (f[id>>6]&(1ull<<(id&63)))!=0;
    }
}vis[N],ka[K],kb[K],qv,qa;
int ks;
int kid[N],L[K],R[K];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;++i)e[i].clear();
        for(int i=1;i<=n;++i){
            vis[i].cl();
        }
        ks=(n+B-1)/B;
        for(int i=1;i<=ks;++i){
            L[i]=R[i-1]+1;
            R[i]=min(n,i*B);
            for(int j=L[i];j<=R[i];++j){
                kid[j]=i;
            }
            ka[i].cl();
            kb[i].cl();
        }
        ka[ks+1].cl();kb[ks+1].cl();
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
        }
        for(int i=n;i;--i){
            vis[i].upd(i);
            for(int to:e[i]){
                vis[i]|=vis[to];
            }
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
            ta[a[i]]=i;
            ka[kid[a[i]]].upd(i);
        }
        for(int i=ks-1;i;--i){
            ka[i]|=ka[i+1];
        }
        for(int i=1;i<=n;++i){
            cin>>b[i];
            tb[b[i]]=i;
            kb[kid[b[i]]].upd(i);
        }
        for(int i=ks-1;i;--i){
            kb[i]|=kb[i+1];
        }
        while(q--){
            int op,x,y;
            cin>>op>>x>>y;
            if(op==1){
                int ax=a[x],ay=a[y];
                swap(a[x],a[y]);
                swap(ta[ax],ta[ay]);
                if(ax>ay)swap(ax,ay);
                for(int i=kid[ax]+1;i<=kid[ay];++i){
                    ka[i].upd(x);ka[i].upd(y);
                }
            }
            else if(op==2){
                int bx=b[x],by=b[y];
                swap(b[x],b[y]);
                swap(tb[bx],tb[by]);
                if(bx>by)swap(bx,by);
                for(int i=kid[bx]+1;i<=kid[by];++i){
                    kb[i].upd(x);kb[i].upd(y);
                }
            }
            else{
                int z=x;
                cin>>x;
                swap(x,y);
                qv=vis[z];
                qa=ka[kid[y]+1];
                qa^=ka[kid[x]+1];
                for(int i=x;i<=R[kid[x]];++i)qa.upd(ta[i]);
                for(int i=y+1;i<=R[kid[y]];++i)qa.upd(ta[i]);
                qv&=qa;
                int nbk=1;
                for(int i=0;i<=N/64;++i){
                    while(nbk!=ks&&(qv.f[i]&kb[nbk+1].f[i])){
                        ++nbk;
                    }
                }
                int ans=0;
                for(int i=R[nbk];i>=L[nbk];--i){
                    if(qv.get(tb[i])){
                        ans=i;
                        break;
                    }
                }
                cout<<ans<<'\n';
            }
        }
    }
    return 0;
}