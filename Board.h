
#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Board {
private:
    int width;
    int height;
    std::vector<Crawler*> crawlers;
    static const int GRID_SIZE = 10;
    std::vector<std::vector<std::list<Crawler*>>> grid;

public:
    // constructors
    Board(int width, int height);
    Board();

    // destructor
    ~Board();

    void addCrawler(int id, Position startPos, Direction dir, int size);
    void moveAll();
    std::vector<Position> getCrawlerPaths(int id) const;
    void displayBoard() const;
    void loadCrawlersFromFile(const std::string& filename);
    Crawler* findBugById(int id) const;
    void displayBugHistories() const;
    void displayCells() const;
    void writeLifeHistoryToFile() const;
    static void fightInCell(std::list<Crawler*>& cell);
    void tapBoard();
    int countAliveBugs() const;
    void runSimulation();

    // prevent copying
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif //BOARD_H
