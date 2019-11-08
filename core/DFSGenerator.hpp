#ifndef DFSGENERATOR_HPP
#define DFSGENERATOR_HPP
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>
#include <stack>
#include <utility>

class DFSGenerator: public MazeGenerator
{
private:
    std::vector<std::vector<bool>> visited;
    std::stack<std::pair<int,int>> pastCells;
public:
    virtual void generateMaze(Maze& maze);
    virtual void fillVector(Maze& maze);
    virtual std::pair<int,int> newCell(int x, int y, Direction dir, Maze& maze, std::vector<std::vector<bool>> visited);
    virtual void buildMaze(int x, int y, Maze& maze, std::vector<std::vector<bool>> visited, std::stack<std::pair<int,int>> pastCells);
    virtual std::vector<Direction> generateDirections(int x, int y, Maze& maze, std::vector<std::vector<bool>> visited);
    virtual bool allVisited(std::vector<std::vector<bool>> visited, Maze& maze);
};
#endif
