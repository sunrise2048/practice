#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N],b[N];
int t[N],in[N];
vector<int> e[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            t[i]=in[i]=0;
            e[i].clear();
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
            t[a[i]]++;
        }
        for(int i=1;i<=n;++i){
            cin>>b[i];
        }
        int z=1;
        for(int i=2;i<=n;++i){
            if(t[i]>t[z])z=i;
        }
        for(int i=1;i<=n;++i){
            if(b[i]==z)continue;
            e[b[i]].push_back(a[i]);
            in[a[i]]++;
        }
        queue<int> q;
        for(int i=1;i<=n;++i){
            if(in[i]==0)q.push(i);
        }
        while(!q.empty()){
            int no=q.front();
            q.pop();
            for(int to:e[no]){
                in[to]--;
                if(in[to]==0)q.push(to);
            }
        }
        bool fl=1;
        for(int i=1;i<=n;++i){
            if(in[i]){
                fl=0;
                break;
            }
        }
        if(fl)cout<<"AC\n";
        else cout<<"WA\n";
    }
    return 0;
}