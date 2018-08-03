bool PQA(ll D, ll &p, ll &q) //最小解
{
    ll d = sqrt(D);
    if ((d + 1) * (d + 1) == D) return false;
    if (d * d == D)             return false;
    if ((d - 1) * (d - 1) == D) return false;
    ll u = 0, v = 1, a = int(sqrt(D)), a0 = a, lastp = 1, lastq = 0;
    p = a, q = 1;
    do {
        u = a * v - u;
        v = (D - u * u) / v;
        a = (a0 + u) / v;
        ll thisp = p, thisq = q;
        p = a * p + lastp;
        q = a * q + lastq;
        lastp = thisp;
        lastq = thisq;
    } while ((v != 1 && a <= a0));
    p = lastp;
    q = lastq;
    if (p * p - D * q * q == -1) {
        p = lastp * lastp + D * lastq * lastq;
        q = 2 * lastp * lastq;
    }
    return true;
}
/* 求出最小的(x1,y1)后，使用如下迭代式求通解
 * x_{n}=x_{1}*x_{n-1}+dy_{1}*y_{n-1}
 * y_{n}=y_{1}*x_{n-1}+ x_{1}*y_{n-1}
*/

