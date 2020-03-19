# linux-structure
도서 실습과 그림으로 배우는 리눅스 구조 실습

## Chapter 2
### C언어 실행 파일에서 시스템 콜 확인
```bash
$ strace -o hello.log ./hello
$ cat hello.log
```

### CPU 의 사용자 모드 점유 / 커널 모드 점유 확인하기
1초 단위로 측정 : `sar -P ALL 1`

<b>%user</b> 가 사용자 모드, <b>%system</b>이 커널 모드

무한정 도는 loop 프로그램으로 사용자 모드 점유 확인해보기
```bash
$ ./loop &          # '&'는background 실행을 의미
$ sar -P ALL 1
$ ps -ef | grep loop    # loop의 프로세스 ID(PID)를 찾기
$ kill [loop의 PID]      # 찾은 PID를 통해서 프로세스 종료
``` 

시스템 콜(커널 모드 사용)을 하는 프로그램으로 커널 모드 점유 확인해보기
```bash
$ ./ppidloop &
$ sar -P ALL 1
$ ps -ef | grep ppidloop    # ppidloop의 프로세스 ID(PID)를 찾기
$ kill [ppidloop의 PID]      # 찾은 PID를 통해서 프로세스 종료
```

strace 로 확인한 프로세스 내의 시스템 콜에서 소요된 시간 확인하기
```bash
$ strace -T -o hello.log ./hello
$ cat hello.log
```

<b>ldd</b> : 프로그램이 어떠한 라이브러리를 링크하고 있는지 확인하기
echo 프로그램이 링크하고 있는 라이브러리 확인 : `$ ldd /bin/echo`

ppidloop 프로그램이 링크하고 있는 라이브러리 확인 : `$ ldd ppidloop`

## Chapter 3
리눅스에서 프로세스 생성 방법은 fork() 함수와 execve() 함수를 사용하여 만들 수 있다.
 
### fork() 함수
목적 : 같은 프로그램의 처리를 여러 개의 프로세스가 나눠서 처리하도록 한다.

fork() 함수를 실행하면 실행한 프로세스와 함께 새로운 프로세스 1개가 생성된다.
* 부모 프로세스 : 생성 전의 프로세스
* 자식 프로세스 : 새롭게 생성된 프로세스

리턴 값
* 부모 프로세스 : 자식 프로세스의 PID
* 자식 프로세스 : 0

### execve() 함수
목적 : 전혀 다른 프로그램을 실행할 때 사용
