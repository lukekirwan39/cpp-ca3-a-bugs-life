
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
        }
        else if (dynamic_cast<const Jumper*>(bug)) {
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

        if (!bug->isAlive()) {
            if (const Crawler* crawler = dynamic_cast<const Crawler*>(bug)) {
                std::cout << " Eaten by " << crawler->getKillerId();
            }
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
        std::string type = dynamic_cast<const Hopper*>(bug) ? "Hopper" :
                           dynamic_cast<const Crawler*>(bug) ? "Crawler" :
                            dynamic_cast<const Jumper*>(bug)? "Jumper": "Unknown";

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
            if (const Crawler* c = dynamic_cast<const Crawler*>(bug)) {
                outfile << "Eaten by " << c->getKillerId();
            } else {
                outfile << "Dead";
            }
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

    const auto startTime = steady_clock::now();
    bool timeLimit = false;

    map<int, int> killCount; // Track kills for each bug

    // Remove dead bugs from the list
    cell.remove_if([](Bug* bug) {
        Crawler* crawler = dynamic_cast<Crawler*>(bug);
        return (crawler && !crawler->isAlive());
    });

    // Collect all the alive crawlers
    std::vector<Crawler*> crawlers;
    for (Bug* bug : cell) {
        if (Crawler* crawler = dynamic_cast<Crawler*>(bug)) {
            if (crawler->isAlive()) {
                crawlers.push_back(crawler);
            }
        }
    }

    // Battle loop until only one bug remains
    while (crawlers.size() > 1 && !timeLimit) {
        int maxSize = 0;

        for (Crawler* c : crawlers) {
            if (c->getSize() > maxSize)
                maxSize = c->getSize();
        }


        std::vector<Crawler*> contenders;
        for (Crawler* c : crawlers) {
            if (c->getSize() == maxSize)
                contenders.push_back(c);
        }

        // Select a dominant bug
        Crawler* dominant = (contenders.size() == 1)
            ? contenders[0]
            : contenders[rand() % contenders.size()];

        // Track the kills and growth of the dominant bug
        int eatenSize = 0;
        for (Crawler* c : crawlers) {
            if (c != dominant) {
                eatenSize += c->getSize();
                c->setAlive(false);
                c->setKillerId(dominant->getId());
                killCount[dominant->getId()]++; // Increment kill count
            }
        }

        dominant->grow(eatenSize);

        // Check time limit (e.g., 10 seconds)
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime);
        if (elapsed.count() >= 1) {
            timeLimit = true;
        }
    }


    // Collect and sort the results based on kills and size
    std::vector<Bug*> aliveBugs;
    for (Bug* bug : cell) {
        if (bug->isAlive()) {
            aliveBugs.push_back(bug);
        }
    }


    // Print the results
    for (const auto& bug : aliveBugs) {
        cout << "Bug ID: " << bug->getId()
             << ", Kills: " << killCount[bug->getId()]
             << ", Size: " << bug->getSize() << endl;
    }
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
    const auto startTime = steady_clock::now();
    bool timeLimit = false;

    while (countAliveBugs() > 1 && !timeLimit) {
        std::cout << "\n--- Round " << round << " ---\n";

        moveAll();
        tapBoard();
        displayCells();

        std::this_thread::sleep_for(milliseconds(100));
        ++round;

        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime);
        if (elapsed.count() >= 1) {
            timeLimit = true;
        }
    }

    std::cout << "\nSimulation complete! ";
    if (countAliveBugs() == 1) {
        for (Bug* bug : bugs) {
            if (bug->isAlive()) {
                std::cout << "Last bug standing: Crawler " << bug->getId() << "\n";
            }
        }
    } else {
        std::cout << "No bugs survived. \n";
    }

    writeLifeHistoryToFile();
    std::cout << "Life history saved to file.\n";
}

std::vector<Bug*> Board::getBugs() const {
    return bugs;
}

void Board::superBugFight(int x, int y) {
    auto& cell = grid[y][x];
    for (Bug* bug : cell) {
        if (bug->isAlive()) {
            bug->setAlive(false); // Super-Bug defeats them
        }
    }
}
