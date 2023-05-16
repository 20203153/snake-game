# snake-game

## C++ 프로그래밍 팀프로젝트 과제

## 과제 빌드방법
### 필요 프로그램
- cmake
- make
- ncurses(-dev)
- compiler (Clang or gcc)
### 빌드 방법
```sh
cmake . && make
```

## 과제 마일스톤

### 1.
- [ ] NCurses Lib 함수 이용, 2차원 배열 Map을 Game 화면으로 표시하는 프로그램
- [ ] Map 사이즈는 최소 21*21
- [ ] Wall과 Immune Wall 구분.
- 비고: lib::ElementType 으로 Element를 구분할 예정.
```c++
enum ElementType {
    Wall = 1,
    ImmuneWall = 2,
    SnakeHead = 3,
    SnakeBody = 4,
};
```

### 2.
- [ ] 맵 위에 Snake를 표시.
- [ ] 화살표 입력받아 Snake가 움직임.
- 비고: lib::DirectionKey 으로 방향 설정 예정.
```c++
enum DirectionKey {
    up = 'w',
    left = 'a',
    right = 'd',
    down = 's'
};
```

### 3.
- [ ] Map 위 Growth Item 출현
- [ ] Map 위 Poison Item 출현

- 비고: GrothItem = 5, PoisonItem = 6 으로 lib::ElementType 설정.
- 비고2: 게임 규칙 #2 준수.

### 4.
- [ ] Map 위 한 쌍의 Gate가 출현
- [ ] Gate에 Snake가 통과할 수 있도록 수정.

- 비고: Gate = 7 으로 lib::ElementType 설정.
- 비고2: 게임 규칙 #3 #4 #5 준수.

### 5.
- [ ] 우측에 게임 점수 표시.
- [ ] Mission 달성 시 다음 Map으로 진행.
- [ ] Stage 는 최소 4단계, Map은 서로 다르게 구성.

- 비고: 게임 점수는 게임 규칙 #6 준수.

## 비고
### ncurses
http://www.gnu.org/software/ncurses/