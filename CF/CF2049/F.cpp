#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int K=18;
int T;
int n,q;
ll a[N];
int cn[K][N];
int cr[K][N];
class BCJ{
public:
    int fa[N];
    void cl(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void merge(int x,int y){
        fa[find(x)]=find(y);
    }
}bcj[K];
map<int,int> t[K][N];
pair<int,int> op[N];
multiset<int> st;
void mer(int op,int x){
    int y=bcj[op].find(x-1);
    if(cn[op][y]==(1<<op))st.erase(st.find(cr[op][y]-y+1));
    if(cn[op][x]==(1<<op))st.erase(st.find(cr[op][x]-x+1));
    cr[op][y]=cr[op][x];
    bcj[op].merge(x,y);
    if(t[op][y].size()<t[op][x].size()){
        swap(t[op][x],t[op][y]);
        swap(cn[op][x],cn[op][y]);
    }
    for(auto [vl,d]:t[op][x]){
        if(!d)continue;
        if(t[op][y][vl]){
            t[op][y][vl]+=d;
        }
        else{
            t[op][y][vl]=d;
            ++cn[op][y];
        }
    }
    if(cn[op][y]==(1<<op))st.insert(cr[op][y]-y+1);
}
int ans[N];
void era(int x){
    for(int i=0;i<K;++i){
        if(a[x]<(1<<i)){
            int id=bcj[i].find(x);
            t[i][id][a[x]]--;
            if(!t[i][id][a[x]]){
                if(cn[i][id]==(1<<i))st.erase(st.find(cr[i][id]-id+1));
                cn[i][id]--;
            }
        }
    }
}
void ins(int x){
    for(int i=0;i<K;++i){
        if(a[x]>=(1<<i))continue;
        int id=bcj[i].find(x);
        if(!t[i][id][a[x]]){
            ++cn[i][id];
            if(cn[i][id]==(1<<i))st.insert(cr[i][id]-id+1);
        }
        t[i][id][a[x]]++;
        if(id==x&&cr[i][x]==x){
            if(x>1&&a[x-1]<(1<<i))mer(i,x);
            if(x<n&&a[x+1]<(1<<i))mer(i,x+1);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=0;i<K;++i){
            bcj[i].cl();
            memset(cn[i],0,sizeof(int)*(n+1));
            for(int j=1;j<=n;++j)t[i][j].clear();
        }
        for(int i=1;i<=q;++i){
            cin>>op[i].first>>op[i].second;
            a[op[i].first]+=op[i].second;
        }
        st.clear();
        for(int i=0;i<K;++i){
            for(int j=1;j<=n;++j){
                cr[i][j]=j;
                if(a[j]<(1<<i)){
                    t[i][j][a[j]]=1;
                    cn[i][j]=1;
                    if(!i)st.insert(1);
                    if(j>1&&a[j-1]<(1<<i)){
                        mer(i,j);
                    }
                }
            }
        }
        for(int i=q;i;--i){
            if(st.empty())ans[i]=0;
            else ans[i]=*st.rbegin();
            auto [x,d]=op[i];
            era(x);
            a[x]-=d;
            ins(x);
        }
        for(int i=1;i<=q;++i){
            cout<<ans[i]<<'\n';
        }
    }
    return 0;
}