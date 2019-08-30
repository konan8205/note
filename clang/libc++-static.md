# Link statically with libc++ in clang

## Requirement
- Headers and static library of libc++ and libc++abi are needed.

## Step
- Pass arguement `-nostdlib++`, `-nostdinc++` and `-pthread` to clang.
- Include libc++ header files via argument.
- Link the object files with `libc++.a` and `libc++abi.a` at last.

Note that static libraries must be linked in dependency order.

## Example
### Set environment variables
```
LIBCPP_INCLUDE="/usr/include/c++/v1"
LIBCPP_STATIC="/usr/lib/x86_64-linux-gnu/libc++.a /usr/lib/x86_64-linux-gnu/libc++abi.a"
```

### Create object file(s)
1. `clang++ -std=c++17 -nostdlib++ -nostdinc++ -pthread -I$LIBCPP_INCLUDE main.cpp $LIBCPP_STATIC`
2. `clang++ -std=c++17 -nostdinc++ -I$LIBCPP_INCLUDE -c main.cpp`

### Create a executable file
`clang++ -std=c++17 -nostdlib++ -pthread ./main.o $LIBCPP_STATIC`

## Reference
https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang1-nostdinc
https://stackoverflow.com/questions/46765489/how-to-static-link-with-clang-libc
