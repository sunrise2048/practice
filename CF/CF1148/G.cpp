#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int M=1e7+5;
int n,k;
int a[N];
bool isp[M];
int phi[M];
vector<int> pr;
int mip[M];
vector<int> sp[N];
void init(){
    const int n=1e7;
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(!isp[i]){
            phi[i]=-1;
            mip[i]=i;
            pr.push_back(i);
        }
        for(int p:pr){
            if(i*p>n)break;
            isp[i*p]=1;
            mip[i*p]=p;
            if(i%p==0){
                break;
            }
            else phi[i*p]=-phi[i];
        }
    }
}
int sum[M];
vector<int> ps;
void add(int no,int s,int d){
    if(no==ps.size()){
        sum[s]+=d*phi[s];
        return;
    }
    add(no+1,s,d);add(no+1,s*ps[no],d);
}
int qu(int no,int s){
    if(no==ps.size())return sum[s];
    return qu(no+1,s)+qu(no+1,s*ps[no]);
}
vector<int> id;
bool fl[N];
vector<int> tid[N];
void solve(int l,int r,vector<int>& nid){
    if(l==r){
        for(int no:nid){
            tid[id[l]].push_back(no);
        }
        return;
    }
    const int mid=l+r>>1;
    for(int i=l;i<=mid;++i){
        ps=sp[id[i]];
        add(0,1,1);
    }
    vector<int> ls,rs;
    for(int no:nid){
        ps=sp[no];
        if(qu(0,1)==0)rs.push_back(no);
        else ls.push_back(no);
    }
    for(int i=l;i<=mid;++i){
        ps=sp[id[i]];
        add(0,1,-1);
    }
    solve(l,mid,ls);solve(mid+1,r,rs);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        int no=a[i];
        while(no!=1){
            int mp=mip[no];
            while(no%mp==0)no/=mp;
            sp[i].push_back(mp);
        }
    }
    for(int i=1;i<=n;++i){
        ps=sp[i];
        if(qu(0,1)==0){
            id.push_back(i);
            add(0,1,1);
            fl[i]=1;
        }
    }
    if(id.size()>=k){
        id.resize(k);
        for(int no:id)cout<<no<<' ';
        return 0;
    }
    for(int no:id){
        ps=sp[no];
        add(0,1,-1);
    }
    vector<int> lid;
    for(int i=1;i<=n;++i){
        if(fl[i])continue;
        lid.push_back(i);
    }
    solve(0,id.size()-1,lid);
    sort(id.begin(),id.end(),[](const int& x,const int& y){
        return tid[x].size()>tid[y].size();
    });
    int ns=n;
    while(ns>k){
        int bk=id.back();
        if(tid[bk].size()==0){
            ns--;
            id.pop_back();
            continue;
        }
        if(ns==k+1&&tid[bk].size()==1){
            tid[id[0]].pop_back();
            ns--;
            continue;
        }
        tid[bk].pop_back();
        --ns;
    }
    for(int no:id){
        cout<<no<<' ';
        for(int nn:tid[no])cout<<nn<<' ';
    }
    return 0;
}