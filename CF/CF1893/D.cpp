#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m;
int a[N],s[N];
int cn[N];
int d[N];
vector<int> t[N];
priority_queue<pair<int,int>> pq;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        fill(cn+1,cn+n+1,0);
        for(int i=1;i<=n;++i){
            int lv;
            cin>>lv;
            cn[lv]++;
        }
        while(!pq.empty())pq.pop();
        for(int i=1;i<=n;++i){
            if(cn[i])pq.emplace(cn[i],i);
        }
        for(int i=1;i<=m;++i)cin>>s[i];
        for(int i=1;i<=m;++i)cin>>d[i];
        bool fl=1;
        for(int i=1;i<=m;++i){
            t[i].clear();
            int len;
            vector<pair<int,int>> ve;
            while(s[i]){
                len=min(s[i],d[i]);
                while(len--){
                    if(pq.empty()){
                        fl=0;
                        break;
                    }
                    auto [cn,vl]=pq.top();
                    pq.pop();
                    t[i].push_back(vl);
                    --cn;
                    if(cn)ve.emplace_back(cn,vl);
                }
                if(!fl)break;
                for(auto [cn,vl]:ve)pq.emplace(cn,vl);
                ve.clear();
                s[i]-=min(s[i],d[i]);
            }
            if(!fl)break;
        }
        if(!fl){
            cout<<"-1\n";
            continue;
        }
        for(int i=1;i<=m;++i){
            for(int vl:t[i])cout<<vl<<' ';
            cout<<'\n';
        }
    }
    return 0;
}