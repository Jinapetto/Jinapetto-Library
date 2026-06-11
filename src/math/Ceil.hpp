ll llceil(ll a, ll b) {
    if(b < 0) a = -a, b = -b;
    return a > 0 ? (a - 1) / b + 1 : a / b;
}