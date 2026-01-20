#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

/*绝对值函数*/
int absVal(int x){
    if(x >> 31){
        return (~x) + 1;
    }
    else{
        return x;
    }
}

/*返回负值函数*/
int negate(int x){
    return (~x) + 1;
}

/*仅使用|和~，实现&*/
int bitAnd(int x,int y){
    return ~((~x) | (~y));
}

/*仅使用~和&，实现|*/
int bitOr(int x,int y){
    return ~((~x) & (~y));
}

/*仅使用~和&，实现^*/
int bitXor(int x,int y){
    int v1 = bitAnd(~x,y),v2 = bitAnd(x,~y);
    return bitOr(v1,v2);
}

/*判断x是否是最大正整数*/
int isTmax(int x){
    return !(~(x+(1<<31)));
}

/*统计x的二进制表示中的1的个数*/
/* 把 32 位分成 32 个 1-bit 计数器，然后两两合并成 16 个 2-bit 计数器，
再合并成 8 个 4-bit 计数器……最后得到一个 6-bit 的累加和。 */
int bitCount(int x){
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
    x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
    return x;
}

/*产生特定位数为1的二进制数*/
int bitMask(int highbit,int lowbit){
    if(highbit == 31){
        return 0xFFFFFFFF << lowbit;
    }
    int upper = ~0 << (highbit + 1);
    int lower = ~0 << lowbit;
    return ~upper & lower;
}

/*检查是否溢出*/
int addOK(int x,int y){
    int sum = x + y;
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int sign_s = sum >> 31;
    /*当x与y同号并且和的符号与其不同时发生溢出*/
    int same_sign = !(sign_x ^ sign_y);
    int diff_sign = sign_x ^ sign_s;
    return same_sign & diff_sign;
}

/*交换两个字节*/
int byteSwap(int x,int n,int m){
    int swap_a = bitMask(n*8+7,n*8);
    int temp_a = x & swap_a;
    int swap_b = bitMask(m*8+7,m*8);
    int temp_b = x & swap_b;
    /* 1. 把原x中这两字节清零 */
    x = x & ~(swap_a | swap_b);
    
    /* 2. 把两段字节交叉搬回去 */
    x = x | ((temp_a >> (n*8) & 0xFF) << (m*8)) |   // 原n字节 → m位置
        ((temp_b >> (m*8) & 0xFF) << (n*8));        // 原m字节 → n位置
    
    return x;
}

int absVal_standard(int x){
    return (x<0) ? -x : x;
}

int netgate_standard(int x){
    return -x;
}

int bitAnd_standard(int x,int y){
    return x & y;
}

int bitOr_standard(int x,int y){
    return x|y;
}

int bitXor_standard(int x,int y){
    return x^y;
}

int isTmax_standard(int x){
    if(x == 0x7FFFFFFF){
        return 1;
    }
    else{
        return 0;
    }
}

int bitCount_standard(int x){
    int ans = 0;
    for(int i=0;i<32;i++){
        ans += (x&1);
        x = x>>1;
    }
    return ans;
}

int bitMask_standard(int highbit,int lowbit){
    unsigned int ans = 0;
    for(int i = lowbit;i <= highbit;i++){
        ans = ans | (1u << i);
    }
    return ans;
}

int addOK_standard(int x,int y){
    long long xl = x, yl = y, sum = xl + yl;
    if(sum > __INT_MAX__ || sum <(int)0x80000000) return 1;
    else return 0;
}

int byteSwap_standard(int x,int n,int m){
    int temp = x;
    char*p = (char*)&temp;
    int a = *(p + n);
    int b = *(p + m);
    *(p + n) = b;
    *(p + m) = a;
    return temp;
}

/*产生随机正负数*/
int randnum(){
    int x = rand();
    if(rand() % 2){
        x = -x;
    }
    return x;
}

int main(){
    srand(time(0));

    printf("abs_test start...\n");
    for(int i=0;i<10;i++){
        int x = randnum();
        assert(absVal(x) == absVal_standard(x));
        printf(" %d passed\n",i);
    }
    printf("abs_test successed\n");

    printf("negate_test start...\n");
    for(int i=0;i<10;i++){
        int x = randnum();
        assert(negate(x) == netgate_standard(x));
        printf(" %d passed\n",i);
    }
    printf("negate_test successed\n");

    printf("bitAnd_test start...\n");
    for(int i=0;i<10;i++){
        int x = randnum();
        int y = randnum();
        assert(bitAnd(x,y) == bitAnd_standard(x,y));
        printf(" %d passed\n",i);
    }
    printf("bitAnd_test successed\n");

    printf("bitOr_test start...\n");
    for(int i=0;i<10;i++){
        int x = randnum();
        int y = randnum();
        assert(bitOr(x,y) == bitOr_standard(x,y));
        printf(" %d passed\n",i);
    }
    printf("bitOr_test successed\n");

    printf("bitXor_test start...\n");
    for(int i=0;i<10;i++){
        int x = randnum();
        int y = randnum();
        assert(bitXor(x,y) == bitXor_standard(x,y));
        printf(" %d passed\n",i);
    }
    printf("bitXor_test successed\n");

    printf("isTmax_test start...\n");
    for(int i = 0; i < 10; i++) {
        int x;
        if(i == 0) x = 0x7fffffff;
        else if(i == 1) x = -1;
        else x = randnum();
        assert(isTmax(x) == isTmax_standard(x));
        printf(" %d passed\n", i);
    }
    printf("isTmax successed\n");

    printf("bitcount_test started\n");
    for(int i=0;i<10;i++){
        int x = randnum();
        assert(bitCount(x) == bitCount_standard(x));
        printf(" %d passed\n",i);
    }
    printf("bitcount successed\n");

    printf("bitmask_test started\n");
    for(int i=0;i<10;i++){
        int x = rand() % 32,y = rand() % 32;
        if(x < y) {
            int t;
            t = x; x = y; y = t;
        }
        if(i < 3) x = 31;
        int temp = bitMask(x,y);
        assert(temp == bitMask_standard(x, y));
        printf(" %d passed\n", i);
    }
    printf("bit_mask successed\n");

    printf("addOK_test startrd\n");
    for(int i = 0; i < 10; i++) {
        int x = randnum(), y = randnum();
        assert(addOK(x, y) == addOK_standard(x, y));
        printf(" %d passed\n", i);
    }
    printf("addOK_test successed\n");

    printf("byteswap_test started\n");
    for(int i = 0; i < 10; i++) {
        int x = randnum(), n = rand() % 4, m = rand() % 4;
        assert(byteSwap(x, n, m) == byteSwap_standard(x, n, m));
        printf(" %d passed\n", i);
    }
    printf("byteswap_test successed\n");

    return 0;
}