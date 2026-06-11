struct Eratosthenes_seg{
    vector<bool> isp_s;
    vector<bool> isp;
    int sqrt_r;
    Eratosthenes_seg(ll l, ll r){
        sqrt_r = ceil(sqrt(r));
        isp_s.assign(sqrt_r, true);
        isp_s[0] = isp_s[1] = false;
        for(int i = 2; i < sqrt_r; i++) {
            if(isp_s[i] == false) continue;
            for(int j = i * 2; j < sqrt_r; j += i) {
                isp_s[j] = false;
            }
        }
        
        isp.assign(r - l, true);
        for(int i = 0; i < min(2LL, r - l); i++) if(l + i < 2) isp[i] = false;

        for (ll i = 2; i < sqrt_r; i++) {
            if (!isp_s[i]) continue;
            ll k = max(i, (l + i - 1) / i);
            for (ll j = k * i; j < r; j += i) {
                isp[j - l] = false;
            }
        }
    }
};