#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=305;
const double eps=1e-10;
int m;
struct info{
    double p,t,c;
};
class Tree{
public:
    int n,s;
    vector<int> e[N],son[N];
    int d[N],fa[N];
    vector<int> nfd;
    double grade[N],A[N],B[N],a[N],b[N];
    double S[N];
    vector<double> lis;
    vector<info> ps;
    void init_nfd(){
        for(int i=1;i<=n;++i)d[i]=e[i].size();
        nfd.reserve(n);
        auto dfs=[&](int no,int ff,auto&& dfs)->void {
            fa[no]=ff;
            nfd.push_back(no);
            for(int to:e[no]){
                if(to==ff)continue;
                son[no].push_back(to);
                dfs(to,no,dfs);
            }
        };
        dfs(1,0,dfs);
    }
    void init_grade(){
        vector<char> act(n+1,0);
        act[1]=1;
        auto dfs1=[&](int no,auto&& dfs)->void {
            double sa=0,sb=0;
            for(int to:son[no]){
                if(!act[to])continue;
                dfs(to,dfs);
                sa+=A[to];
                sb+=B[to];
            }
            if(no!=1){
                S[no]=d[no]-sa;
                A[no]=1.0/S[no];
                B[no]=(d[no]+sb)/S[no];
            }
        };
        auto dfs2=[&](int no,auto&& dfs)->void {
            for(int to:son[no]){
                if(!act[to])continue;
                a[to]=A[to]*a[no];
                b[to]=A[to]*b[no]+B[to];
                dfs(to,dfs);
            }
        };
        for(int cn=1;cn<n;++cn){
            dfs1(1,dfs1);
            a[1]=1,b[1]=0;
            dfs2(1,dfs2);
            double mi=1e18;
            int z=0;
            for(int i=2;i<=n;++i){
                if(act[i]||!act[fa[i]])continue;
                double tim=(b[fa[i]]+d[i])/a[fa[i]];
                if(tim<mi-eps||(fabs(tim-mi)<eps&&i<z)){
                    z=i;
                    mi=tim;
                }
            }
            act[z]=1;
            grade[z]=mi;
        }
    }
    info calc(double lim){
        vector<char> act(n+1);
        act[1]=1;
        for(int i=2;i<=n;++i){
            act[i]=(grade[i]<=lim+eps);
        }
        if(!act[s])return {0,0,0};
        for(int i=n-1;i;--i){
            int no=nfd[i];
            if(!act[no])continue;
            double sa=0;
            for(int to:son[no]){
                if(act[to])sa+=A[to];
            }
            S[no]=d[no]-sa;
            A[no]=1.0/S[no];
        }
        vector<double> xs(n+1);
        auto calc=[&](double val)->vector<double> {
            vector<double> nb(n+1),as(n+1);
            for(int i=n-1;i;--i){
                int no=nfd[i];
                if(!act[no])continue;
                double snb=0;
                for(int to:son[no]){
                    if(act[to])snb+=nb[to];
                }
                nb[no]=(xs[no]+snb)/S[no];
            }
            as[1]=val;
            for(int no:nfd){
                if(!act[no])continue;
                for(int to:son[no]){
                    if(act[to])as[to]=(A[to]*as[no]+nb[to]);
                }
            }
            return as;
        };
        auto p=calc(1);
        for(int i=2;i<=n;++i)xs[i]=d[i];
        auto t=calc(0);
        for(int i=2;i<=n;++i)xs[i]=d[i]*p[i];
        auto c=calc(0);
        return {p[s],t[s],c[s]};
    }
    void init_ps(){
        for(int i=2;i<=n;++i){
            lis.push_back(grade[i]);
        }
        sort(lis.begin(),lis.end());
        {
            vector<double> ls;
            for(double no:lis){
                if(ls.empty()||fabs(ls.back()-no)>eps)ls.push_back(no);
            }
            swap(ls,lis);
        }
        ps.reserve(lis.size());
        for(double lim:lis){
            ps.push_back(calc(lim));
        }
    }
    void init(int _n,int _s){
        n=_n;s=_s;
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        init_nfd();
        init_grade();
        init_ps();
    }
    info query_le(double lm){
        int l=-1,r=lis.size();
        while(l<r-1){
            int mid=l+r>>1;
            if(lis[mid]<=lm+eps)l=mid;
            else r=mid;
        }
        if(l<0)return {0,0,0};
        return ps[l];
    }
    info query_lt(double lm){
        int l=-1,r=lis.size();
        while(l<r-1){
            int mid=l+r>>1;
            if(lis[mid]<lm-eps)l=mid;
            else r=mid;
        }
        if(l<0)return {0,0,0};
        return ps[l];
    }
}tree[N];
int main(){
    cin>>m;
    for(int i=1;i<=m;++i){
        int n,s;
        cin>>n>>s;
        tree[i].init(n,s);
    }
    double ans=0;
    for(int i=1;i<=m;++i){
        for(double lm:tree[i].lis){
            info ne=tree[i].query_le(lm);
            info nt=tree[i].query_lt(lm);
            double sp=ne.p-nt.p;
            double se=ne.c-nt.c;
            if(sp<eps||se<eps)continue;
            for(int j=1;j<i;++j){
                info no=tree[j].query_le(lm);
                double q=1-no.p;
                double f=no.t-no.c;
                se=se*q+sp*f;
                sp*=q;
            }
            for(int j=i+1;j<=m;++j){
                info no=tree[j].query_lt(lm);
                double q=1-no.p;
                double f=no.t-no.c;
                se=se*q+sp*f;
                sp*=q;
            }
            ans+=se;
        }
    }
    printf("%.15f\n",ans);
    return 0;
}