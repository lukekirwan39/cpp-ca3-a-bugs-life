
#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>

class Board {
private:
    int width;
    int height;
    std::vector<Crawler*> crawlers;

public:
    Board(int width, int height);

    // destructor
    ~Board();

    void addCrawler(int id, Position startPos, Direction dir, int size);
    void moveAll();
    std::vector<Position> getCrawlerPaths(int id) const;
    void displayBoard() const;

    // prevent copying
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif //BOARD_H
