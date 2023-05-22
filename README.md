# Chess-game

### [ 현재 상황 ]
- SFMLChessGame, ChessPiece class 구현
- CMakeLists.txt 변경 (경로 설정 필요 X)
<br>

### [ 주의사항 ]
※ 본인의 cmake-build-debug 폴더에 image 폴더를 넣어야 정상적인 이미지 출력 가능

※ 실행이 되지 않을 시 CMakeLists.txt 내에서 프로젝트 이름과 SFML 경로를 본인의 경로에 맞게 맞출 것
<br>
ex)
```
cmake_minimum_required(VERSION 3.24)
project(Chess_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess_game ChessBoardState.h ChessBoardState.cpp ChessPiece.cpp ChessPiece.h SFMLChessGame.h SFMLChessGame.cpp ChessGame.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
# 경로 맞추기
set(SFML_DIR "C:/Program Files/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

# 경로 맞추기
include_directories("C:/Program Files/SFML-2.5.1/include")
target_link_libraries(Chess_game sfml-system sfml-window sfml-graphics sfml-audio)
```

<br>

### [ History ]
- t000 <br>
: hello world SFML 구현
- t001 <br>
: 체스 기물의 움직임 함수 구현 <br>
: 프로그램 출력 결과로 확인 가능 <br>
: `chess.h`(struct ChessPiece, 전역함수), `chess.cpp` 추가
- t002 <br>
: GUI 버전으로 시각화 및 기물 선택시 이동 가능 위치 표시, 기물 이동 구현 <br>
: SFML을 이용한 프로그램 창으로 결과 확인 가능 <br>
: `ChessBoardState.h`(class로 구현), `ChessBoardState.cpp` 추가
- t003 <br>
: `ChessBoardState.h`에 vector와 unique_ptr을 이용한 기물 객체 생성 및 보관 멤버변수 추가 <br>
: `chess.h` 파일을 기능에 따라 ChessPiece와 ChessBoardState class로 분리 후 제거 <br>
: `ChessGame.cpp`에서 SFMLChessGame의 멤버함수 start를 호출하여 실행
: `SFMLChessGame.h`(class로 구현), `SFMLChessGame.cpp` 추가
