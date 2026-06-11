class Eratosthenes {
public:
    vector<bool> isprime;
    vector<int> minfactor;
    vector<int> mobius;

    Eratosthenes(int max_n) {
        isprime.resize(max_n + 1, true);
        minfactor.resize(max_n + 1, -1);
        mobius.resize(max_n + 1, 1);

        //エラトステネスの篩
        isprime[1] = false;
        minfactor[1] = 1;

        for(int i = 2; i <= max_n; i++) {
            if(isprime[i] == false) continue;
            mobius[i] = -1;
            minfactor[i] = i;

            for(int j = i * 2; j <= max_n; j += i) {
                isprime[j] = false;
                if(minfactor[j] == -1) minfactor[j] = i;
                if((j / i) % i == 0) mobius[j] = 0;  // iで二回割り切れる
                else mobius[j] = -mobius[j];         // 1->-1 or -1->1
            }
        }
    }

    vector<pair<int, int>> factorize(int n) {
        assert(1 <= n && n < isprime.size());
        vector<pair<int, int>> ret;
        while(n > 1) {
            // first
            int a = minfactor[n];
            // second
            int b = 0;
            while(minfactor[n] == a) {
                b++;
                n /= a;
            }
            ret.push_back({a, b});
        }
        return ret;
    }

    vector<int> divisors(int n) {
        vector<int> ret({1});

        vector<pair<int, int>> pr = factorize(n);

        for(pair<int, int> p : pr) {
            int sz = ret.size();
            for(int i = 0; i < sz; i++) {
                int v = 1;
                for(int j = 0; j < p.second; j++) {
                    v *= p.first;
                    ret.push_back(ret[i] * v);
                }
            }
        }
        sort(ret.begin(),ret.end());
        return ret;
    }
};
