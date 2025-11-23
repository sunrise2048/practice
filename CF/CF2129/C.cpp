#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e3+5;
int T;
int n;
char a[N];
vector<int> f;
void init(){
    int ss=1;
    int sl=2;
    f.push_back(1);
    for(int i=2;i<=1000;++i){
        if(sl+1+2*i>1000)break;
        if(i*(i+1)/2>ss){
            f.push_back(i);
            ss+=i*(i+1)/2;
            sl+=1+2*i;
        }
    }
}
int ask(vector<int>& a){
    cout<<"? "<<a.size()<<' ';
    for (int id:a) cout<<id<<' ';
    cout<<endl;
    int s;
    cin>>s;
    return s;
}
int idl,idr;
int main(){
    init();
    cin>>T;
    while (T--) {
        cin>>n;
        vector<int> id(n);
        for (int i=0;i<n;++i) id[i]=i+1;
        int ns=ask(id);
        if(ns){
            int l=1,r=n;
            while (l<r-1) {
                int mid=l+r>>1;
                id.resize(mid);
                for (int i=0;i<mid;++i) id[i]=i+1;
                int op=ask(id);
                if(op)r=mid;
                else l=mid;
            }
            idl=r-1;
            idr=r;
        }
        else{
            idl=n;
            idr=1;
        }
        for (int l=1;l<=n;l+=f.size()){
            int r=min(n,l+(int)f.size()-1);
            id.clear();
            for (int d=0;l+d<=r;++d) {
                int no=l+d;
                if(d)id.push_back(idl);
                for (int i=0;i<f[d];++i) {
                    id.push_back(idl);
                    id.push_back(no);
                }
            }
            int ns=ask(id);
            for (int d=r-l;d>=0;--d) {
                int no=l+d;
                if (ns>=f[d]*(f[d]+1)/2) {
                    a[no]=')';
                    ns-=f[d]*(f[d]+1)/2;
                }
                else a[no]='(';
            }
        }
        cout<<"! ";
        for(int i=1;i<=n;++i)cout<<a[i];
        cout<<endl;
    }
    return 0;
}