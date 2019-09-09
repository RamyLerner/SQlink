#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	void* handle;
	void (*f1) ();
	void (*f2) ();
	char* error;
	
	handle = dlopen("libN.so",RTLD_LAZY);
	if (!handle) {
            printf("handel error\n");
            return -1;
    }

    f1 = dlsym(handle, "lib1func");
    f2 = dlsym(handle, "lib2func");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    (*f1)();
    (*f2)();
    dlclose(handle);
}