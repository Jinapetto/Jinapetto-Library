// problem https://judge.yosupo.jp/problem/unionfind_with_potential
#include <bits/stdc++.h>
using namespace std;
class WeightedUnionFind{
private:
    long long datasize;
    long long inf_ = 1LL<<60;
    vector<long long> parent;
    vector<long long> weight;
    bool check_=true;
  
public:
    WeightedUnionFind(long long size_):datasize(size_),parent(size_,-1),weight(size_,0){}
    long long find(long long a){
        if(parent[a]<0)return a;
        long long a2=find(parent[a]);
        weight[a]+=weight[parent[a]];
        return parent[a]=a2;
    }
    long long get_weight(long long a){
        find(a);
        return weight[a];
    }
    bool merge(long long a,long long b,long long d){
        if(same(a,b)&&diff(a,b)!=d)check_=false;
        d+=get_weight(a);
        d-=get_weight(b);
        long long a2=find(a),b2=find(b);
        if(a2==b2)return false;
        if(parent[a2]>parent[b2]){
            swap(a2,b2);
            d=-d;
        }
        parent[a2]+=parent[b2];
        parent[b2]=a2;
        weight[b2]=d;
        return true;
    }
    bool same(long long a,long long b){
        return find(a)==find(b);
    }
    long long diff(long long a,long long b){
        if(!same(a,b))return -inf_;
        return get_weight(b)-get_weight(a);
    }
    long long size(long long a){
        return -parent[find(a)];
    }
    vector<vector<long long>> groups(){
        vector<long long> leaders(datasize),groupsize(datasize);
        vector<vector<long long>> res(datasize);
        for(long long i=0;i<datasize;i++){
            leaders[i]=find(i);
            groupsize[leaders[i]]++;
        }
        for(long long i=0;i<datasize;i++){
            res[i].reserve(groupsize[i]);
        }
        for(long long i=0;i<datasize;i++){
            res[leaders[i]].push_back(i);
        }
        res.erase(remove_if(res.begin(),res.end(),[&](vector<long long>& v){return v.empty();}),res.end());
        return res;
    }
    bool check(){return check_;}
};


int main(){
    int n,m;
    int mod=998244353;
    cin>>n>>m;
    WeightedUnionFind wuf(n);
    for(int i=0;i<m;i++){
        int c;
        cin>>c;
        if(c==0){
            int u,v,w;
            cin>>u>>v>>w;
            if(wuf.same(u,v)){
                if((((wuf.diff(u,v)%mod)+mod)%mod)==w){
                    cout<<1<<endl;
                }else{
                    cout<<0<<endl;
                }
            }else{
                cout<<1<<endl;
                wuf.merge(u,v,w);
            }
        }
        if(c==1){
            int u,v;
            cin>>u>>v;
            if(wuf.same(u,v)){
                cout<<((wuf.diff(u,v)%mod)+mod)%mod<<endl;
            }else{
                cout<<-1<<endl;
            }
        }
    }
    return 0;
}
