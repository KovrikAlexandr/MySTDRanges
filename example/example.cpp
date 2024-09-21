#include <iostream>
#include <map>

#include <MyRanges.hpp>

int main() {
    std::map<int, std::string> m = { {1, "never"}, {2, "gonna"}, {3, "give"}, {4, "you"}, {5, "up"}};
    auto h = m  | my_std::value()
                | my_std::transform([](std::string s) {return "[" + s + "]"; }) 
                | my_std::reverse() 
                | my_std::transform([](std::string s) {return "{" + s + "}"; })
                | my_std::filter([](std::string s) -> bool{ return s.size() > 0; }); 
    for (auto s : h) {
        std::cout << s << '\n';
    }
}