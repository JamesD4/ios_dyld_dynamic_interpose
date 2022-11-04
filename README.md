# iOS Dynamic Interpose PoC DYLIB

I had a problem I needed to solve which eventually lead me down a road to developing this PoC DYLIB that effectively replaces the implementation of a given C/C++ function at runtime.

Sort of like objective-c method swizzling, but for C/C++!

dynamic library code → `./main.c`

sample target binary code → `./target.c`

You can inject the dylib however you like, but for simplicity, you could use DYLD_INSERT_LIBRARIES to load the dylib at launch:

```
DYLD_INSERT_LIBRARIES=/interpose.dylib ./target
```

For injecting the dylib at runtime, you could try substrate or similar.
