// ax + by = gcd(a,b)
ll extGCD(ll a, ll b, ll& x, ll& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
// x = x0 + t * b/gcd(a,b)
// y = y0 - t * a/gcd(a,b)