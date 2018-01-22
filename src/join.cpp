#include "globals.h"
#include "join_lists.h"
#include "sequence_tuples.h"

#define SHIFT2(K_SIZE) (64 - ((K_SIZE * 5) + 1))
//#define KEY(i) (i>>48)
#define KEY(i) (i >> SHIFT2(K_SIZE))
#define PROT(i) (((i << 32) >> 46))

void JOIN_TUPLES(uint64_t *list1, size_t n1, uint64_t *list2, size_t n2,
                 uint64_t **cnt) {

  size_t ptr1 = 0, ptr2 = 0, ptr3 = 0, ptr4 = 0;

  while (ptr1 < n1 && ptr2 < n2) {

    if (KEY(list1[ptr1]) < KEY(list2[ptr2])) {
      ptr1++;
    }

    else if (KEY(list1[ptr1]) > KEY(list2[ptr2])) {
      ptr2++;
    }

    else {
      // find equi-key range in list1
      ptr3 = ptr1 + 1;

      // IS THIS
      // ORIGINAL while( ptr3 < n1 && (KEY( list1[ptr3] ) != KEY( list1[ptr1] ))
      // ) { ptr3++ ; }
      while (ptr3 < n1 && (KEY(list1[ptr3]) == KEY(list1[ptr1]))) {
        ptr3++;
      }
      // find equi-key range in list2
      ptr4 = ptr2 + 1;
      // ORIGINAL while( ptr4 < n2 && (KEY( list2[ptr4] ) != KEY( list2[ptr2] ))
      // ) { ptr4++ ; }
      while (ptr4 < n2 && (KEY(list2[ptr4]) == KEY(list2[ptr2]))) {
        ptr4++;
      }

      for (size_t i = ptr1; i < ptr3; i++) {

        for (size_t j = ptr2; j < ptr4; j++) {
          cnt[PROT(list1[i])][PROT(list2[j])]++;
        }
      }
      ptr1 = ptr3;
      ptr2 = ptr4;
    }
  }
}
