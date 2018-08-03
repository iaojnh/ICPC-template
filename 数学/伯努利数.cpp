/* 1^k+2^k+3^k+бнбн+n^k
 * O(k^2)
*/
struct Bell
{
    static const int N=::N;
    static const int MOD=::mod;
    int C[N][N],B[N];
    int pow_mod(int x,int k)
    {
        int ans=1;
        while(k)
        {
            if(k&1)ans=1LL*ans*x%mod;
            x=1LL*x*x%mod;
            k>>=1;
        }
        return ans;
    }
    void init()
    {
        rep(i,0,N)
        {
            C[i][0]=C[i][i]=1;
            rep(j,1,i)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
        }
        B[0]=1;
        rep(i,1,N)
        {
            B[i]=0;
            rep(j,0,i)B[i]=(1LL*B[i]-1LL*C[i+1][j]*B[j]%MOD+MOD)%MOD;
            B[i]=1LL*B[i]*pow_mod(C[i+1][i],MOD-2)%MOD;
        }
    }
    int cal(int n,int k)
    {
        int ans=pow_mod(k+1,MOD-2),sum=0;
        rep(i,0,k+1)sum=(sum+1LL*C[k+1][i]*B[i]%MOD*pow_mod(n,k+1-i)%MOD)%MOD;
        return 1LL*ans*sum%MOD;
    }
}B;