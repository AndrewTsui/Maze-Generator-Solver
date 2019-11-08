#include "DFSSolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, DFSSolver, "DFS Solver (Required)");

std::random_device dev;
std::default_random_engine eng{dev()};

//fills vector with all falses to keep track of where the maze solver has been
void DFSSolver::fillVector(MazeSolution& ms)
{
    visited.resize(ms.getWidth());
    for(int i = 0; i < visited.size(); ++i)
    {
        visited[i].resize(ms.getHeight());
    }
}
//function that generates a vector of possible directions the maze solver can go by checking if
//any adjacent cells have been visited and if any adjacent cells have walls in between them
std::vector<Direction> DFSSolver::generateDirections(int x, int y, const Maze& maze, MazeSolution& ms, std::vector<std::vector<bool>> visited)
{
    std::vector<Direction> able;
    if(x - 1 >= 0)
    {
        if(visited[x-1][y] == false && !maze.wallExists(x, y, Direction::left))
            able.push_back(Direction::left);
    }
    if(x + 1 <= ms.getWidth() - 1)
    {
        if(visited[x+1][y] == false && !maze.wallExists(x, y, Direction::right))
            able.push_back(Direction::right);
    }
    if(y - 1 >= 0)
    {
        if(visited[x][y-1] == false && !maze.wallExists(x, y, Direction::up))
            able.push_back(Direction::up);
    }
    if(y + 1 <= ms.getHeight() - 1)
    {
        if(visited[x][y+1] == false && !maze.wallExists(x, y, Direction::down))
            able.push_back(Direction::down);
    }
    return able;
}
//function that gets the new coordinates for the cell after moving in a given direction
std::pair<int,int> DFSSolver::newCell(int x, int y, Direction dir, const Maze& maze, MazeSolution& ms, std::vector<std::vector<bool>> visited)
{
    switch(dir)
    {
        case(Direction::up):
            y -= 1;
            break;
        case(Direction::right):
            x += 1;
            break;
        case(Direction::down):
            y += 1;
            break;
        case(Direction::left):
            x -= 1;
            break;
    }
    return std::pair<int,int>(x,y);
}
//recursive function that randomly moves maze solver in a direction and back tracking
//if it runs out of moves until it reaches the end point
void DFSSolver::traverseMaze(int x, int y, const Maze& maze, MazeSolution& ms, std::vector<std::vector<bool>> visited, std::stack<std::pair<int,int>> pastCells)
{
    if(ms.isComplete())
    {
        return;
    }
    visited[x][y] = true;
    std::vector<Direction> possible = generateDirections(x, y, maze, ms, visited);
    if(possible.size() == 0)
    {
        pastCells.pop();
        ms.backUp();
        int oldX = pastCells.top().first;
        int oldY = pastCells.top().second;
        traverseMaze(oldX, oldY, maze, ms, visited, pastCells);
    }
    else
    {
        std::uniform_int_distribution<int> distribution{0, static_cast<int>(possible.size()-1)};
        int dir = distribution(eng);
        std::pair<int, int> newCoords = newCell(x, y, possible[dir], maze, ms, visited);
        pastCells.push(std::pair<int,int>(newCoords.first, newCoords.second));
        ms.extend(possible[dir]);
        traverseMaze(newCoords.first, newCoords.second, maze, ms, visited, pastCells);
    }
}
void DFSSolver::solveMaze(const Maze& maze, MazeSolution& ms)
{
    fillVector(ms);
    pastCells.push(std::pair<int,int>(ms.getStartingCell().first, ms.getStartingCell().second));
    traverseMaze(ms.getStartingCell().first, ms.getStartingCell().second, maze, ms, visited, pastCells);
}
