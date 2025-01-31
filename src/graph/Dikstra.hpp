vector<ll> Dikstra(vector<vector<pair<int,ll>>> &g, int s){
    vector<ll> dist(g.size(),LINF);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>> > que;
    que.push({0,s});
    while(!que.empty()){
        auto [cost, cur] = que.top();
        que.pop();
        if(dist[cur] != LINF) continue;
        dist[cur] = cost;
        for(auto [next, w] : g[cur])if(dist[next] == LINF){
            que.push({cost + w, next});
        }
    }
    return dist;
}
