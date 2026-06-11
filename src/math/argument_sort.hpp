auto cmp = [](pair<int,int> a, pair<int,int> b){
    int ah = (a.second < 0 || (a.second == 0 && a.first < 0));
    int bh = (b.second < 0 || (b.second == 0 && b.first < 0));
    if(ah != bh) return ah < bh;
    return (ll)a.first * b.second > (ll)a.second * b.first;
};

auto cmp = [&](int i, int j){
    int ah = (p[i].second < 0 || (p[i].second == 0 && p[i].first < 0));
    int bh = (p[j].second < 0 || (p[j].second == 0 && p[j].first < 0));
    if(ah != bh) return ah < bh;
    return (ll)p[i].first * p[j].second > (ll)p[i].second * p[j].first;
};