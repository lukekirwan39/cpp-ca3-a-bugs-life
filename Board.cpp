
#include "Board.h"

#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <bits/ranges_algo.h>
using namespace std;


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
    ifstream file(filename);

    if (!file){
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    string line;

    while (getline(file, line)){
        // parsing the line
        istringstream iss(line);
        string token;
        vector<std::string> tokens;

        while (getline(iss, token, ',')){
            // trims the whitespace
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }

        if (tokens.size() != 6 || tokens[0] != "C"){
            cout << "Invalid line format: " << line << "\n";
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
                    cout << "Invalid direction number: " << dirNum << "\n";
                    continue;
        }

        Position pos = {x, y};
        addCrawler(id, pos, dir, size);
    }

    file.close();
}

void Board::displayBoard() const {
    for (const auto& crawler : crawlers) {
        cout << "ID: " << crawler->getId()
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

    // map<Position, vector<Crawler*>>positionMap;
    // for (Crawler* crawler: crawlers) {
    //     if (crawler->isAlive()) {
    //         positionMap[crawler->getPosition()] = crawlers;
    //     }
    // }
    // for (auto& [position, bugs] : positionMap) {
    //     if (bugs.size()>1) {
    //         sort(bugs.begin(), bugs.end(),
    //         [](Crawler* crawler1, Crawler* crawler2) {
    //             return crawler1->getSize() > crawler2->getSize();
    //         });
    //
    //         int maxSize = bugs[0]->getSize();
    //         vector<Crawler*> maxsizebugs;
    //
    //         for (Crawler* bug: bugs) {
    //
    //             if (bug->getSize() == maxSize) {
    //                 maxsizebugs.push_back(bug);
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //         Crawler* winner;
    //         if (maxsizebugs.size() > 1) {
    //             srand(time(nullptr));
    //             winner = maxsizebugs[rand() % maxsizebugs.size()];
    //         }
    //         else {
    //             winner = maxsizebugs[0];
    //         }
    //
    //         // Calculate total size to add to winner
    //         int totalSize = 0;
    //         for (Crawler* bug : bugs) {
    //             if (bug != winner) {
    //                 totalSize += bug->getSize();
    //                 bug->setAlive(false);  // Mark as dead
    //             }
    //         }
    //         // Winner grows by sum of eaten bugs' sizes
    //         winner->setSize(winner->getSize() + totalSize);
    //
    //         cout << "At (" << position.x << "," << position.y << "): "
    //              << "Crawler " << winner->getId() << " ate " << bugs.size()-1
    //              << " bugs and grew to size " << winner->getSize() << endl;
    //     }
    // }
}
void Board::displayAllBugPaths() const {
    for (const Crawler* crawler: crawlers) {
        cout <<crawler->getId()<<" Crawaler path: ";

        bool allPaths = true;
        for (const Position& pos: crawler->getPath()) {
            if (!allPaths)
                cout<<",";
                cout << "(" << pos.x << "," << pos.y << ")";
                allPaths = false;

        }


        if (!crawler->isAlive()) {
            bool found = false;
            for (const Crawler* other : crawlers) {
                if (other->isAlive() && other->getPosition().x == crawler->getPosition().x &&
                    other->getPosition().y == crawler->getPosition().y) {
                    cout << "Eaten by "<<other->getId();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Dead \n";
        }
        else {
            cout<<"Still alive";
        }
        cout<<endl;
    }
}

void Board::writeLifeHistoryToFile() const {
    ofstream outfile ("bugs_life_history.out");

    if (!outfile) {
        cout << "Error opening file: " << "bugs_life_history.out" << "\n";
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
        outfile<<endl;
    }
    cout<<"life history of all bugs to a text file called bugs_life_history_date_time.out"<<endl;

}

void Board::displayAllCells() const {
    map<Position, vector<const Crawler*>> positionMap;

    // Populate the map
    for (const Crawler* crawler : crawlers) {
        if (crawler->isAlive()) {
            positionMap[crawler->getPosition()].push_back(crawler);
        }
    }

    // Display all cells
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Position currentPos{x, y};
            cout << "(" << x << "," << y << "): ";

            auto it = positionMap.find(currentPos);
            if (it == positionMap.end()) {
                cout << "empty";
            } else {
                bool firstBug = true;
                for (const Crawler* bug : it->second) {
                    if (!firstBug) cout << ", ";
                    cout << "Crawler " << bug->getId();
                    firstBug = false;
                }
            }
            cout << endl;
        }
    }
}