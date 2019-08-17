#include<stdio.h>
#include"bits.h"

int main(){
	int nf, input = 0, bit, res;
	Bitmap_t* bm;
	bitfunc funcArr[3] = {bitOn, bitOff, bitStatus};
	printf("enter number of features\n");
	scanf("%d", &nf);
	bm = createBitmap(nf);
	while (input != -1){
		printf("type 1 to print\ntype 2 for bitOn()\ntype 3 for bitOff()\ntype 4 for bitStatus()\ntype -1 to exit\n");
		scanf("%d", &input);
		switch (input){
			case 1: printBitmap (bm);
				break;
			case 2: printf("enter #bit to turn on\n");
				scanf("%d" ,&bit);
				res = useBitfunc (funcArr[0], bm, bit);
				switch (res){
					case 0: printf("done\n");
						break;
					case 1: printf("invalid bitmap\n");
						break;
					case 2: printf("bit too big (or bitmap too small)\n");
						break;	
				}	
				break;
			case 3: printf("enter #bit to turn off\n");
				scanf("%d" ,&bit);
				res = useBitfunc (funcArr[1], bm, bit);
				switch (res){
					case 0: printf("done\n");
						break;
					case 1: printf("invalid bitmap\n");
						break;
					case 2: printf("bit too big (or bitmap too small)\n");
						break;	
				}	
				break;
			case 4: printf("enter #bit to check\n");
				scanf("%d" ,&bit);
				res = useBitfunc (funcArr[2], bm, bit);
				switch (res){
					case 0: printf("off\n");
						break;
					case 1: printf("invalid bitmap\n");
						break;
					case 2: printf("bit too big (or bitmap too small)\n");
						break;	
					case 3: printf("on\n");
						break;
				}
			case -1: break;
			default: printf("invalid input\n");
		}
	}
	destroyBitmap(bm);
}
