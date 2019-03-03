//数论只会gcd
int gcd(int a,int b) {
    return b==0?a:gcd(b,a%b);
}