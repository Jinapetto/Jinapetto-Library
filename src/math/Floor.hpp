ll llfloor(ll a, ll b) {
    if(b < 0) a = -a, b = -b;
    return a >= 0 ? a / b : (a + 1) / b - 1;
}