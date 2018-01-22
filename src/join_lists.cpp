#include "globals.h"
#include "join_lists.h"
#include "sequence_tuples.h"

#define SHIFT2(K_SIZE) (64 - ((K_SIZE * 5) + 1))
//#define KEY(i) (i>>48)
#define KEY(i) (i >> SHIFT2(K_SIZE))
#define PROT(i) (((i << 32) >> 46))

void JOIN_TUPLES(uint64_t *list1, size_t n1, uint64_t *list2, size_t n2,
                 uint16_t **count_matrix) {

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
      while (ptr3 < n1 && (KEY(list1[ptr3]) == KEY(list1[ptr1]))) {
        ptr3++;
      }
      // find equi-key range in list2
      ptr4 = ptr2 + 1;
      while (ptr4 < n2 && (KEY(list2[ptr4]) == KEY(list2[ptr2]))) {
        ptr4++;
      }

      for (size_t i = ptr1; i < ptr3; i++) {
        for (size_t j = ptr2; j < ptr4; j++) {
          count_matrix[PROT(list1[i])][PROT(list2[j])]++;
        }
      }
      ptr1 = ptr3;
      ptr2 = ptr4;
    }
  }
}

void JOIN_TUPLES2(uint64_t *list1, size_t n1, uint16_t **count_matrix) {
  size_t ptr1 = 0, ptr2 = 0;
  while (ptr1 < n1 && ptr2 < n1) {
    // find equi-key range start
    ptr2 = ptr1 + 1;
    while (ptr2 < n1 && (KEY(list1[ptr2]) == KEY(list1[ptr1]))) {
      // while(KEY( list1[ptr2] ) == KEY( list1[ptr1] )) {
      // count_matrix[ PROT( list1[ptr1] ) ][ PROT( list1[ptr2] ) ]++ ;
      ptr2++;
    }

    for (size_t i = ptr1; i < ptr2; i++) {
      for (size_t j = ptr1; j < ptr2; j++) {
        count_matrix[PROT(list1[i])][PROT(list1[j])]++;
      }
    }
    ptr1 = ptr2;
    // ptr1++;
  }
}

/*void JOIN_TUPLES2( uint64_t *list1 , size_t n1 , uint16_t **count_matrix ) {

    size_t ptr1 = 0 , ptr2 = 0 , ptr3 = 0, ptr4 = 0 ;

    while( ptr1 < n1 && ptr2 < n1 ) {

        //find equi-key range start
        ptr3 = ptr1 + 1 ;
        while( ptr3 < n1 && (KEY( list1[ptr3] ) == KEY( list1[ptr1] )) ) {
            ptr3++ ;
        }
        //find equi-key range end
        //ptr4 = ptr2 + 1 ;
        //while( ptr4 < n1 && (KEY( list1[ptr4] ) == KEY( list1[ptr2] )) ) {
        //    ptr4++ ;
        //}

        for( size_t i = ptr1 ; i < ptr3 ; i++ ) {
            //for( size_t j = ptr2 ; j < ptr4 ; j++ ) {
            for( size_t j = ptr1 ; j < ptr3 ; j++ ) {
                //count_matrix[ PROT( list1[i] ) ][ PROT( list1[j] ) ]++ ;
                count_matrix[ PROT( list1[i] ) ][ PROT( list1[j] ) ]++ ;
            }
        }
        ptr1 = ptr3;
        //ptr2 = ptr4;
    }
}*/
