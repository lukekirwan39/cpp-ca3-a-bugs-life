
#include "Board.h"

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

        while (std::getline(iss, token, ',')){
            // trims the whitespace
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_first_not_of(" \t")+1);
            tokens.push_back(token);
        }

        if (tokens.size() != 6 || tokens[0] != "C"){
            std::cout << "Invalid line format: " << line << "\n";
            continue;
        }

        int id = std::stoi(tokens[1]);
        int x = std::stoi(tokens[2]);
        int y = std::stoi(tokens[3]);
        int dirNum = std::stoi(tokens[4]);
        int size = std::stoi(tokens[5]);

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




