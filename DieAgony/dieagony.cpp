#include <iostream>
#include <array>
#include <string>
#include <vector>

/**
 * Let a die be a six-element integer tuple denoting:
 * 0. The top face
 * 1. The front face
 * 2. The left face
 * 3. The right face
 * 4. The back face
 * 5. The bottom face
 * in that order.
 */
using die = const std::array<int, 6>;

const std::vector<std::vector<int>> grid{
    {57, 33, 132, 268, 492, 732},
    {81, 123, 240, 443, 353, 508},
    {186, 42, 195, 704, 452, 228},
    {-7, 2, 357, 452, 317, 395},
    {5, 23, -4, 592, 445, 620},
    {0, 77, 32, 403, 337, 452}};


// Flip the die from the square below to the square above.
die flip_up(die d)
{
    return {d[4], d[0], d[2], d[3], d[5], d[1]};
}

// Flip the die from the square above to the square below.
die flip_down(die d)
{
    return {d[1], d[5], d[2], d[3], d[0], d[4]};
}

// Flip the die from the square on the right to the square on the left.
die flip_left(die d)
{
    return {d[3], d[1], d[0], d[5], d[4], d[2]};
}

// Flip the die from the square on the left to the square on the right.
die flip_right(die d)
{
    return {d[2], d[1], d[5], d[0], d[4], d[3]};
}

die set_face(die d, const int face, const int number)
{
    die new_die = {d[0], d[1], d[2], d[3], d[4], d[5]};
    auto mutable_die = const_cast<std::array<int, 6> *>(&new_die);
    (*mutable_die)[face] = number;
    return new_die;
}

bool backtrack(const int row,
               const int col,
               die die,
               const int turn)
{
    // Base case: reached the top right square
    if (row == 0 && col == grid[0].size() - 1)
    {
        std::cout << row << " " << col << std::endl;
        return true;
    }

    // Case 1: Flip upwards
    if (row > 0)
    {
        if (die[4] == 0)
        {
            // Check if there is a suitable number for the back face
            const int candidate = (grid[row - 1][col] - grid[row][col]) / (turn + 1);
            if (grid[row][col] + (turn + 1) * candidate == grid[row - 1][col] &&
                backtrack(row - 1, col, flip_up(set_face(die, 4, candidate)), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
        else
        {
            // Check if the existing number for the back face works with the turn
            if (grid[row][col] + (turn + 1) * die[4] == grid[row - 1][col] &&
                backtrack(row - 1, col, flip_up(die), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
    }

    // Case 2: Flip downwards
    if (row + 1 < grid.size())
    {
        if (die[1] == 0)
        {
            // Check if there is a suitable number for the front face
            const int candidate = (grid[row + 1][col] - grid[row][col]) / (turn + 1);
            if (grid[row][col] + (turn + 1) * candidate == grid[row + 1][col] &&
                backtrack(row + 1, col, flip_down(set_face(die, 1, candidate)), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
        else
        {
            // Check if the existing number for the front face works with the turn
            if (grid[row][col] + (turn + 1) * die[1] == grid[row + 1][col] &&
                backtrack(row + 1, col, flip_down(die), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
    }

    // Case 3: Flip left
    if (col > 0)
    {
        if (die[3] == 0)
        {
            // Check if there is a suitable number for the right face
            const int candidate = (grid[row][col - 1] - grid[row][col]) / (turn + 1);
            if (grid[row][col] + (turn + 1) * candidate == grid[row][col - 1] &&
                backtrack(row, col - 1, flip_left(set_face(die, 3, candidate)), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
        else
        {
            // Check if the existing number for the front face works with the turn
            if (grid[row][col] + (turn + 1) * die[3] == grid[row][col - 1] &&
                backtrack(row, col - 1, flip_left(die), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
    }

    // Case 4: Flip right
    if (col + 1 < grid[0].size())
    {
        if (die[2] == 0)
        {
            // Check if there is a suitable number for the left face
            const int candidate = (grid[row][col + 1] - grid[row][col]) / (turn + 1);
            if (grid[row][col] + (turn + 1) * candidate == grid[row][col + 1] &&
                backtrack(row, col + 1, flip_right(set_face(die, 2, candidate)), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
        else
        {
            // Check if the existing number for the front face works with the turn
            if (grid[row][col] + (turn + 1) * die[3] == grid[row][col + 1] &&
                backtrack(row, col + 1, flip_right(die), turn + 1))
            {
                std::cout << row << " " << col << std::endl;
                return true;
            }
        }
    }

    // Report failure
    return false;
}

int main()
{
    backtrack(grid.size() - 1, 0, {0, 0, 0, 0, 0, 0}, 0);
}