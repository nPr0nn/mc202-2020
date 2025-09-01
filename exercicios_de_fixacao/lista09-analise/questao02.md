-- Versão recursiva:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define int long long

int binpow(int x, int n){
  if(n == 0) return 1;
  int res = binpow(x, n/2);
  if(n % 2) return res*res*x;
  return res*res;
}

int32_t main(){
  int x, n;
  scanf("%lld %lld", &x, &n);
  int pot = binpow(x, n);
  printf("%lld\n", pot);
}
```


-- Versão iterativa:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define int long long

int binpow(int x, int n){
  int res = 1;
  while(n > 0){
    if(n&1) res = res*x;
    x = x*x;
    n >>= 1;
  }
  return res;
}

int32_t main(){
  int x, n;
  scanf("%lld %lld", &x, &n);
  int pot = binpow(x, n);
  printf("%lld\n", pot);
}
```