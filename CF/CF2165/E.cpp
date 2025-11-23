#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T;
int n;
vector<int> e[N];
int cn[N],in[N];
int d[N];
int mx[N];
int mxd[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=0;i<=n;++i) {
            e[i].clear();
            d[i]=0;
            mx[i]=0;
            mxd[i]=0;
        }
        memset(cn,0,sizeof(int)*(n+1));
        for (int i=1;i<n;++i) {
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        queue<int> q;
        mx[1]=1;
        for (int i=1;i<=n;++i) {
            in[i]=e[i].size();
            if (in[i]==1) {
                d[i]=1;
                q.push(i);
            }
        }
        while(!q.empty()){
            int no=q.front();
            q.pop();
            cn[d[no]]++;
            for (int to:e[no]) {
                in[to]--;
                if (in[to]==1) {
                    d[to]=d[no]+1;
                    q.push(to);
                }
            }
            if (q.empty()) cn[d[no]]--;
        }
        for (int i=3;i<n;i+=2) {
            mx[i]=mx[i-2]+cn[(i-1)/2];
        }
        for (int i=1;i<=n;++i) {
            vector<int> td;
            for(int to:e[i])td.push_back(d[to]);
            sort(td.begin(),td.end(),greater<int>());
            for(int j=1;j<=td.size();++j){
                int tj=min(d[i]-1,td[j-1]-1);
                mxd[tj]=max(mxd[tj],j);
            }
        }
        for (int i=n-1;i>=0;--i) {
            mxd[i]=max(mxd[i],mxd[i+1]);
        }
        for (int i=4;i<n;i+=2) {
            mx[i]=mx[i-2]+cn[(i-1)/2];
        }
        for (int i=2;i<n;i+=2) {
            mx[i]+=mxd[i/2-1];
        }
        int as=1;
        for (int i=1;i<n;++i) {
            while (mx[as]<i) ++as;
            cout<<as<<' ';
        }cout<<'\n';
    }
    return 0;
}