#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#import <mach/mach.h>
#include <sys/utsname.h>
#import <mach-o/loader.h>
#import <sys/mman.h>
#import <pthread.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <mach/error.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>

typedef char* (*DupProc)(const char*);

char* mystrdup(const char* in)
{
	return "lol";
}


struct dyld_interpose_tuple {
	const void* replacement;
	const void* replacee;
};

extern const struct mach_header __dso_handle;
extern void dyld_dynamic_interpose(const struct mach_header* mh, const struct dyld_interpose_tuple array[], size_t count);

__attribute__((constructor)) static void initialize(void) {
    struct dyld_interpose_tuple sTable[] = { {&mystrdup, &strdup} };

    if (dyld_dynamic_interpose == NULL) {
        printf("unable to resolve dyld_dynamic_interpose");
        exit(1);
    }

    printf("getting handle to main thread\n");
    void *main_thread = dlopen(NULL, RTLD_NOW);

    const void* symbol = dlsym(main_thread, "main");
    if (!symbol) {
        printf("unable to resolve symbol for main thread\n");
    }
    Dl_info info = {};
    if (!dladdr(symbol, &info)) {
        printf("unable to find mach header\n");
    }
    
    const struct mach_header *header = (struct mach_header *)info.dli_fbase;

    dyld_dynamic_interpose(header, sTable, 1);
}
