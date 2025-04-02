
#include "Board.h"
#include <sstream>
#include <fstream>


Board::Board(int w, int h) : width(w), height(h){}

Board::Board(){};

Board::~Board(){
    for (Crawler* crawler: crawlers){
        delete crawler;
    }
}

void Board::addCrawler(int id, Position startPos, Direction dir, int size){
    Crawler* newCrawler = new Crawler(id, startPos, dir, size);
    crawlers.push_back(newCrawler);
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
                  << ", Size: " << crawler->getSize() << "\n";
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
    for (Crawler* crawler: crawlers) {
        if (crawler->isAlive()) {
            crawler->move(width, height);
        }
    }
}
void Board::displayAllBugPaths() const {
    for (const Crawler* crawler: crawlers) {
        std::cout <<crawler->getId()<<" Crawaler path: ";

        bool allPaths = true;
        for (const Position& pos: crawler->getPath()) {
            if (!allPaths)
                std::cout<<",";
                std::cout << "(" << pos.x << "," << pos.y << ")";
                allPaths = false;

        }


        if (!crawler->isAlive()) {
            bool found = false;
            for (const Crawler* other : crawlers) {
                if (other->isAlive() && other->getPosition().x == crawler->getPosition().x &&
                    other->getPosition().y == crawler->getPosition().y) {
                    std::cout << "Eaten by "<<other->getId();
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "Dead \n";
        }
        else {
            std::cout<<"Still alive";
        }
        std::cout<<std::endl;
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





