#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int K=20;
int T;
int n,q;
int a[N];
int xj1[K],tm1[K];
int xj[K];
bool fl[N];
vector<pair<int,int>> qs[N];
void ins1(int vl,int tm){
    for(int i=19;i>=0;--i){
        if(vl&(1<<i)){
            if(!xj1[i]){
                xj1[i]=vl;tm1[i]=tm;
                return;
            }
            if(tm1[i]>tm){
                swap(tm1[i],tm);
                swap(xj1[i],vl);
            }
            vl^=xj1[i];
        }
    }
}
void ins(int vl){
    for(int i=19;i>=0;--i){
        if(vl&(1<<i)){
            if(!xj[i]){
                for(int j=i-1;j>=0;--j){
                    if(vl&(1<<j))vl^=xj[j];
                }
                for(int j=19;j>i;--j){
                    if(xj[j]&(1<<i))xj[j]^=vl;
                }
                xj[i]=vl;
                return;
            }
            vl^=xj[i];
        }
    }
}
int grk(int vl){
    if(vl==-1)return -1;
    int cn=0;
    int s=0;
    for(int i=0;i<20;++i){
        if(!xj[i])continue;
        if(vl&(1<<i)){
            s+=(1<<cn);
            vl^=xj[i];
        }
        ++cn;
    }
    return s;
}
int gs(int rk){
    int cn=0;
    int s=0;
    for(int i=0;i<20;++i){
        if(!xj[i])continue;
        if(rk&(1<<cn))s^=xj[i];
        ++cn;
    }
    if(rk>=(1<<cn))return -1;
    return s;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;++i){
            qs[i].clear();
            cin>>a[i];
        }
        for(int i=1;i<=q;++i){
            int l,r;
            cin>>l>>r;
            fl[i]=1;
            qs[l].emplace_back(r,i);
        }
        memset(xj1,0,sizeof(xj1));
        memset(tm1,0,sizeof(tm1));
        for(int l=n;l;--l){
            ins1(a[l],l);
            for(auto [r,id]:qs[l]){
                vector<int> xi;
                for(int i=0;i<20;++i){
                    if(xj1[i]&&tm1[i]<=r)xi.push_back(tm1[i]);
                }
                sort(xi.begin(),xi.end());
                int lv=-1;
                memset(xj,0,sizeof(xj));
                for(int i=0;i<xi.size();++i){
                    int no=xi[i],ne=(i+1==xi.size()?r:xi[i+1]-1);
                    ins(a[no]);
                    int nrk=grk(lv);
                    nrk+=ne-no+1;
                    lv=gs(nrk);
                    if(lv==-1){
                        fl[id]=0;
                        break;
                    }
                }
            }
        }
        for(int i=1;i<=q;++i){
            if(fl[i])cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}