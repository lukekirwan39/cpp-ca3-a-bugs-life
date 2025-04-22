#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>
#include <fstream>
#include <list>

class Board {
private:
    int width;
    int height;
    std::vector<Bug*> bugs;
    static const int GRID_SIZE = 10;
    std::vector<std::vector<std::list<Bug*>>> grid;

public:
    // constructors
    Board(int width, int height);
    Board();

    // destructor
    ~Board();

    void addBug(Bug* bug);
    void moveAll();
    std::vector<Position> getCrawlerPaths(int id) const;
    void displayBoard() const;
    void loadBugsFromFile(const std::string& filename);
    Bug* findBugById(int id) const;
    void displayBugHistories() const;
    void displayCells() const;
    void writeLifeHistoryToFile() const;
    static void fightInCell(std::list<Bug*>& cell);
    void tapBoard();
    int countAliveBugs() const;
    void runSimulation();
    std::vector<Bug*> getBugs() const;
    void superBugFight(int x, int y) const;

    // prevent copying
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif //BOARD_H
