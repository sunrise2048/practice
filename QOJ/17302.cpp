#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=205;
const int D=85;
const int K=3005;
int T;
int n,k;
int s[N];
int kmp[N];
int lcp[N];
int ad[N][2];
int h[N][2];
int ne[N][2];
int f[2][D][N][K];
struct node{
    int op,d,sl,cn;
    //node()=default;
    //node(int op,int d,int sl,int cn):op(op),d(d),sl(sl),cn(cn){}
};
int las[2][D][N][K];
vector<int> t;
int gid(int op,int d,int sl,int cn,int vl){
    return op*D*N*K*2+d*N*K*2+sl*K*2+cn*2+vl;
}
void gt(int op,int d,int sl,int cn){
    if(op+d+sl+cn==0)return;
    int ls=las[op][d][sl][cn];
    gt(ls/(D*N*K*2),ls/(N*K*2)%D,ls/(K*2)%N,ls/2%K);
    t.push_back(ls&1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    cin>>T;
    while(T--){
        memset(lcp,0,sizeof(lcp));
        memset(ad,0,sizeof(ad));
        memset(h,0,sizeof(h));
        memset(f,0x3f,sizeof(f));
        memset(las,0,sizeof(las));
        memset(ne,0,sizeof(ne));
        t.clear();
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            char c;
            cin>>c;
            s[i]=c-'0';
        }
        {
            int j=0;
            for(int i=2;i<=n;++i){
                while(j&&s[i]!=s[j+1])j=kmp[j];
                if(s[i]==s[j+1])++j;
                kmp[i]=j;
            }
            for(int i=1;i<=n;++i){
                int len=0;
                while(i+len<=n&&s[i+len]==s[len+1])++len;
                lcp[i]=len;
            }
        }
        s[n+1]=-1;
        for(int i=0;i<=n;++i){
            int j=i;
            while(j&&s[j+1]!=0)j=kmp[j];
            if(s[j+1]==0)++j;
            ne[i][0]=j;
            for(int k=1;k<=i-j+1;++k){
                int lc=min(i-k+1,lcp[k]);
                if((k+lc==i+1?0:s[k+lc])<s[lc+1]){
                    ad[i][0]++;
                }
            }
            for(int k=1;k<=j;++k){
                int lc=min(j-k,lcp[k]);
                if(s[k+lc]<=s[lc+1]){
                    h[i][0]++;
                }
            }
            if(j==n)--h[i][0];
            j=i;
            while(j&&s[j+1]!=1)j=kmp[j];
            if(s[j+1]==1)++j;
            ne[i][1]=j;
            for(int k=1;k<=i-j+1;++k){
                int lc=min(i-k+1,lcp[k]);
                if((k+lc==i+1?1:s[k+lc])<s[lc+1]){
                    ad[i][1]++;
                }
            }
            for(int k=1;k<=j;++k){
                int lc=min(j-k,lcp[k]);
                if(s[k+lc]<=s[lc+1]){
                    h[i][1]++;
                }
            }
            if(j==n)--h[i][1];
        }
        queue<node> q;
        q.emplace(node{0,0,0,0});
        f[0][0][0][0]=0;
        while(!q.empty()){
            auto [op,d,sl,cn]=q.front();
            q.pop();
            if(op&&cn==k){
                gt(op,d,sl,cn);
                break;
            }
            for(int vl:{0,1}){
                int top=op,td=d+ad[sl][vl],tl=ne[sl][vl],tc=cn+d+ad[sl][vl]+h[sl][vl];
                if(tc>k)continue;
                if(tl==n)top=1;
                if(f[top][td][tl][tc]<=f[op][d][sl][cn]+1)continue;
                f[top][td][tl][tc]=f[op][d][sl][cn]+1;
                las[top][td][tl][tc]=gid(op,d,sl,cn,vl);
                q.emplace(node{top,td,tl,tc});
            }
        }
        if(t.empty()){
            cout<<"Impossible\n";
        }
        else{
            for(int no:t)cout<<no;
            cout<<'\n';
        }
    }
    return 0;
}