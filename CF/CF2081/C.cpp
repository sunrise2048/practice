#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int T;
int n,m;
int a[N][N];
int hs[N],ls[N];
vector<int> vh[4],vl[4];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        fill(hs+1,hs+n+1,0);
        fill(ls+1,ls+m+1,0);
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                char c;
                cin>>c;
                a[i][j]=c-'0';
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                hs[i]^=a[i][j];
                ls[j]^=a[i][j];
            }
        }
        int ans=n+m;
        for(int op:{0,1,2,3}){
            vh[op].clear();vl[op].clear();
        }
        for(int i=1;i<=n;++i){
            if(hs[i])vh[hs[i]].push_back(i);
            else --ans;
        }
        for(int i=1;i<=m;++i){
            if(ls[i])vl[ls[i]].push_back(i);
            else --ans;
        }
        for(int op:{1,2,3}){
            while(!vh[op].empty()&&!vl[op].empty()){
                --ans;
                int x=vh[op].back();vh[op].pop_back();
                int y=vl[op].back();vl[op].pop_back();
                a[x][y]^=op;
            }
        }
        vector<int> ch,cl;
        for(int op:{1,2,3}){
            if(vh[op].size())ch.push_back(op);
            if(vl[op].size())cl.push_back(op);
        }
        if(ch.size()+cl.size()==3&&ch.size()&&cl.size()){
            if(ch.size()==1){
                int c0=ch[0],c1=cl[0],c2=cl[1];
                while(vh[c0].size()&&vl[c1].size()&&vl[c2].size()){
                    --ans;
                    int x=vh[c0].back(),y=vl[c1].back(),z=vl[c2].back();
                    vh[c0].pop_back();vl[c1].pop_back();vl[c2].pop_back();
                    a[x][y]^=c1,a[x][z]^=c2;
                }
            }
            else{
                int c0=cl[0],c1=ch[0],c2=ch[1];
                while(vl[c0].size()&&vh[c1].size()&&vh[c2].size()){
                    --ans;
                    int x=vl[c0].back(),y=vh[c1].back(),z=vh[c2].back();
                    vl[c0].pop_back();vh[c1].pop_back();vh[c2].pop_back();
                    a[y][x]^=c1,a[z][x]^=c2;
                }
            }
        }
        ch.clear();cl.clear();
        for(int op:{1,2,3}){
            if(vh[op].size())ch.push_back(op);
            if(vl[op].size())cl.push_back(op);
        }
        if(ch.size()&&cl.size()){
            int x=ch[0],y=cl[0];
            while(vh[x].size()>1&&vl[y].size()>1){
                --ans;
                int id0=vh[x].back();vh[x].pop_back();
                int id1=vh[x].back();vh[x].pop_back();
                int id2=vl[y].back();vl[y].pop_back();
                int id3=vl[y].back();vl[y].pop_back();
                a[id0][id2]^=x;
                a[id1][id2]^=x;
                a[id0][id2]^=y;
                a[id0][id3]^=y;
            }
        }
        for(int op:{1,2,3}){
            while(!vh[op].empty()){
                int x=vh[op].back();
                a[x][1]^=op;
                vh[op].pop_back();
            }
            while(!vl[op].empty()){
                int y=vl[op].back();
                a[1][y]^=op;
                vl[op].pop_back();
            }
        }
        cout<<ans<<'\n';
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                cout<<a[i][j];
            }cout<<'\n';
        }
    }
    return 0;
}