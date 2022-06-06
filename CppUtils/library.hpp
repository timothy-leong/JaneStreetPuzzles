#include <iomanip>
#include <vector>
using namespace std;

/**
 * @brief Checks if lower_bound <= num <= upper_bound
 *
 * @param num The number of interest
 * @param lower_bound The smallest number that num can be
 * @param upper_bound The largest number that num can be
 * @return true if lower_bound <= num <= upper_bound
 * @return false otherwise
 */
bool in_range(int num, int lower_bound, int upper_bound)
{
    return static_cast<unsigned int>(num - lower_bound) <= static_cast<unsigned int>(upper_bound - lower_bound);
}

/**
 * @brief Prints a matrix. Assumes that the element can be passed to std::cout.
 *
 * @tparam T the datatype of the elements in the matrix.
 * @param matrix A vector of vector of T.
 * @param width The width of each element (e.g. if width = 3, all integers less than 3 characters will be padded with spaces to occupy 3 spaces)
 */
template <typename T>
void print_matrix(vector<vector<T>> &matrix, int width = 3)
{
    for (auto &row : matrix)
    {
        for (auto &elem : row)
            ::cout << setw(3) << elem << " ";

        ::cout << endl;
    }
}

/**
 * @brief If the condition c evaluates to true, return r.
 * 
 */
#define return_if(c, r) \
    if (c)              \
    return r

/**
 * @brief If c is true, perform a void return
 *
 */
#define just_return_if(c) \
    if (c)                \
    return

/**
 * @brief If c is true, return true
 *
 */
#define return_true_if(c) return_if(c, true)

/**
 * @brief If c is true, return false
 *
 */
#define return_false_if(c) return_if(c, false)

/**
 * @brief If c is true, continue
 *
 */
#define continue_if(c) \
    if (c)             \
    continue
