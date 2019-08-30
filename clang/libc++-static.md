# clang에서 libc++를 정적으로 링크하기

## 방법
1. -nostdlib++와 -nostdinc++ 및 -lpthread를 명령행에 추가한다.
2. libc++의 헤더 파일을 포함한다.
3. libc++.a 및 libc++abi.a 를 명령행의 제일 뒤에 추가한다.

## 잘못된 방법
1. gcc/clang의 명령 인자에 -nostdinc를 추가하지 않는다.
2. 명령행에 libc++.a 및 libc++abi.a를 소스 파일보다 앞에 추가한다.

## 예시
### 환경 변수 지정
```
LIBCPP_INCLUDE="/usr/include/c++/v1"
LIBCPP_STATIC="/usr/lib/x86_64-linux-gnu/libc++.a /usr/lib/x86_64-linux-gnu/libc++abi.a"
```

### 오브젝트 파일 생성
1. `clang++ -std=c++17 -nostdlib++ -nostdinc++ -pthread -I$LIBCPP_INCLUDE main.cpp $LIBCPP_STATIC`
2. `clang++ -std=c++17 -nostdinc++ -I$LIBCPP_INCLUDE -c main.cpp`

### 실행 파일 생성
`clang++ -std=c++17 -nostdlib++ -pthread ./main.o $LIBCPP_STATIC`

## 참고
https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang1-nostdinc
https://stackoverflow.com/questions/46765489/how-to-static-link-with-clang-libc
