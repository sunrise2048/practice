#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e4+5;
int T;
int n;
int p[N];
int get_op(int x,int y){
    cout<<"? "<<x<<' '<<y<<endl;
    int op;
    cin>>op;
    return op;
}
void gb(int id,vector<int>& id1,vector<int>& id2){
    reverse(id1.begin(),id1.end());reverse(id2.begin(),id2.end());
    while(id1.size()+id2.size()){
        if(id1.empty()){
            p[id++]=id2.back();
            id2.pop_back();
            continue;
        }
        if(id2.empty()){
            p[id++]=id1.back();
            id1.pop_back();
            continue;
        }
        if(get_op(id1.back(),id2.back())){
            p[id++]=id1.back();
            id1.pop_back();
        }
        else{
            p[id++]=id2.back();
            id2.pop_back();
        }
    }
}
void prt(){
    cout<<"! ";
    for(int i=1;i<=n;++i)cout<<p[i]<<' ';
    cout<<'\n';
}
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        int l,r=n;
        while(r!=1&&get_op(r,r-1)==0){
            --r;
        }
        if(r==1){
            cout<<"! -1"<<endl;
            continue;
        }
        l=r;
        while(l!=1&&get_op(l,l-1)==1){
            --l;
        }
        if(l==1){
            cout<<"! -1"<<endl;
            continue;
        }
        int z=l-1;
        int mx1=l;
        for(int i=l+1;i<r;++i){
            if(get_op(z,i)){
                mx1=i;
            }
            else break;
        }
        int mx2=n+1;
        for(int i=n;i>=r;--i){
            if(get_op(z,i)){
                mx2=i;
            }
            else break;
        }
        iota(p+1,p+n+1,1);
        if(mx2==n+1){
            p[z]=mx1;
            vector<int> id1,id2;
            for(int i=r-1;i>=l;--i){
                if(i==mx1)id1.push_back(z);
                else id1.push_back(i);
            }
            for(int i=r;i<=n;++i){
                id2.push_back(i);
            }
            gb(z+1,id1,id2);
            prt();
            continue;
        }
        vector<int> id1,id2;
        if(get_op(mx1,mx2)){
            p[z]=mx1;
            for(int i=r-1;i>=l;--i){
                if(i==mx1)id1.push_back(z);
                else id1.push_back(i);
            }
            for(int i=r;i<=n;++i){
                id2.push_back(i);
            }
        }
        else{
            p[z]=mx2;
            for(int i=r-1;i>=l;--i){
                id1.push_back(i);
            }
            for(int i=r;i<=n;++i){
                if(i==mx2)id2.push_back(z);
                else id2.push_back(i);
            }
        }
        gb(z+1,id1,id2);
        prt();
    }
    return 0;
}