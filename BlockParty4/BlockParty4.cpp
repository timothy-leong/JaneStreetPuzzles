#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

vector<vector<int>> square_grid(int length)
{
    return vector<vector<int>>(length, vector<int>(length));
}

int main()
{
    const int grid_length{10};
    // const int grid_length{5};

    // Create our grid
    auto grid{square_grid(grid_length)};

    // Input existing numbers
    vector<tuple<int, int, int>> initial_numbers{
        {0, 1, 3},
        {0, 5, 7},
        {1, 3, 4},
        {2, 8, 2},
        {3, 3, 1},
        {4, 0, 6},
        {4, 2, 1},
        {4, 3, 1},
        {4, 6, 1},
        {5, 1, 1},
        {5, 3, 5},
        {5, 4, 1},
        {5, 6, 1},
        {5, 7, 3},
        {5, 9, 6},
        {6, 2, 2},
        {6, 6, 2},
        {6, 7, 1},
        {6, 8, 2},
        {6, 9, 3},
        {7, 1, 2},
        {7, 2, 1},
        {7, 5, 1},
        {7, 7, 1},
        {7, 8, 4},
        {8, 6, 6},
        {8, 7, 2},
        {8, 8, 3},
        {9, 1, 6},
        {9, 4, 5},
        {9, 6, 4},
        {9, 8, 2}};

    // vector<tuple<int, int, int>> initial_numbers{
    //     {3, 0, 3},
    //     {2, 2, 4},
    //     {1, 4, 2},
    //     {2, 1, 1},
    //     {1, 3, 1},
    //     {0, 4, 4},
    //     {4, 2, 3},
    //     {4, 3, 1},
    //     {4, 4, 4}};

    // Input existing components
    vector<vector<pair<int, int>>> components{
        {{0, 0}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {3, 0}, {3, 1}, {4, 0}, {5, 0}, {6, 0}},
        {{5, 1}},
        {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {1, 4}},
        {{0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {1, 5}, {1, 8}, {1, 9}},
        {{1, 6}, {1, 7}, {2, 7}},
        {{2, 4}, {2, 5}},
        {{2, 2}, {2, 3}, {3, 3}},
        {{3, 2}, {4, 1}, {4, 2}, {5, 2}},
        {{6, 1}, {7, 0}, {7, 1}, {8, 0}, {8, 1}, {8, 2}, {9, 0}, {9, 1}, {9, 2}, {9, 3}},
        {{2, 6}, {3, 5}, {3, 6}, {3, 7}, {4, 7}, {4, 8}},
        {{3, 4}, {4, 3}, {4, 4}},
        {{4, 5}, {5, 5}},
        {{4, 6}},
        {{5, 3}, {6, 3}, {6, 4}, {6, 5}, {7, 4}},
        {{5, 4}},
        {{5, 6}, {5, 7}, {6, 6}},
        {{6, 2}, {7, 2}},
        {{6, 7}, {6, 8}, {6, 9}},
        {{2, 8}, {2, 9}, {3, 8}, {3, 9}, {4, 9}, {5, 8}, {5, 9}},
        {{7, 6}, {7, 9}, {8, 5}, {8, 6}, {8, 9}, {9, 6}, {9, 7}, {9, 8}, {9, 9}},
        {{7, 7}, {7, 8}, {8, 7}, {8, 8}},
        {{7, 3}, {8, 3}, {8, 4}, {9, 4}, {9, 5}},
        {{7, 5}}};

    // vector<vector<pair<int, int>>> components{
    //     {{0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2}},
    //     {{2, 1}},
    //     {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1}},
    //     {{3, 1}, {3, 2}, {4, 2}},
    //     {{4, 3}},
    //     {{2, 3}, {3, 3}, {3, 4}, {4, 4}},
    //     {{1, 3}},
    //     {{0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}}};

    // Map all cells to their component index
    auto cell_index{square_grid(grid_length)};

    for (int component_id{}; component_id < components.size(); ++component_id)
    {
        for (const auto &[row, col] : components[component_id])
            cell_index[row][col] = component_id;
    }

    // Visualise the components
    for (auto &row : cell_index)
    {
        for (auto &num : row)
        {
            ::cout << setw(3) << num << " ";
        }
        ::cout << endl;
    }
    ::cout << endl;

    // We need a function to get the component id of a cell
    auto get_component_id = [&cell_index](int row, int col) -> int
    {
        return cell_index[row][col];
    };

    // For each component, we need to track which numbers we've used
    vector<vector<bool>> numbers_used;
    numbers_used.reserve(components.size());
    for (auto &component : components)
    {
        numbers_used.push_back(vector<bool>(component.size()));
    }

    /*
        We need a function to check if a particular component needs a number n, that is,
        if n is less than or equal to the size of the component and no cell in that component currently has n
    */
    auto needs = [&numbers_used, &components](int component_id, int num) -> bool
    {
        return num <= static_cast<int>(components[component_id].size()) && !numbers_used[component_id][num - 1]; // the -1 is due to 0-indexing
    };

    /*
         We need a function to get all cells exactly distance k away from a given cell
    */
    auto distance_k_away = [&grid](const int row, const int col, int k) -> vector<pair<int, int>>
    {
        vector<pair<int, int>> result;
        for (int possible_row{max(0, row - k)}; possible_row <= min(static_cast<int>(grid.size()) - 1, row + k); ++possible_row)
        {
            const int column_offset{k - abs(row - possible_row)};
            for (int column : {col + column_offset, col - column_offset})
            {
                if (0 <= column && column < static_cast<int>(grid[0].size()))
                    result.push_back({possible_row, column});
            }
        }
        return result;
    };

    /*
          We also need a function to check if there's a cell with a
          particular number within distance less than k of a cell:
    */

    auto have_number_less_than_distance_k = [&distance_k_away, &grid](int row, int col, int desired_number, int k) -> bool
    {
        for (int distance{1}; distance < k; ++distance)
        {
            auto cells{distance_k_away(row, col, distance)};
            for (auto &[r, c] : cells)
            {
                if (grid[r][c] == desired_number)
                    return true;
            }
        }

        return false;
    };

    /*
        We need a function to insert a number into a grid. It should update the grid, and update `numbers_used`.
        We also need the undo-er for this function
    */
    auto insert = [&numbers_used, &get_component_id, &grid](int row, int col, int num) -> void
    {
        grid[row][col] = num;
        numbers_used[get_component_id(row, col)][num - 1] = true;
    };

    auto remove = [&numbers_used, &get_component_id, &grid](int row, int col) -> void
    {
        numbers_used[get_component_id(row, col)][grid[row][col] - 1] = false;
        grid[row][col] = 0;
    };

    // Insert pre-existing numbers into the grid and numbers_used map
    for (auto &[row, column, element] : initial_numbers)
        insert(row, column, element);

    // Define a backtracking function:
    function<bool(int, int)> backtrack = [&grid,
                                          &needs,
                                          &get_component_id,
                                          &components,
                                          &backtrack,
                                          &have_number_less_than_distance_k,
                                          &numbers_used,
                                          &insert,
                                          &remove,
                                          &distance_k_away](int component_id, int component_index) -> bool
    {
        // If you've reached past the last component, you've succeeded
        if (component_id == static_cast<int>(components.size()))
            return true;

        // If you've reached the end of one component, go to the next component
        if (component_index == static_cast<int>(components[component_id].size()))
            return backtrack(component_id + 1, 0);

        const auto &[row, col] = components[component_id][component_index];

        if (grid[row][col] == 0)
        {
            // We need to try every possible number
            const int size_of_component{static_cast<int>(components[component_id].size())};

            for (int possible_num{1}; possible_num <= size_of_component; ++possible_num)
            {
                if (!numbers_used[component_id][possible_num - 1] && !have_number_less_than_distance_k(row, col, possible_num, possible_num))
                {
                    // Try using this number
                    insert(row, col, possible_num);

                    if (backtrack(component_id, component_index))
                        return true;

                    remove(row, col);
                }
            }

            // If there is no number you can put here, it's a lost cause
            return false;
        }

        /*
            There's a number here, which means either it pre-existed, or some other number
            gave you this number. We cannot just delete it if we can't succeed in filling up the
            rest of the grid, we can only report the failure.
        */
        const int this_number{grid[row][col]};

        // Get all cells that are this_number away
        auto neighbours{distance_k_away(row, col, this_number)};

        // If any cells have this_number, we don't need to create any more of this_number. Move on
        for (auto &[r, c] : neighbours)
        {
            if (grid[r][c] == this_number)
                return backtrack(component_id, component_index + 1);
        }

        // Filter out all the cells that have a number other than 0
        for (const auto &[row, col] : neighbours)
        {
            if (grid[row][col] != 0)
                continue;

            if (!needs(get_component_id(row, col), this_number))
                continue;

            if (have_number_less_than_distance_k(row, col, this_number, this_number))
                continue;

            insert(row, col, this_number);

            // Go on with your life, see whether you succeed
            if (backtrack(component_id, component_index + 1))
                return true;

            // You failed, but you still have more neighbours to try
            remove(row, col);
        }

        // If you've tried all neighbours, and nobody can be this number away from you, it's a lost cause
        return false;
    };

    // Try solving the grid
    backtrack(0, 0);
    for (auto &row : grid)
    {
        for (auto &num : row)
        {
            ::cout << setw(3) << num << " ";
        }
        ::cout << endl;
    }

    // We need to multiply numbers along a row and sum up the products across rows:
    const int answer = accumulate(grid.begin(), grid.end(), 0,
                                  [](int sum, vector<int> &row)
                                  {
                                      return sum + accumulate(row.begin(), row.end(), 1, multiplies<int>());
                                  });

    ::cout << "Answer: " << answer << endl;
}
