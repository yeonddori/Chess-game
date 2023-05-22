#include "SFMLChessGame.h"

SFMLChessGame::SFMLChessGame() {
    std::unique_ptr<ChessBoardState> chessBoardState = std::make_unique<ChessBoardState>();
    setChessBoardState(std::move(chessBoardState));
}
SFMLChessGame::~SFMLChessGame() {
    started = false;
    window.close();
}
void SFMLChessGame::setChessBoardState(std::unique_ptr<ChessBoardState> boardState) {
    m_boardState = std::move(boardState);
    m_boardState->initialize();
}
void SFMLChessGame::start() {
    window.create(sf::VideoMode(640, 640), "Chess Game");
    started = true;
    mainLoop();
}
void SFMLChessGame::draw() {
    m_boardState->draw(window);
}
void SFMLChessGame::handleUserInput(sf::Event& event) {
    m_boardState->handleInput(window, event);
}
void SFMLChessGame::clear() {
    window.clear();
}
void SFMLChessGame::show() {
    window.display();
}
void SFMLChessGame::mainLoop() {
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleUserInput(event);
        }

        clear();
        draw();
        show();
    }
}