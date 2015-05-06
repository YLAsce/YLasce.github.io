#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

template<class T>
inline bool read(T &n)
{
    T x = 0, tmp = 1;
    char c = getchar();
    while((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if(c == EOF) return false;
    if(c == '-') c = getchar(), tmp = -1;
    while(c >= '0' && c <= '9') x *= 10, x += (c - '0'),c = getchar();
    n = x*tmp;
    return true;
}
template <class T>
inline void write(T n)
{
    if(n < 0)
    {
        putchar('-');
        n = -n;
    }
    int len = 0,data[20];
    while(n)
    {
        data[len++] = n%10;
        n /= 10;
    }
    if(!len) data[len++] = 0;
    while(len--) putchar(data[len]+48);
}

struct Tree
{
    int id;
    int height;

    bool operator < (const Tree &b)const
    {
        return height > b.height;
    }
}tree[50005];

struct Cuts
{
    int id;
    int height;
    int ans;
}cuts[50005];

bool cmp1(Cuts a,Cuts b)
{
    return a.height > b.height;
}

bool cmp2(Cuts a,Cuts b)
{
    return a.id < b.id;
}

bool isCut[50005];

int n,q;

int main()
{
    while(read(n) && read(q))
    {
        for(int i=1;i<=n;i++)
        {
            read(tree[i].height);
            tree[i].id = i;
        }

        for(int i=1;i<=q;i++)
        {
            read(cuts[i].height);
            cuts[i].id = i;
            cuts[i].ans = 0;
        }

        sort(tree+1,tree+1+n);
        sort(cuts+1,cuts+1+q,cmp1);

        int Index = 1;
        int tmpans = 0;

        memset(isCut,0,sizeof(isCut));

        for(int i=1;i<=q;i++)
        {
            while(Index <= n && tree[Index].height > cuts[i].height)
            {
                isCut[ tree[Index].id ] = true;

                if(isCut[ tree[Index].id-1 ] && isCut[ tree[Index].id+1 ]) tmpans--;
                else if(!isCut[ tree[Index].id-1 ] && !isCut[ tree[Index].id+1 ]) tmpans++;
                Index++;
            }
            cuts[i].ans = tmpans;
            //cout<<tmpans<<endl;
        }

        sort(cuts+1,cuts+1+q,cmp2);
        for(int i=1;i<=q;i++)
        {
            write(cuts[i].ans);
            putchar('\n');
        }
    }
    return 0;
}
