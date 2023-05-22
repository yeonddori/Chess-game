#ifndef CHESS_GAME_SFMLCHESSGAME_H
#define CHESS_GAME_SFMLCHESSGAME_H

#include "ChessBoardState.h"

class SFMLChessGame {
public:
    enum class Mode {
        SelectPiece,
        SelectPosition,
        None,
    };

    SFMLChessGame();
    ~SFMLChessGame();

    void setChessBoardState(std::unique_ptr<ChessBoardState> boardState);

//    void setBoardRenderer(std::unique_ptr<IBoardRenderer> boardRenderer);

    //void setEventReceiver(std::unique_ptr<IEventReceiver> eventReceiver) {
    //
    //}

    void start();
    void draw();
    void handleUserInput(sf::Event& event);
protected:
    //void update() = 0;
    void clear();
    void show();
    void mainLoop();
    bool isStarted() { return started; }

protected:
    bool started = false;
    Mode mode = Mode::None;
    std::unique_ptr<ChessBoardState> m_boardState;
    sf::RenderWindow window;
    //
};

#endif //CHESS_GAME_SFMLCHESSGAME_H