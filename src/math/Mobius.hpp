class Eratosthenes {
public:
    vector<bool> isprime;
    vector<int> minfactor;
    vector<int> mobius;

    Eratosthenes(int max_n) {
        isprime.resize(max_n + 1, true);
        mobius.resize(max_n + 1, 1);
        isprime[1] = false;

        for(int i = 2; i <= max_n; i++) {
            if(isprime[i] == false) continue;
            mobius[i] = -1;

            for(int j = i * 2; j <= max_n; j += i) {
                isprime[j] = false;
                if((j / i) % i == 0) mobius[j] = 0;
                else mobius[j] = -mobius[j];
            }
        }
    }
};
