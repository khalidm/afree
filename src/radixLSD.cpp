#include "globals.h"
#include "radixLSD.h"

#define nTopBytesToSort (((K_SIZE * 5) / 8) + 1 + 0)

#define nRadixPileSize (nTopBytesToSort * 256 * 8)

void SORT_TUPLES(uint64_t *list, const uint64_t nItemsInList) {

  if (nItemsInList <= 1)
    return; // trivial!

  // allocate auxillary array
  uint64_t *auxillaryList = new uint64_t[nItemsInList];
  assert(auxillaryList);

  uint64_t radixPileSizes[nTopBytesToSort][256];
  // memset(radixPileSizes, 0, 4096 ) ; // 2*256*8 bytes
  memset(radixPileSizes, 0, nRadixPileSize); // 2*256*8 bytes
  int r;

  // find pile boundaries for each radix-size iteration.
  for (uint64_t i = 0; i < nItemsInList; i++) {

    for (r = 0; r < nTopBytesToSort; r++) {

      // computing the pile boundaries only for the top
      // order bytes -- specified in nTopBytesToSort bytes.
      // This is because we only want to sort based
      // on the content in the top n order bytes
      radixPileSizes[r][(list[i] >> ((r + 8 - nTopBytesToSort) << 3) & 255)]++;
    }
  }

  // find start positions of each radix pile
  uint64_t t1, t2;
  for (int i = 0; i < nTopBytesToSort; i++) {

    t1 = radixPileSizes[i][0];
    t2 = 0;
    radixPileSizes[i][0] = 0;

    for (int j = 1; j < 256; j++) {

      t2 = radixPileSizes[i][j];
      radixPileSizes[i][j] = radixPileSizes[i][j - 1] + t1;
      t1 = t2;
    }
  }

  uint64_t radix, i;
  uint64_t *srcref;
  uint64_t *destref;

  for (r = 0; r < nTopBytesToSort; r++) {
    if (r % 2 == 0) {
      srcref = list;
      destref = auxillaryList;
    } else {
      srcref = auxillaryList;
      destref = list;
    }

    // handle case where all bytes at a depth
    // have same content. In which case, the list is sorted
    // and hence proceeding is pointless
    bool continueflag = false;
    for (i = 0; i < 256; i++) {

      if (radixPileSizes[r][i] != nItemsInList && radixPileSizes[r][i] != 0) {
        continueflag = true;
        break;
      }
    }

    if (!continueflag) {

      memcpy(destref, srcref, nItemsInList << 3);
      // memcpy( destref, srcref, nItemsInList<<K_SIZE) ;
      continue;
    }

    for (i = 0; i < nItemsInList; i++) {

      radix = (srcref[i] >> ((r + (8 - nTopBytesToSort)) << 3)) & 255;
      destref[radixPileSizes[r][radix]] = srcref[i];
      radixPileSizes[r][radix]++;
    }
  }

  // free auxillary array
  delete[] auxillaryList;
}
