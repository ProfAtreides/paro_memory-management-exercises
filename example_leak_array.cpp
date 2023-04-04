#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void print_numbers(std::vector<int*> const& x) noexcept
{
    std::cout << x.size() << " elements: [ ";
    std::transform(x.begin(),
                   x.end(),
                   std::ostream_iterator<int>(std::cout, " "),
                   [](int const* item) -> int { return *item; });
    std::cout << "]" << std::endl;
}

std::vector<int*> create_numbers() noexcept
{
    constexpr int count = 32;

    std::vector<int*> numbers(count);
    for (int i = 0; i < count; ++i) { numbers[i] = new int(12 * i); }

    return numbers;
}

const void destroy_numbers(std::vector<int*> const& numbers) noexcept
{
    const size_t count = numbers.size();
    for (int i = 0; i < count; ++i)
    {
        delete numbers[numbers.size() - 1 - i];
    }
}

int main(int argc, char* argv[])
{
    std::vector<int*> nums = create_numbers();

    print_numbers(nums);

    destroy_numbers(nums);

    return 0;
}
