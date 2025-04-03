
#include "Board.h"
#include <sstream>
#include <fstream>
#include <thread>

Board::Board(): width(GRID_SIZE), height(GRID_SIZE), grid(GRID_SIZE, std::vector<std::list<Crawler*>>(GRID_SIZE)){}

Board::Board(int w, int h) : width(w), height(h), grid(h, std::vector<std::list<Crawler*>>(w)){}

Board::~Board(){
    for (Crawler* crawler: crawlers){
        delete crawler;
    }
}

void Board::addCrawler(int id, Position startPos, Direction dir, int size){
    Crawler* newCrawler = new Crawler(id, startPos, dir, size);
    crawlers.push_back(newCrawler);

    int x = startPos.x;
    int y = startPos.y;

    grid[x][y].push_back(newCrawler);
}

void Board::loadCrawlersFromFile(const std::string& filename){
    std::ifstream file(filename);

    if (!file){
        std::cout << "Error opening file: " << filename << "\n";
        return;
    }

    std::string line;

    while (getline(file, line)){
        // parsing the line
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(iss, token, ',')){
            // trims the whitespace
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }

        if (tokens.size() != 6 || tokens[0] != "C"){
            std::cout << "Invalid line format: " << line << "\n";
            continue;
        }

        int id = stoi(tokens[1]);
        int x = stoi(tokens[2]);
        int y = stoi(tokens[3]);
        int dirNum = stoi(tokens[4]);
        int size = stoi(tokens[5]);

        Direction dir;
        switch (dirNum){
            case 1: dir = Direction::NORTH; break;
            case 2: dir = Direction::EAST; break;
            case 3: dir = Direction::SOUTH; break;
            case 4: dir = Direction::WEST; break;
            default:
                    std::cout << "Invalid direction number: " << dirNum << "\n";
                    continue;
        }

        Position pos = {x, y};
        addCrawler(id, pos, dir, size);
    }

    file.close();
}

void Board::displayBoard() const {
    for (const auto& crawler : crawlers) {
        std::cout << "ID: " << crawler->getId()
                  << ", Position: (" << crawler->getPosition().x << ", " << crawler->getPosition().y << ")"
                  << ", Direction: " << crawler->getDirectionAsString()
                  << ", Size: " << crawler->getSize() <<
                      ", Status: " << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

std::string Crawler::getDirectionAsString() const {
    switch (direction) {
        case Direction::NORTH: return "NORTH";
        case Direction::EAST:  return "EAST";
        case Direction::SOUTH: return "SOUTH";
        case Direction::WEST:  return "WEST";
        default: return "UNKNOWN";
    }
}

Crawler* Board::findBugById(const int id) const{
    for (Crawler* bug: crawlers){
        if (bug->getId() == id){
            return bug;
        }
    }
    return nullptr;
}

void Board::moveAll() {
    for (Crawler* crawler : crawlers) {
        if (crawler->isAlive()) {
            int oldX = crawler->getPosition().x;
            int oldY = crawler->getPosition().y;

            grid[oldY][oldX].remove_if([crawler](Crawler* c) {
                return c == crawler;
            });

            crawler->move(width, height);

            int newX = crawler->getPosition().x;
            int newY = crawler->getPosition().y;

            grid[newY][newX].push_back(crawler);
        }
    }
}

void Board::displayBugHistories() const {
    for (const Crawler* crawler : crawlers) {
        std::cout << crawler->getId() << " " << "Crawler" << " Path: ";

        for (const Position& pos : crawler->getPath()) {
            std::cout << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &crawler->getPath().back())
                std::cout << ",";
        }

        if (!crawler->isAlive()) {
            std::cout << " Eaten by " << crawler->getKillerId();
        }

        std::cout << std::endl;
    }
}

void Board::writeLifeHistoryToFile() const {
    std::ofstream outfile ("bugs_life_history.out");

    if (!outfile) {
        std::cout << "Error opening file: " << "bugs_life_history.out" << "\n";
    }

    for (const Crawler* crawler: crawlers) {
        outfile<<crawler->getId()<<"Crawler path : \n";
        bool first=true;
        for (const Position& pos: crawler->getPath()) {
            if (!first)
                outfile<<",";
            outfile<<"(" << pos.x << "," << pos.y << ")";
            first = false;
        }
        if (!crawler->isAlive()) {
            bool found = false;
            for (const Crawler* other: crawlers) {
                if (other->isAlive() && other->getPosition().x == crawler->getPosition().x &&
                    other->getPosition().y == crawler->getPosition().y) {
                    outfile<<"Eaten by "<<other->getId();
                    found = true;
                    break;
                }
            }
            if (!found)
                outfile<<"Dead";

        }
        else {
            outfile<<"Still alive";
        }
        outfile<<std::endl;
    }
    std::cout<<"life history of all bugs to a text file called bugs_life_history_date_time.out"<<std::endl;

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

            const std::list<Crawler*>& cell = grid[row][col];
            bool hasAlive = false;
            bool first = true;

            for (const Crawler* bug : cell) {
                if (!bug->isAlive()) continue;

                hasAlive = true;
                if (!first) std::cout << ", ";
                std::cout << "Crawler " << bug->getId();
                first = false;
            }

            if (!hasAlive) {
                std::cout << "empty";
            }

            std::cout << std::endl;
        }
    }
}


void Board::fightInCell(std::list<Crawler *> &cell){
    //filters out all the dead bugs
    cell.remove_if([](Crawler* c){
        return !c->isAlive();
    });

    if (cell.size() <= 1) return;

    //finding the max size
    int maxSize = 0;
    for (Crawler* c: cell){
        if (c->getSize() > maxSize)
            maxSize = c->getSize();
    }

    std::vector<Crawler*> contenders;
    for (Crawler* c: cell){
        if (c->getSize() == maxSize)
            contenders.push_back(c);
    }

    Crawler* dominant = contenders.size() == 1 ? contenders[0] : contenders[rand() % contenders.size()];

    int eatenSize = 0;
    for (Crawler* c: cell){
        if (c != dominant){
            eatenSize += c->getSize();
            c->setAlive(false);
            c->setKillerId(dominant->getId());
        }
    }

    dominant->grow(eatenSize);
}

int Board::countAliveBugs() const{
    int alive = 0;
    for (const Crawler* c : crawlers) {
        if (c->isAlive()) ++alive;
    }
    return alive;
}

void Board::runSimulation() {
    int round = 1;

    while (countAliveBugs() > 1) {
        std::cout << "\n--- Round " << round << " ---\n";

        moveAll();
        tapBoard();
        displayCells();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++round;
    }

    std::cout << "\nSimulation complete! ";
    if (countAliveBugs() == 1) {
        for (Crawler* c : crawlers) {
            if (c->isAlive()) {
                std::cout << "Last bug standing: Crawler " << c->getId() << "\n";
            }
        }
    } else {
        std::cout << "No bugs survived. \n";
    }

    writeLifeHistoryToFile();
    std::cout << "Life history saved to file.\n";
}
