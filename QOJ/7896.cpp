#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=25;
int T;
int n,d;
struct Tree{
    vector<int> son;
    int si,mxd;
    int f[3];
};
vector<Tree> t,tf;
int ans[N][N];
int aid[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    t.push_back({{},1,0,{1,1,0}});
    tf.push_back({{},1,0,{1,1,0}});
    for(int n=2;n<=21;++n){
        vector<int> ns;
        vector<Tree> nf;
        auto dfs=[&](int s,int id,auto&& dfs)->void {
            if(!s){
                int f0=1,f1=1,f2=1;
                int nmx=ns.size();
                for(int s:ns){
                    nmx=max({nmx,tf[s].mxd,(int)tf[s].son.size()+1});
                    f0*=tf[s].f[1]+tf[s].f[2];
                    f1*=tf[s].f[2];
                    f2*=tf[s].f[0]+tf[s].f[2];
                }
                f2-=f1;
                nf.push_back({ns,n,nmx,{f0,f1,f2}});
                return;
            }
            while(id&&tf[id].si>s)--id;
            for(int i=id;i>=0;--i){
                ns.push_back(i);
                dfs(s-tf[i].si,i,dfs);
                ns.pop_back();
            }
        };
        int id=tf.size()-1;
        while(id&&tf[id].si>n/2)--id;
        dfs(n-1,id,dfs);
        for(auto no:nf){
            t.push_back(no);
            ans[n][no.mxd]=max(ans[n][no.mxd],no.f[0]+no.f[2]);
            if(ans[n][no.mxd]==no.f[0]+no.f[2])aid[n][no.mxd]=t.size()-1;
        }
        if(n>10)continue;
        nf.clear();
        dfs(n-1,tf.size()-1,dfs);
        for(auto no:nf)tf.push_back(no);
    }
    for(int i=1;i<=21;++i){
        for(int j=1;j<i;++j){
            ans[i][j]=max(ans[i][j],ans[i][j-1]);
            if(ans[i][j]==ans[i][j-1])aid[i][j]=aid[i][j-1];
        }
    }
    cin>>T;
    while(T--){
        cin>>n>>d;
        ++n;
        cout<<ans[n][d]<<'\n';
        cout<<n<<'\n';
        int cn=1;
        auto dfs=[&](int no,int z,auto&& dfs)->void {
            for(int to:tf[z].son){
                ++cn;
                cout<<no<<' '<<cn<<'\n';
                dfs(cn,to,dfs);
            }
        };
        for(int to:t[aid[n][d]].son){
            ++cn;
            cout<<1<<' '<<cn<<'\n';
            dfs(cn,to,dfs);
        }
    }
    return 0;
}