#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n;
struct edge{
    int u,v,w;
    edge()=default;
    edge(int u,int v,int w):u(u),v(v),w(w){}
};
vector<edge> ve;
vector<int> id;
int ask(int x,int y){
    if(x==y)return 0;
    if(x>y)swap(x,y);
    cout<<"? "<<x<<' '<<y<<endl;
    int ds;
    cin>>ds;
    return ds;
}
mt19937 mt(time(0));
void solve(vector<int>& id,int qx,vector<int>& qdx){
    if(id.size()<=1)return;
    int x;
    if(qx!=-1)x=qx;
    else x=id[mt()%id.size()];
    vector<int> dx,dy(id.size());
    if(qdx.empty()){
        dx.resize(id.size());
        for(int i=0;i<id.size();++i)dx[i]=ask(x,id[i]);
    }
    else swap(qdx,dx);
    int y=0;
    for(int i=0;i<id.size();++i){
        if(dx[i]>dx[y])y=i;
    }
    y=id[y];
    for(int i=0;i<id.size();++i)dy[i]=ask(y,id[i]);
    int ds=ask(x,y);
    vector<pair<int,int>> le;
    for(int i=0;i<id.size();++i){
        int no=id[i];
        if(dx[i]+dy[i]==ds){
            le.emplace_back(dx[i],no);
        }
    }
    sort(le.begin(),le.end());
    for(int i=0;i+1<le.size();++i){
        ve.emplace_back(le[i].second,le[i+1].second,le[i+1].first-le[i].first);
    }
    vector<vector<int>> ts(le.size());
    for(int i=0;i<id.size();++i){
        int td=dx[i]-(dx[i]+dy[i]-ds)/2;
        int it=lower_bound(le.begin(),le.end(),make_pair(td,0))-le.begin();
        ts[it].push_back(i);
    }
    for(int i=0;i<le.size();++i){
        int nl=le[i].first;
        vector<int> tdx(ts[i].size());
        for(int j=0;j<ts[i].size();++j){
            tdx[j]=dx[ts[i][j]]-nl;
            ts[i][j]=id[ts[i][j]];
        }
        solve(ts[i],le[i].second,tdx);
    }
}
int main(){ 
    cin>>T;
    while(T--){
        cin>>n;
        ve.clear();
        id.resize(n);
        iota(id.begin(),id.end(),1);
        vector<int> ep;
        solve(id,-1,ep);
        cout<<"! ";
        for(auto [u,v,w]:ve)cout<<u<<' '<<v<<' '<<w<<' ';
        cout<<endl;
    }
    return 0;
}