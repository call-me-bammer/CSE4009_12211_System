<<<<<<< HEAD
/* 
 * mm-implicit.c -  Simple allocator based on implicit free lists, 
 *                  first fit placement, and boundary tag coalescing. 
 *
 * Each block has header and footer of the form:
 * 
 *      31                     3  2  1  0 
 *      -----------------------------------
 *     | s  s  s  s  ... s  s  s  0  0  a/f
 *      ----------------------------------- 
 * 
 * where s are the meaningful size bits and a/f is set 
 * iff the block is allocated. The list has the following form:
 *
 * begin                                                          end
 * heap                                                           heap  
 *  -----------------------------------------------------------------   
=======
/*
 * mm-implicit.c -  Simple allocator based on implicit free lists,
 *                  first fit placement, and boundary tag coalescing.
 *
 * Each block has header and footer of the form:
 *
 *      31                     3  2  1  0
 *      -----------------------------------
 *     | s  s  s  s  ... s  s  s  0  0  a/f
 *      -----------------------------------
 *
 * where s are the meaningful size bits and a/f is set
 * iff the block is allocated. The list has the following form:
 *
 * begin                                                          end
 * heap                                                           heap
 *  -----------------------------------------------------------------
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
 * |  pad   | hdr(8:a) | ftr(8:a) | zero or more usr blks | hdr(8:a) |
 *  -----------------------------------------------------------------
 *          |       prologue      |                       | epilogue |
 *          |         block       |                       | block    |
 *
 * The allocated prologue and epilogue blocks are overhead that
 * eliminate edge conditions during coalescing.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "mm.h"
#include "memlib.h"

/*
<<<<<<< HEAD
 * If NEXT_FIT defined use next fit search, else use first fit search 
=======
 * If NEXT_FIT defined use next fit search, else use first fit search
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
 */
#define NEXT_FITx


<<<<<<< HEAD

/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* word size (bytes) */  
=======
/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* word size (bytes) */
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE  (1<<12)  /* initial heap size (bytes) */
#define OVERHEAD    8       /* overhead of header and footer (bytes) */

<<<<<<< HEAD
#define MAX(x, y) ((x) > (y)? (x) : (y))  
=======
#define MAX(x, y) ((x) > (y)? (x) : (y))
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)       (*(size_t *)(p))
<<<<<<< HEAD
#define PUT(p, val)  (*(size_t *)(p) = (val))  
=======
#define PUT(p, val)  (*(size_t *)(p) = (val))
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
<<<<<<< HEAD
#define HDRP(bp)       ((char *)(bp) - WSIZE)  
=======
#define HDRP(bp)       ((char *)(bp) - WSIZE)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))
/* $end mallocmacros */

/* Global variables */
<<<<<<< HEAD
static char *_heap_listp;  /* pointer to first block */  
=======
static char *_heap_listp;  /* pointer to first block */
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
#ifdef NEXT_FIT
static char *rover;       /* next fit rover */
#endif

static int _heap_ext_counter=0;

/* function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
<<<<<<< HEAD
static void printblock(void *bp); 
=======
static void printblock(void *bp);
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
static void checkblock(void *bp);

char* get_heap_listp() {
    return _heap_listp;
}
char* set_and_get_heap_listp(char* ptr) {
    _heap_listp = ptr;
    return _heap_listp;
}

<<<<<<< HEAD
/* 
 * mm_init - Initialize the memory manager 
 */
/* $begin mminit */
int mm_init(void) 
=======
/*
 * mm_init - Initialize the memory manager
 */
/* $begin mminit */
int mm_init(void)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
{
    /* create the initial empty heap */
    if (set_and_get_heap_listp(mem_sbrk(4*WSIZE)) == (void *)-1)
	return -1;
    PUT(get_heap_listp(), 0);                        /* alignment padding */
<<<<<<< HEAD
    PUT(get_heap_listp()+WSIZE, PACK(OVERHEAD, 1));  /* prologue header */ 
    PUT(get_heap_listp()+DSIZE, PACK(OVERHEAD, 1));  /* prologue footer */ 
=======
    PUT(get_heap_listp()+WSIZE, PACK(OVERHEAD, 1));  /* prologue header */
    PUT(get_heap_listp()+DSIZE, PACK(OVERHEAD, 1));  /* prologue footer */
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
    PUT(get_heap_listp()+WSIZE+DSIZE, PACK(0, 1));   /* epilogue header */
    set_and_get_heap_listp(get_heap_listp()+DSIZE);

#ifdef NEXT_FIT
    rover = get_heap_listp();
#endif

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
	return -1;
    return 0;
}
/* $end mminit */

<<<<<<< HEAD
/* 
 * mm_malloc - Allocate a block with at least size bytes of payload 
 */
/* $begin mmmalloc */
void *mm_malloc(size_t size) 
{
	//TODO
	return NULL;
} 
/* $end mmmalloc */

/* 
 * mm_free - Free a block 
=======
/*
 * mm_malloc - Allocate a block with at least size bytes of payload
 */
/* $begin mmmalloc */
void *mm_malloc(size_t size)
{

  get_heap_listp()


	return NULL;
}
/* $end mmmalloc */

/*
 * mm_free - Free a block
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
 */
/* $begin mmfree */
void mm_free(void *bp)
{
<<<<<<< HEAD
	//TODO
=======
  // 1. check block is allocated before.
  if (GET_ALLOC(HDRP(bp)) != 1)
    return;

  size_t size = GET_SIZE(HDRP(bp));
  // 2. a->f.
  PUT(HDRP(bp), PACK(size ,0));
  PUT(FTRP(bp), PACK(size, 0));

  // 3. check merge case conditions.
  coalesce(bp);
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
}

/* $end mmfree */

/*
 * mm_realloc - naive implementation of mm_realloc
 */
void *mm_realloc(void *ptr, size_t size)
{
<<<<<<< HEAD
	//TODO 
	return NULL;
}

/* 
 * mm_checkheap - Check the heap for consistency 
 */
void mm_checkheap(int verbose) 
=======
	//TODO
  if (size == 0)
    mm_free(ptr);



	return NULL;
}

/*
 * mm_checkheap - Check the heap for consistency
 */
void mm_checkheap(int verbose)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
{
    char *bp = get_heap_listp();

    if (verbose)
	printf("Heap (%p):\n", get_heap_listp());

    if ((GET_SIZE(HDRP(get_heap_listp())) != DSIZE) || !GET_ALLOC(HDRP(get_heap_listp())))
	printf("Bad prologue header\n");
    checkblock(get_heap_listp());

    for (bp = get_heap_listp(); GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
<<<<<<< HEAD
	if (verbose) 
	    printblock(bp);
	checkblock(bp);
    }
     
=======
	if (verbose)
	    printblock(bp);
	checkblock(bp);
    }

>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
    if (verbose)
	printblock(bp);
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
	printf("Bad epilogue header\n");
}

/* The remaining routines are internal helper routines */

<<<<<<< HEAD
/* 
 * extend_heap - Extend heap with free block and return its block pointer
 */
/* $begin mmextendheap */
static void *extend_heap(size_t words) 
=======
/*
 * extend_heap - Extend heap with free block and return its block pointer
 */
/* $begin mmextendheap */
static void *extend_heap(size_t words)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
{
    char *bp;
    size_t size;
    _heap_ext_counter++;
<<<<<<< HEAD
	
    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((bp = mem_sbrk(size)) == (void *)-1) 
=======

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((bp = mem_sbrk(size)) == (void *)-1)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
	return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* new epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}
/* $end mmextendheap */

<<<<<<< HEAD
/* 
 * place - Place block of asize bytes at start of free block bp 
=======
/*
 * place - Place block of asize bytes at start of free block bp
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
 *         and split if remainder would be at least minimum block size
 */
/* $begin mmplace */
/* $begin mmplace-proto */
static void place(void *bp, size_t asize)
/* $end mmplace-proto */
{
<<<<<<< HEAD
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (DSIZE + OVERHEAD)) { 
=======
    size_t csize = GET_SIZE(HDRP(bp));

    if ((csize - asize) >= (DSIZE + OVERHEAD)) {
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
	PUT(HDRP(bp), PACK(asize, 1));
	PUT(FTRP(bp), PACK(asize, 1));
	bp = NEXT_BLKP(bp);
	PUT(HDRP(bp), PACK(csize-asize, 0));
	PUT(FTRP(bp), PACK(csize-asize, 0));
    }
<<<<<<< HEAD
    else { 
=======
    else {
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
	PUT(HDRP(bp), PACK(csize, 1));
	PUT(FTRP(bp), PACK(csize, 1));
    }
}
/* $end mmplace */

<<<<<<< HEAD
/* 
 * find_fit - Find a fit for a block with asize bytes 
 */
static void *find_fit(size_t asize)
{
#ifdef NEXT_FIT 
=======
/*
 * find_fit - Find a fit for a block with asize bytes
 */
static void *find_fit(size_t asize)
{
#ifdef NEXT_FIT
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
    /* next fit search */
    char *oldrover = rover;

    /* search from the rover to the end of list */
    for ( ; GET_SIZE(HDRP(rover)) > 0; rover = NEXT_BLKP(rover))
	if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
	    return rover;

    /* search from start of list to old rover */
    for (rover = get_heap_listp(); rover < oldrover; rover = NEXT_BLKP(rover))
	if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
	    return rover;

    return NULL;  /* no fit found */
<<<<<<< HEAD
#else 
=======
#else
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
    /* first fit search */
    void *bp;

    for (bp = get_heap_listp(); GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
	if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
	    return bp;
	}
    }
    return NULL; /* no fit */
#endif
}

/*
 * coalesce - boundary tag coalescing. Return ptr to coalesced block
 */
<<<<<<< HEAD
static void *coalesce(void *bp) 
=======
static void *coalesce(void *bp)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1 */
	return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
	size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
	PUT(HDRP(bp), PACK(size, 0));
<<<<<<< HEAD
	PUT(FTRP(bp), PACK(size,0));
=======
	PUT(FTRP(bp), PACK(size, 0));
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
	size += GET_SIZE(HDRP(PREV_BLKP(bp)));
	PUT(FTRP(bp), PACK(size, 0));
	PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
	bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4 */
<<<<<<< HEAD
	size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
=======
	size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
	    GET_SIZE(FTRP(NEXT_BLKP(bp)));
	PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
	PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
	bp = PREV_BLKP(bp);
    }

#ifdef NEXT_FIT
    /* Make sure the rover isn't pointing into the free block */
    /* that we just coalesced */
<<<<<<< HEAD
    if ((rover > (char *)bp) && (rover < NEXT_BLKP(bp))) 
=======
    if ((rover > (char *)bp) && (rover < NEXT_BLKP(bp)))
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
	rover = bp;
#endif

    return bp;
}


<<<<<<< HEAD
static void printblock(void *bp) 
=======
static void printblock(void *bp)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
{
    size_t hsize, halloc, fsize, falloc;

    hsize = GET_SIZE(HDRP(bp));
<<<<<<< HEAD
    halloc = GET_ALLOC(HDRP(bp));  
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));  
    
=======
    halloc = GET_ALLOC(HDRP(bp));
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));

>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
    if (hsize == 0) {
	printf("%p: EOL\n", bp);
	return;
    }

<<<<<<< HEAD
    printf("%p: header: [%d:%c] footer: [%d:%c]\n", bp, 
	   hsize, (halloc ? 'a' : 'f'), 
	   fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
=======
    printf("%p: header: [%d:%c] footer: [%d:%c]\n", bp,
	   hsize, (halloc ? 'a' : 'f'),
	   fsize, (falloc ? 'a' : 'f'));
}

static void checkblock(void *bp)
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
{
    if ((size_t)bp % 8)
	printf("Error: %p is not doubleword aligned\n", bp);
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
	printf("Error: header does not match footer\n");
}
<<<<<<< HEAD


=======
>>>>>>> 2ab26fb35d2e2a4eabba1b924ebaf59cf2932e08
