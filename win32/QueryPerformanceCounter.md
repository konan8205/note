# QueryPerformanceCounter

## 주의
Windows Vista 이전 버전의 경우, 멀티스레드 환경에서 스레드를 특정 코어에 고정한 후 호출하는 것이 안전하다.

## 참고
https://docs.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
https://docs.microsoft.com/en-us/windows/win32/dxtecharts/game-timing-and-multicore-processors
https://stackoverflow.com/questions/10894504/is-there-any-stdchrono-thread-safety-guaranty-even-with-multicore-context
https://bitbucket.org/sinbad/ogre/src/8fc4ef8aae3b/OgreMain/src/WIN32/OgreTimer.cpp
