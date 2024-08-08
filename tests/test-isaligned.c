#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "kernel/riscv.h"
// #define PGSHIFT 12  // bits of offset within a page
// #define PXSHIFT(level)  (PGSHIFT+(9*(level)))
// #define IS_ALIGNED(addr, level) ((addr) % (1 << PXSHIFT(level)) == 0)
// #define PG_SIZE(level) (1 << PXSHIFT(level))

// #define MAX_PGLEVEL 3


void assert_ok(int value, char * msg){
  if(!value) {
      fprintf(stderr, "[FAILED] %s\n", msg);
      exit(1);
  }

  printf("[OK] %s\n", msg);
}

int main(void){
  
  assert_ok(
    PG_SIZE(0) == 1 << 12, "Page size level 0"
  );

  assert_ok(
    PG_SIZE(1) == 1 << (12 + 9), "Page size level 1"
  );

  assert_ok(
    PG_SIZE(2) == 1 << (12 + 9 + 9), "Page size level 2"
  );

  char msg[1024];
  for(int level= 0; level <= PG_MAX_LEVEL; level++){
    sprintf(msg, "0 aligned with page size of level %d", level);
    assert_ok(IS_ALIGNED(0, level), msg);


    uint64_t pgsize = PG_SIZE(level);
    for(int i = 1; i <= 3; i++) {
      uint64_t addr = pgsize * i;


      for(int l = 0; l < PG_MAX_LEVEL; l++){
        int expected = l <= level;
        sprintf(
          msg, "%sIS_ALIGNED(%d * PG_SIZE(%d), %d))", expected ? "" : "!", i, level, l
        );
        assert_ok(IS_ALIGNED(addr, l) == expected, msg);
      }
    }

  }

  return 0;
}

