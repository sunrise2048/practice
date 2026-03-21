#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1.5e4+5;
int n,m;
vector<bitset<N>> f[N];
bitset<N> bt[N];
int a[N];
int s[N],b[N];
int lm;
vector<int> t;
priority_queue<pair<int,int>> q;
void gett(int i,int cn,int vl){
    if(i==0)return;
    if(cn<f[i-1].size()&&f[i-1][cn][vl]){
        gett(i-1,cn,vl);
        return;
    }
    t.push_back(b[i]);
    gett(i,cn-1,vl-b[i]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        lm+=a[i];
        for(int j=1;j<=a[i];++j){
            s[j]++;
        }
    }
    for(int i=1;i<=lm;++i)s[i]+=s[i-1];
    bt[0][0]=1;
    for(int i=1;i<=lm;++i){
        bt[i]=bt[i-1]<<1;
        bt[i][0]=1;
    }
    cin>>m;
    for(int i=1;i<=m;++i){
        cin>>b[i];
    }
    reverse(b+1,b+m+1);
    f[0].resize(1);
    f[0][0][0]=1;
    for(int i=1;i<=m;++i){
        f[i].resize(lm/b[i]+1);
        for(int j=0;j<f[i].size();++j){
            if(j<f[i-1].size())f[i][j]=f[i-1][j];
            if(j){
                f[i][j]|=f[i][j-1]<<b[i];
            }
            f[i][j]&=bt[s[j]];
        }
    }
    int as=-1;
    for(int i=0;i<f[m].size();++i){
        if(f[m][i][lm]){
            as=i;
            break;
        }
    }
    if(as==-1){
        cout<<"-1\n";
        return 0;
    }
    cout<<as<<'\n';
    gett(m,as,lm);
    reverse(t.begin(),t.end());
    for(int i=1;i<=n;++i){
        q.emplace(a[i],i);
    }
    for(int si:t){
        cout<<si<<' ';
        vector<int> tt;
        while(si--){
            int no=q.top().second;
            a[no]--;
            q.pop();
            tt.push_back(no);
            cout<<no<<' ';
        }
        cout<<'\n';
        for(int no:tt)q.emplace(a[no],no);
    }
    return 0;
}