#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h" // defines PGSIZE
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *pageTester;
    int accessBitmap = 0;
    pageTester = malloc((sizeof(int))*PGSIZE);
    for (int i = 0; i < sizeof(int)-1; ++i)
    {
      pageTester[i*PGSIZE]=1; // accessed
    }
    for (int j = 0 ; j < sizeof(int) ; j++ ){
      printf("%d",pageTester[j*PGSIZE]);
    }
    printf("\n");
    if (pgaccess(pageTester,sizeof(int),&accessBitmap) < 0)
    {
      printf("error in pgaccess\n");
    }
    else
    {
        for (int i =0; i < sizeof(int); ++i)
        {
            printf("\nPage %d, accessed: %d\n",
                i, accessBitmap & (1<<i) && 1);
        }
    }

    return 0;
}
  
