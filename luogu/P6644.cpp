#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e3+5;
int n;
int e[N][N];
vector<int> ve[N];
int ne[N],pr[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            char c;
            cin>>c;
            if(c=='R')e[i][j]=e[j][i]=1;
        }
    }
    for(int i=1;i<=n;++i){
        int jd=0;
        int ed=i;
        memset(ne,0,sizeof(ne));memset(pr,0,sizeof(pr));
        for(int j=1;j<=n;++j){
            if(i==j)continue;
            if(pr[ed]==0||e[pr[ed]][ed]==e[ed][j]){
                pr[j]=ed;
                ne[ed]=j;
                ed=j;
                continue;
            }
            if(!jd){
                pr[j]=ed;
                ne[ed]=j;
                jd=ed;
                ed=j;
                continue;
            }
            if(e[pr[jd]][jd]==e[jd][j]){
                int no=jd;
                int to=ne[jd];
                if(e[j][to]==e[j][no]){
                    jd=to;
                    if(ne[to]==0)jd=0;
                }
                else jd=j;
                ne[no]=j;pr[j]=no;
                ne[j]=to;pr[to]=j;
            }
            else{
                int no=pr[jd];
                int to=jd;
                jd=j;
                ne[no]=j;pr[j]=no;
                ne[j]=to;pr[to]=j;
                if(e[j][no]==e[j][to])jd=no;
                if(pr[jd]==0)jd=0;
            }
        }
        int no=i;
        while(no){
            ve[i].push_back(no);
            no=ne[no];
        }
    }
    for(int i=1;i<=n;++i){
        cout<<n<<' ';
        for(int j:ve[i])cout<<j<<' ';
        cout<<'\n';
    }
    return 0;
}