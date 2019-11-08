#include "DFSGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, DFSGenerator, "DFS Generator (Required)");

std::random_device device;
std::default_random_engine engine{device()};

//fills the vector with all falses to keep track of where the maze generator has been
void DFSGenerator:: fillVector(Maze& maze)
{
    visited.resize(maze.getWidth());
    for(int i = 0; i < visited.size(); ++i)
    {
        visited[i].resize(maze.getHeight());
    }
}
//determines if all the cells in the maze have been visited
bool DFSGenerator:: allVisited(std::vector<std::vector<bool>> visited, Maze& maze)
{
    for(int r = 0; r < maze.getHeight(); ++r)
    {
        for(int c = 0; c < maze.getWidth(); ++c)
        {
            if(visited[c][r] != true)
                return false;
        }
     }
     return true;
}
//returns a vector of all possible directions it can go from the current cell
std::vector<Direction> DFSGenerator::generateDirections(int x, int y, Maze& maze, std::vector<std::vector<bool>> visited) //creates a vector of all possible directions
{
    std::vector<Direction> able;
    if(x - 1 >= 0)
        {    
            if(visited[x-1][y] == false)
               able.push_back(Direction::left);
        }
    if(x + 1 <= maze.getWidth()-1)
        {
            if(visited[x+1][y] == false)
               able.push_back(Direction::right);
        }
    if(y - 1 >= 0)
        {
            if(visited[x][y-1] == false)
                able.push_back(Direction::up);
        }
    if(y + 1 <= maze.getHeight()-1)
        {
            if(visited[x][y+1] == false)
                able.push_back(Direction::down);
        }
    return able;
}
//function that updates the cell's coordinates after moving in a given direction
std::pair<int, int> DFSGenerator:: newCell(int x, int y, Direction dir,  Maze& maze, std::vector<std::vector<bool>> visited) //increments or decrements x or y depending on next move and returns as a pair
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
    return std::pair<int, int>(x,y);
}
//recursive funnction that builds the maze by randomly choosing a direction and backtracking if it runs out of possible moves
void DFSGenerator:: buildMaze(int x, int y, Maze& maze, std::vector<std::vector<bool>> visited, std::stack<std::pair<int,int>> pastCells) //recursive call to remov walls and build maze
{
        if(allVisited(visited, maze))
            return;
        visited[x][y] = true;
        //printVector(maze, visited);
        std::vector<Direction> possible = generateDirections(x, y, maze, visited); 
        if(possible.size() == 0)
        {
            pastCells.pop();
            int oldX = pastCells.top().first;
            int oldY = pastCells.top().second;
            buildMaze(oldX, oldY, maze, visited, pastCells);
        }
        else
        {
            std::uniform_int_distribution<int> distribution{0, static_cast<int>(possible.size()-1)};
            int dir = distribution(engine);
            std::pair<int, int> newCoords = newCell(x, y, possible[dir], maze, visited);
            if(maze.wallExists(x,y,possible[dir]))
            {
                maze.removeWall(x, y, possible[dir]);
                pastCells.push(std::pair<int,int>(newCoords.first,newCoords.second));
                buildMaze(newCoords.first, newCoords.second, maze, visited, pastCells);
            }
        }
}
void DFSGenerator:: generateMaze(Maze& maze)
{
    maze.addAllWalls();
    fillVector(maze);
    pastCells.push(std::pair<int,int>(0,0));
    buildMaze(0, 0, maze, visited, pastCells);
}


