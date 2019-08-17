#ifndef BITS_H
#define BITS_H
	
	struct bitmap{
		int nf;
		unsigned int *arr;
	};
	typedef struct bitmap Bitmap_t;

	typedef int (*bitfunc)(Bitmap_t*, int);
	int useBitfunc (bitfunc bf, Bitmap_t* bm, int n);

	Bitmap_t* createBitmap (int nf);
	void destroyBitmap(Bitmap_t* bm);
	int printBitmap(Bitmap_t* bm);
	int bitOn (Bitmap_t* bm, int n);
	int bitOff (Bitmap_t* bm, int n);
	int bitStatus (Bitmap_t* bm, int n);

#endif
