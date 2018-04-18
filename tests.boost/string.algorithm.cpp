#include <boost/algorithm/string.hpp>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

using namespace boost::algorithm;

int main()
{
    auto s = "Boost C++ k\xfct\xfcphaneleri";
    auto upper_case1 = to_upper_copy(s);
    auto upper_case2 = to_upper_copy(s, std::locale{"Turkish"});
    std::locale::global(std::locale{"Turkish"});
    std::cout << upper_case1 << std::endl;
    std::cout << upper_case2 << std::endl;

    auto s2 = "Boost C++ Libraries";
    std::cout << erase_first_copy(s2, "s") << std::endl;
    std::cout << erase_nth_copy(s2, "s", 0) << std::endl;
    std::cout << erase_last_copy(s2, "s") << std::endl;
    std::cout << erase_all_copy(s2, "s") << std::endl;
    std::cout << erase_head_copy(s2, 5) << std::endl;
    std::cout << erase_tail_copy(s2, 9) << std::endl;

    // boost::iterator_range<std::string::iterator> r = find_first(s,
    // "C++");
    auto r = find_first(s, "C++");
    std::cout << r << std::endl;
    r = find_first(s, "xyz");
    std::cout << r << std::endl;

    std::vector<std::string> v{"Boost", "C++", "Libraries"};
    std::cout << join(v, " ") << std::endl;

    std::cout << replace_first_copy(s2, "+", "-") << std::endl;
    std::cout << replace_nth_copy(s2, "+", 0, "-") << std::endl;
    std::cout << replace_last_copy(s2, "+", "-") << std::endl;
    std::cout << replace_all_copy(s2, "+", "-") << std::endl;
    std::cout << replace_head_copy(s2, 5, "BOOST") << std::endl;
    std::cout << replace_tail_copy(s2, 9, "LIBRARIES") << std::endl;

    std::cout << "_" << trim_left_copy(s2) << "_" << std::endl;
    std::cout << "_" << trim_right_copy(s2) << "_" << std::endl;
    std::cout << "_" << trim_copy(s2) << "_" << std::endl;

    std::cout.setf(std::ios::boolalpha);
    std::cout << starts_with(s2, "Boost") << std::endl;
    std::cout << ends_with(s2, "Libraries") << std::endl;
    std::cout << contains(s2, "C++") << std::endl;
    std::cout << lexicographical_compare(s2, "Boost") << std::endl;

    v.empty();
    split(v, s, is_space());
    std::cout << v.size() << std::endl;

    r = find_regex(s, boost::regex{"\\w\\+\\+"});
    std::cout << r << std::endl;

    return 1;
}
