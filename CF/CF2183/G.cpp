#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n;
int a[N];
vector<int> q1,q2,q3;
int c[N];
void rd(vector<int>& id){
    id.clear();
    int si;
    cin>>si;
    while(si--){
        int no;
        cin>>no;
        id.push_back(no);
    }
}
void solve(){
    int t1=0;
    for(int i=1;i<=n;++i){
        c[i]=-1;
        if(t1<q2.size()&&q2[t1]==a[i]){
            c[i]=a[i]-q1[t1];
            ++t1;
        }
        else if(a[i-1]<a[i]-1||c[i-1]!=0){
            c[i]=2;
        }
    }
    for(int i=1;i+2<=n;++i){
        if(a[i+2]-a[i]==2&&c[i]==0&&c[i+2]==0&&c[i+1]==-1){
            cout<<"! -1"<<endl;
            return;
        }
    }
    for(int i=1;i<=n;++i){
        if(c[i]!=-1)continue;
        auto it=lower_bound(q3.begin(),q3.end(),a[i]+1);
        if((*it)==a[i]+1)c[i]=1;
        else c[i]=2;
    }
    cout<<"! ";
    for(int i=1;i<=n;++i)cout<<c[i]<<' ';
    cout<<endl;
}
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        cout<<"? L"<<endl;
        rd(q1);
        cout<<"? LR"<<endl;
        rd(q2);
        cout<<"? R"<<endl;
        rd(q3);
        solve();
    }
    return 0;
}