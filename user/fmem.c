#include "kernel/types.h"
#include "user/user.h"

int main(void){
    uint64 free_bytes = freemem();
    printf("Approximately %l bytes free.\n", free_bytes);
    return 0;
}