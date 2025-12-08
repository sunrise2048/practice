#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1505;
int T;
int n,q;
int s[N][N];
int ans[N][N];
vector<int> op;
int cn;
struct ques{
    int id;
    int x;
}qs[N];
int nid;
bool fil(int no,int c){
    if(op[no]!=-1)return op[no]==c;
    op[no]=c;
    for(int i=no+1;i<n;++i){
        int opx=s[no][i]&1,opy=s[no][i]/2;
        if(opx!=c&&!fil(i,opy))return 0;
    }
    return 1;
}
void dfs(int no){
    if(no==n){
        ++cn;
        while(nid!=q&&qs[nid+1].x==cn){
            ++nid;
            for(int i=0;i<n;++i)ans[qs[nid].id][i]=op[i];
        }
        return;
    }
    if(op[no]!=-1){
        dfs(no+1);
        return;
    }
    vector<int> las=op;
    if(fil(no,0))dfs(no+1);
    op=las;
    if(fil(no,1))dfs(no+1);
    op=las;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=0;i<n;++i){
            for(int j=i+1;j<n;++j){
                char c;
                cin>>c;
                s[i][j]=c-'0';
                s[i][j]--;
            }
        }
        cn=0;
        for(int i=1;i<=q;++i){
            cin>>qs[i].x;
            qs[i].id=i;
            ans[i][0]=-1;
        }
        sort(qs+1,qs+q+1,[](const ques& x,const ques& y){
            return x.x<y.x;
        });
        nid=0;
        op.clear();op.resize(n,-1);
        dfs(0);
        for(int i=1;i<=q;++i){
            if(ans[i][0]==-1){
                cout<<"-1\n";
                continue;
            }
            for(int j=0;j<n;++j){
                cout<<ans[i][j];
            }
            cout<<'\n';
        }
    }
    return 0;
}