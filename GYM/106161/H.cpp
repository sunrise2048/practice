#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
const int inf=1e9;
int T;
int n,W;
pair<ll,ll> pr[N],tp[N];
vector<int> idg,idw,idv;
bool fl[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>W;
        idg.clear();idw.clear();idv.clear();
        for(int i=1;i<=n;++i){
            cin>>pr[i].first;
        }
        for(int i=1;i<=n;++i){
            cin>>pr[i].second;
            if(pr[i].first){
                if(pr[i].second)idg.push_back(i);
                else idw.push_back(i);
            }
            else{
                idv.push_back(i);
            }
        }
        sort(idv.begin(),idv.begin(),[](const int& x,const int& y){
            return pr[x].first!=pr[y].first?pr[x].first<pr[y].first:x<y;
        });
        sort(idg.begin(),idg.end(),[](const int& x,const int& y){
            return pr[x].first!=pr[y].first?pr[x].first<pr[y].first:x<y;
        });
        bool as=0;
        for(int i=0;i<=idg.size()+idv.size();++i){
            int l0=0,l1=0;
            int tcn=i;
            vector<int> xid;
            int ne=-1;
            while(tcn--){
                if(l0==idg.size()){
                    xid.push_back(idv[l1]);
                    ++l1;
                    continue;
                }
                if(l1==idv.size()){
                    xid.push_back(idg[l0]);
                    ++l0;
                    continue;
                }
                int x=idg[l0],y=idv[l1];
                if(pr[x].first!=pr[y].first?pr[x].first<pr[y].first:x<y){
                    xid.push_back(idg[l0]);
                    ++l0;
                }
                else{
                    xid.push_back(idv[l1]);
                    ++l1;
                }
            }
            if(l0==idg.size()){
                if(l1==idv.size())ne=-1;
                else ne=idv[l1];
            }
            else if(l1==idv.size())ne=idg[l0];
            else{
                int x=idg[l0],y=idv[l1];
                if(pr[x].first!=pr[y].first?pr[x].first<pr[y].first:x<y){
                    ne=x;
                }
                else{
                    ne=y;
                }
            }
            ll ls=0;
            for(int no:xid){
                fl[no]=1;
                ls+=pr[no].first;
            }
            if(ls>W)
            for(int id:idg)tp[id]=pr[id];
            for(int i=0;i<l1;++i){
                tp[idv[i]]=pr[idv[i]];
                tp[idv[i]].second=inf;
            }
            for(int i=l1;i<idv.size();++i){
                tp[idv[i]]=pr[idv[i]];
                tp[idv[i]].second=1;
            }
            for(int id:idw)tp[id]=pr[id];
            vector<int> iid(n);iota(iid.begin(),iid.end(),1);
            sort(iid.begin(),iid.end(),[](const int& x,const int& y){
                return pr[x].second!=pr[y].second?pr[x].second>pr[y].second:x<y;
            });
            int tmx=inf;
            if(xid.size())tmx=pr[xid.back()].first;
            vector<int> las;
            ll ns=0;
            for(int no:iid){
                if(fl[no]){
                    ls-=tp[no].first;
                    ns+=tp[no].first;
                    continue;
                }
                if(tp[no].second==0){
                    las.push_back(no);
                    continue;
                }
                ;
            }
        }
    }
    return 0;
}