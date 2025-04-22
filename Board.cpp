
#include "Board.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <thread>
#include "Hopper.h"
#include "Jumper.h"
using namespace std;
using namespace chrono;

Board::Board(): width(GRID_SIZE), height(GRID_SIZE), grid(GRID_SIZE, std::vector<std::list<Bug*>>(GRID_SIZE)){}

Board::Board(int w, int h) : width(w), height(h), grid(h, std::vector<std::list<Bug*>>(w)){}

Board::~Board(){
    for (Bug* bug: bugs){
        delete bug;
    }
}

void Board::addBug(Bug* bug) {
    bugs.push_back(bug);

    int x = bug->getPosition().x;
    int y = bug->getPosition().y;

    grid[y][x].push_back(bug);
}

void Board::loadBugsFromFile(const std::string& filename = "bugs.txt") {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(iss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }

        if (tokens.size() != 6) continue;

        char type = tokens[0][0];
        int id = std::stoi(tokens[1]);
        int x = std::stoi(tokens[2]);
        int y = std::stoi(tokens[3]);
        int dirNum = std::stoi(tokens[4]);
        int size = std::stoi(tokens[5]);

        Direction dir;
        switch (dirNum) {
        case 1: dir = Direction::NORTH; break;
        case 2: dir = Direction::EAST; break;
        case 3: dir = Direction::SOUTH; break;
        case 4: dir = Direction::WEST; break;
        default: continue;
        }

        Position pos = {x, y};

        if (type == 'C') {
            addBug(new Crawler(id, pos, dir, size));
        } else if (type == 'H') {
            addBug(new Hopper(id, pos, dir, size));
        }
        else if (type == 'J') {
            addBug(new Jumper(id, pos, dir, size));
        }
    }

    file.close();
}

std::string directionToString(Direction dir) {
    switch (dir) {
    case Direction::NORTH: return "North";
    case Direction::EAST:  return "East";
    case Direction::SOUTH: return "South";
    case Direction::WEST:  return "West";
    default: return "Unknown";
    }
}

void Board::displayBoard() const {
    for (const auto& bug : bugs) {
        std::string typeName;
        std::string extra;

        if (auto hopper = dynamic_cast<const Hopper*>(bug)) {
            typeName = "Hopper";
            extra = " " + std::to_string(hopper->getHopLength());
        } else if (dynamic_cast<const Crawler*>(bug)) {
            typeName = "Crawler";
        }else if (dynamic_cast<const Jumper*>(bug)) {
            typeName = "Jumper";
        }
        else {
            typeName = "Unknown";
        }

        Position pos = bug->getPosition();

        std::cout << bug->getId() << " "
                  << typeName << " "
                  << "(" << pos.x << "," << pos.y << ") "
                  << bug->getSize() << " "
                  << directionToString(bug->getDirection())
                  << extra << " "
                  << (bug->isAlive() ? "Alive" : "Dead")
                  << "\n";
    }
}

Bug* Board::findBugById(const int id) const{
    for (Bug* bug: bugs){
        if (bug->getId() == id){
            return bug;
        }
    }
    return nullptr;
}

void Board::moveAll() {
    for (Bug* bug : bugs) {
        if (bug->isAlive()) {
            Position oldPos = bug->getPosition();
            grid[oldPos.y][oldPos.x].remove_if([bug](Bug* b) {
                return b == bug;
            });

            bug->move();

            Position newPos = bug->getPosition();
            std::cout << "Bug " << bug->getId() << " moved from (" << oldPos.x << "," << oldPos.y << ") to (" << newPos.x << "," << newPos.y << ")\n";
            grid[newPos.y][newPos.x].push_back(bug);
        }
    }
}

void Board::displayBugHistories() const {
    for (const Bug* bug : bugs) {
        std::string type = "Unknown";
        if (dynamic_cast<const Hopper*>(bug)) {
            type = "Hopper";
        } else if (dynamic_cast<const Crawler*>(bug)) {
            type = "Crawler";
        } else if (dynamic_cast<const Jumper*>(bug)) {
            type = "Jumper";
        }

        std::cout << bug->getId() << " " << type << " Path: ";

        const std::vector<Position>& path = bug->getPath();
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << "(" << path[i].x << "," << path[i].y << ")";
            if (i < path.size() - 1) {
                std::cout << ", ";
            }
        }

        if (bug->isAlive()) {
            std::cout << " - Alive";
        } else {
            std::cout << " - Eaten by " << bug->getKillerId();
        }

        std::cout << std::endl;
    }
}

void Board::writeLifeHistoryToFile() const {
    std::ofstream outfile("bugs_life_history.out");

    if (!outfile) {
        std::cerr << "Error opening file: bugs_life_history.out\n";
        return;
    }

    for (const Bug* bug : bugs) {
        std::string type;

        if (dynamic_cast<const Hopper*>(bug))      type = "Hopper";
        else if (dynamic_cast<const Crawler*>(bug)) type = "Crawler";
        else if (dynamic_cast<const Jumper*>(bug))  type = "Jumper";
        else                                        type = "Unknown";

        outfile << bug->getId() << " " << type << " path: ";

        const auto& path = bug->getPath();
        for (size_t i = 0; i < path.size(); ++i) {
            outfile << "(" << path[i].x << "," << path[i].y << ")";
            if (i < path.size() - 1) {
                outfile << ",";
            }
        }

        outfile << " - ";
        if (!bug->isAlive()) {
            outfile << "Eaten by " << bug->getKillerId();
        } else {
            outfile << "Still alive";
        }

        outfile << "\n";
    }

    outfile.close();
    std::cout << "Life history of all bugs written to: bugs_life_history.out\n";
}

void Board::tapBoard() {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            fightInCell(grid[row][col]);
        }
    }
}

void Board::displayCells() const {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::cout << "(" << row << "," << col << "): ";

            const std::list<Bug*>& cell = grid[row][col];
            bool hasAlive = false;
            bool first = true;

            for (const Bug* bug : cell) {
                if (!bug->isAlive()) continue;

                hasAlive = true;
                if (!first) std::cout << ", ";

                // Identify bug type
                if (dynamic_cast<const Crawler*>(bug)) {
                    std::cout << "Crawler " << bug->getId();
                } else if (dynamic_cast<const Hopper*>(bug)) {
                    std::cout << "Hopper " << bug->getId();
                }else if (dynamic_cast<const Jumper*>(bug)) {
                    std::cout << "Jumper " << bug->getId();
                }
                else {
                    std::cout << "UnknownBug " << bug->getId();
                }

                first = false;
            }

            if (!hasAlive) {
                std::cout << "empty";
            }

            std::cout << std::endl;
        }
    }
}


void Board::fightInCell(std::list<Bug*>& cell) {
    cell.remove_if([](Bug* bug) {
        return !bug->isAlive();
    });

    std::vector<Bug*> bugs;
    for (Bug* bug : cell) {
        if (bug->isAlive()) {
            bugs.push_back(bug);
        }
    }

    if (bugs.size() <= 1) return;

    int maxSize = 0;
    for (Bug* b : bugs) {
        if (b->getSize() > maxSize)
            maxSize = b->getSize();
    }

    std::vector<Bug*> contenders;
    for (Bug* b : bugs) {
        if (b->getSize() == maxSize)
            contenders.push_back(b);
    }

    Bug* dominant = (contenders.size() == 1)
        ? contenders[0]
        : contenders[rand() % contenders.size()];

    int eatenSize = 0;
    for (Bug* b : bugs) {
        if (b != dominant) {
            b->setAlive(false);
            b->setKillerId(dominant->getId());
            eatenSize += b->getSize();
        }
    }

    dominant->grow(eatenSize);


    std::cout << "Bug ID " << dominant->getId()
              << " wins the fight and grows by " << eatenSize
              << " to size " << dominant->getSize() << "." << std::endl;
}

int Board::countAliveBugs() const{
    int alive = 0;
    for (const Bug* bug : bugs) {
        if (bug->isAlive()) ++alive;
    }
    return alive;
}

void Board::runSimulation() {
    int round = 1;
    const int maxTime=10;
    const auto startTime=std::chrono::steady_clock::now();
    bool timeLimit = false;

    while (countAliveBugs() > 1) {

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime= std::chrono::duration_cast<std::chrono::seconds>(currentTime-startTime).count();
        if (elapsedTime>=maxTime) {
            std::cout << "\nMaximum simulation time reached. Both bugs win!\n";
            timeLimit = true;
            break;
        }
        std::cout << "\n--- Round " << round << " ---\n";

        moveAll();
        tapBoard();

        std::this_thread::sleep_for(milliseconds(100));
        ++round;
    }
    if (timeLimit) {
        std::cout << "\nSimulation complete! ";
    }
    else if (countAliveBugs() == 1) {
        for (Bug* bug : bugs) {
            if (bug->isAlive()) {
                std::string type;
                if (dynamic_cast<Hopper*>(bug)) type = "Hopper";
                else if (dynamic_cast<Crawler*>(bug)) type = "Crawler";
                else if (dynamic_cast<Jumper*>(bug)) type = "Jumper";
                else type = "Unknown";

                std::cout << "Last bug standing: " << type << " " << bug->getId() << "\n";
            }
        }
    } else {
        std::cout << "No bugs survived.\n";
    }

    writeLifeHistoryToFile();
    std::cout << "Life history saved to file.\n";
}

std::vector<Bug*> Board::getBugs() const {
    return bugs;
}

void Board::superBugFight(int x, int y) const{
    auto& cell = grid[y][x];
    for (Bug* bug : cell) {
        if (bug->isAlive()) {
            bug->setAlive(false);
        }
    }
}