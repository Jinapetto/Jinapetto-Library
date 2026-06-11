struct AhoCora{
    vector<vector<int>> g;
    vector<int> fail;
    vector<int> match;
    int char_sz, margin;

    AhoCora(int _char_sz, int _margin) : char_sz(_char_sz), margin(_margin){
        g.assign(1, vector<int>(char_sz, -1));
        match.assign(1, 0);
    }

    void add(string& s){
        _add(s, 0, 0);
    }

    void build(){
        int n = g.size();
        fail.assign(n, -1);
        fail[0] = 0;

        queue<int> que;

        for(int i = 0;i < char_sz;i++){
            if(g[0][i] == -1){
                g[0][i] = 0;
            }else{
                fail[g[0][i]] = 0;
                que.push(g[0][i]);
            }
        }

        while(!que.empty()){
            int cur = que.front();
            que.pop();

            match[cur] += match[fail[cur]];

            for(int i = 0;i < char_sz;i++){
                if(g[cur][i] == -1){
                    g[cur][i] = g[fail[cur]][i];
                }else{
                    fail[g[cur][i]] = g[fail[cur]][i];
                    que.push(g[cur][i]);
                }
            }
        }
    }

    private:

    void _add(string& s, int cur, int idx){
        if((int)s.size() == idx){
            match[cur]++;
            return;
        }
        if(g[cur][s[idx] - margin] == -1){
            g[cur][s[idx] - margin] = g.size();
            g.push_back(vector<int>(char_sz, -1));
            match.push_back(0);
        }
        _add(s, g[cur][s[idx] - margin], idx + 1);
    }
};
