#ifndef DFSSOLVER_HPP
#define DFSSOLVER_HPP
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <utility>
#include <random>
#include <stack>
#include <vector>

class DFSSolver: public MazeSolver
{
private:
    std::vector<std::vector<bool>> visited;
    std::stack<std::pair<int,int>> pastCells;
public:
    virtual void solveMaze(const Maze& maze, MazeSolution& ms);
    virtual void traverseMaze(int x, int y, const Maze& maze, MazeSolution& ms, std::vector<std::vector<bool>> visited, std::stack<std::pair<int,int>> pastCells);
    virtual std::pair<int,int> newCell(int x, int y, Direction dir, const Maze& maze, MazeSolution& ms, std::vector<std::vector<bool>> visited);
    virtual std::vector<Direction> generateDirections(int x, int y, const Maze& maze, MazeSolution& ms, std::vector<std::vector<bool>> visited);
    virtual void fillVector(MazeSolution& ms);
};
#endif
