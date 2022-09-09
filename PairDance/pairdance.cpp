#include <iostream>
#include <vector>

void print_solution(std::vector<std::pair<int, int>> &pairs, int designated_single)
{
    static int solutions_found = 0;
    std::cout << "Solution: " << ++solutions_found << std::endl;
    std::cout << "Single number: " << designated_single << std::endl;
    for (const auto &p : pairs)
    {
        std::cout << p.first << " joins with " << p.second << std::endl;
    }
    std::cout << "++++++++++++++++++++++++" << std::endl;
}

void enumerate(std::vector<std::vector<int>> &graph,
               std::vector<bool> &in_use,
               std::vector<std::pair<int, int>> &pairs,
               const int designated_single,
               const int curr_num = 1)
{
    if (curr_num == 16)
    {
        print_solution(pairs, designated_single);
        return;
    }

    // If this number is already in use, go to the next number
    if (in_use[curr_num])
    {
        enumerate(graph, in_use, pairs, designated_single, curr_num + 1);
        return;
    }

    // If this number is meant to be single, don't let it do any pairing
    if (curr_num == designated_single)
    {
        in_use[curr_num] = true;
        enumerate(graph, in_use, pairs, designated_single, curr_num + 1);
        in_use[curr_num] = false;
        return;
    }

    // Otherwise pair curr_num with all possible partners
    for (const int possible_partner : graph[curr_num])
    {
        if (!in_use[possible_partner])
        {
            in_use[curr_num] = true;
            in_use[possible_partner] = true;
            pairs.push_back({curr_num, possible_partner});
            enumerate(graph, in_use, pairs, designated_single, curr_num + 1);
            pairs.pop_back();
            in_use[possible_partner] = false;
            in_use[curr_num] = false;
        }
    }
}

int main()
{
    // Create the adjacency list representing reachable neighbours
    std::vector<std::vector<int>> graph = {
        {}, // 0 for padding
        {2, 3},
        {1, 3, 4, 5},
        {1, 2, 5, 6},
        {2, 5, 7, 8},
        {2, 3, 4, 6, 8, 9},
        {3, 5, 9, 10},
        {4, 8, 11, 12},
        {4, 5, 7, 9, 12, 13},
        {5, 6, 8, 10, 13, 14},
        {6, 9, 14, 15},
        {7, 12},
        {7, 8, 11, 13},
        {8, 9, 12, 14},
        {9, 10, 13, 15},
        {10, 14}};

    // Use a vector to record whether a number has been paired up or declared single
    std::vector<bool> in_use(16);

    // Use a vector to remember the pairings
    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(7);

    for (int single = 1; single <= 15; ++single)
        enumerate(graph, in_use, pairs, single);
}