
#include <localdef.h>

/* $XConsortium: Hash.c /main/6 1995/10/25 20:06:11 cde-sun $ */
/*
 *  @OPENGROUP_COPYRIGHT@
 *  COPYRIGHT NOTICE
 *  Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 *  Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 *  ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for
 *  the full copyright text.
 *  
 *  This software is subject to an open license. It may only be
 *  used on, with or for operating systems which are themselves open
 *  source systems. You must contact The Open Group for a license
 *  allowing distribution and sublicensing of this software on, with,
 *  or for operating systems which are not Open Source programs.
 *  
 *  See http://www.opengroup.org/openmotif/license for full
 *  details of the license agreement. Any use, reproduction, or
 *  distribution of the program constitutes recipient's acceptance of
 *  this agreement.
 *  
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 *  PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 *  WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 *  OR FITNESS FOR A PARTICULAR PURPOSE
 *  
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 *  NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 *  EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGES.
 */
/*
 * HISTORY
 */



#include "XmI.h"
#include "HashI.h"

/* Private data structures */

typedef struct _XmHashBucketRec {
  XmHashValue		  hashed_key;
  XmHashKey		  hash_key;
  XtPointer		  value;
  struct _XmHashBucketRec *next;
} XmHashBucketRec, *XmHashBucket;

typedef struct _XmHashTableRec {
  Cardinal		size;
  Cardinal		count;
  XmHashCompareProc	compare;
  XmHashFunction	hasher;
  XmHashBucket		*buckets;
} XmHashTableRec;

/* Static functions */
static XmHashBucket NewBucket(void);
static void FreeBucket(XmHashBucket);

/* Static data */

static XmHashBucket FreeBucketList = NULL;

/* Dumb default hash functions */

static Boolean 
Compare(XmHashKey x, XmHashKey y)
{
  return(x == y);
}

static XmHashValue
Hash(XmHashKey x)
{
  return((XmHashValue) (long) x);
}

/* Available table sizes,  should be prime numbers */

static XmConst int size_table[] = 
	{ 17, 31, 67, 131, 257, 521, 1031, 2053, 4099, 8209, 0 };

XmHashTable
_XmAllocHashTable(Cardinal size_hint, XmHashCompareProc cproc, 
		  XmHashFunction hproc)
{
  XmHashTable   table;
  int		i;

  table = (XmHashTable) XtMalloc(sizeof(XmHashTableRec));

  if (hproc)
    table -> hasher = hproc;
  else
    table -> hasher = Hash;

  if (cproc)
    table -> compare = cproc;
  else
    table -> compare = Compare;
  
  i = 0;

  /* Search size_table for size which is bigger than size_hint */
  while(size_table[i] != 0 &&
	size_table[i] < size_hint) i++;

  if (size_table[i] == 0) i--;

  table -> size = size_table[i];
  table -> count = 0;

  /* Create the array of pointers */
  table->buckets = (XmHashBucket*) XtCalloc(table->size, sizeof(XmHashBucket));

  return(table);
}

void
_XmFreeHashTable(XmHashTable table)
{
  int i;
  XmHashBucket bucket, next;

  for(i = 0; i < table -> size; i++) {
    bucket = table -> buckets[i];
    while(bucket) {
      next = bucket -> next;
      FreeBucket(bucket);
      bucket = next;
    }
  }

  XtFree((char*) table -> buckets);
  XtFree((char*) table);
}

void
_XmResizeHashTable(XmHashTable table, Cardinal new_size)
{
  int i, index;
  int oldsize;
  XmHashBucket current, last, next, new_h;

  i = 0;

  /* Search size_table for size which is bigger than size_hint */
  while(size_table[i] != 0 &&
	size_table[i] < new_size) i++;

  if (size_table[i] == 0) i--;

  /* New size should be larger,  otherwise return */
  if (size_table[i] <= table -> size) return;

  /* Realloc table */
  oldsize = table -> size;
  table -> size = size_table[i];
  table -> buckets = 
    (XmHashBucket*) XtRealloc((char*) table -> buckets, 
			      table -> size * sizeof(XmHashBucket));
  /* NULL new array entries */
  for(i = oldsize; i < table -> size; i++) table -> buckets[i] = NULL;

  /* Rearrange buckets,  this is a slow method,  but always
     correct.  We will end up rescanning any moved buckets */
  for(i = 0; i < table -> size; i++) {
    last = NULL;
    current = table -> buckets[i];
    while(current) {
      /* If this bucket goes somewhere else,  remove 
	 from this chain and reinstall */
      next = current -> next;
      index = current -> hashed_key % table -> size;
      if (index != i) {
	if (last != NULL)
	  last -> next = current -> next;
	else
	  table -> buckets[i] = current -> next;
	/* Now put at end of new bucket chain,  we must do
	   this to maintain ordering */
	current -> next = NULL;
	new_h = table -> buckets[index];
	if (new_h != NULL) {
	  while(new_h -> next != NULL) 
	    new_h = new_h -> next;
	  new_h -> next = current;
	} else {
	  table -> buckets[index] = current;
	}
      }
      current = next;
    }
  }
}

XtPointer
_XmGetHashEntryIterate(XmHashTable table, XmHashKey key, XtPointer *iterator)
{
  XmHashValue index;
  XmHashBucket entry;

  if (iterator && *iterator != NULL) {
    /* If iterating over a number of matching entries */
    entry = (XmHashBucket) *iterator;
    entry = entry -> next;
  } else { 
    /* Normal case */
    index = (table -> hasher(key)) % table -> size;
    entry = table -> buckets[index];
  }

  while(entry) {
    if (table -> compare(entry -> hash_key, key)) {
      if (iterator) *iterator = (XtPointer) entry;
      return(entry -> value);
    }
    entry = entry -> next;
  }

  if (iterator) *iterator = NULL;
  return(NULL);
}

void 
_XmAddHashEntry(XmHashTable table, XmHashKey key, XtPointer value)
{
  int hash;
  XmHashValue index;
  XmHashBucket entry;

  hash = table -> hasher(key);
  index = hash % table -> size;

  entry = NewBucket();
  entry -> hashed_key = hash;
  entry -> hash_key = key;
  entry -> value = value;
  entry -> next = table -> buckets[index];
  table -> buckets[index] = entry;
  table -> count++;
}

XtPointer
_XmRemoveHashEntry(XmHashTable table, XmHashKey key)
{
  XmHashValue index;
  XmHashBucket entry, last = NULL;

  index = (table -> hasher(key)) % table -> size;

  entry = table -> buckets[index];
  while(entry) {
    if (table -> compare(entry -> hash_key, key)) {
      if (last == NULL) {
	/* First entry is handled differently */
	table -> buckets[index] = entry -> next;
      } else {
	last -> next = entry -> next;
      }

      table -> count--;
      FreeBucket(entry);
      return(entry -> hash_key);
    }
    last = entry;
    entry = entry -> next;
  }
  return(NULL);
}

XtPointer 
_XmRemoveHashIterator(XmHashTable table, XtPointer *iterator)
{
  XmHashValue index;
  XmHashBucket entry, current, last = NULL;

  if (! iterator) return(NULL);

  entry = (XmHashBucket) *iterator;

  index = (table -> hasher(entry -> hash_key)) % table -> size;

  current = table -> buckets[index];

  while(current) {
    if (current == entry) {
      if (last == NULL) {
	/* First entry is handled differently */
	table -> buckets[index] = current -> next;
      } else {
	last -> next = current -> next;
      }

      table -> count--;
      FreeBucket(current);
      return(current -> hash_key);
    }
    last = current;
    current = current -> next;
  }
  return(NULL);
}

Cardinal
_XmHashTableCount(XmHashTable table)
{
  return(table -> count);
}

Cardinal
_XmHashTableSize(XmHashTable table)
{
  return(table -> size);
}

/****************************************************************/
/* _XmMapHashTable(table, proc, client_data)			*/
/* Iterate over entire hash table.  Mostly useful for debugging */
/* code using hash tables.					*/
/****************************************************************/

void 
_XmMapHashTable(XmHashTable table, XmHashMapProc proc, XtPointer client_data)
{
  int i;
  XmHashBucket entry, next;

  for(i = 0; i < table -> size; i++) {
    entry = table -> buckets[i];
    while(entry) {
      /* Can free key and value in this proc */
      next = entry -> next;

      /* Terminate processing if the XmHashMapProc return True. */
      if (proc (entry -> hash_key, entry -> value, client_data))
	return;

      entry = next;
    }
  }
}

/* Bucket management */
#define NUMBUCKETS 256

static XmHashBucket 
NewBucket(void)
{
  XmHashBucket rbucket;
  XmHashBucket buckets;
  int i;

  if (FreeBucketList == NULL) {
    /* Allocate alot of buckets at once to cut down on fragmentation */
    buckets = (XmHashBucket) XtMalloc(NUMBUCKETS * sizeof(XmHashBucketRec));

    /* Chain them together */
    for(i = 0; i < NUMBUCKETS; i++) buckets[i].next = &buckets[i+1];

    /* The last points to nothing */
    buckets[NUMBUCKETS - 1].next = (XmHashBucket) NULL;

    FreeBucketList = buckets;
  }

  rbucket = FreeBucketList;
  FreeBucketList = FreeBucketList -> next;

  return(rbucket);
}

static void
FreeBucket(XmHashBucket b)
{
  b -> next = FreeBucketList;
  FreeBucketList = b;
}


#ifdef DEBUG

void
_XmPrintHashTable(XmHashTable table)
{
  int i, max, total_in_use;
  int count;
  XmHashBucket entry;

  max = 0;
  total_in_use = 0;

  printf("size %d hash function %lx compare function %lx\n",
	 table->size, (unsigned long) table->hasher, 
	 (unsigned long) table->compare);

  for (i = 0; i < table -> size; i++) {
    entry = table -> buckets[i];
    count = 0;
    while(entry) {
      count++;
      entry = entry -> next;
    }
    if (count > 0) total_in_use++;
    if (count > max) max = count;
  }

  printf("total entries %d\n", table -> count);
  printf("total bucket chains in use %d or %d percent\n", total_in_use,
	 (total_in_use * 100)/table -> size);
  printf("bucket chain length %d average / %d max\n",
	 table -> count / total_in_use, max);
}

#endif
