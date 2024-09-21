#include <MyRanges.hpp>
#include <gtest/gtest.h>

#include <vector>
#include <forward_list>
#include <list>
#include <set>
#include <map>

TEST(TransformTestSuite, TransformTest) {
    std::vector<int> v = {2, 3, 4, 5};
    std::vector<int> expect = {4, 9, 16, 25};
    auto t = v | my_std::transform([](int x) { return x * x; });

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(TransformTestSuite, StringTest) {
    std::list<std::string> l = {"one", "two", "three"};
    std::vector<std::string> expect = {"(one)", "(two)", "(three)"};

    auto t = l | my_std::transform([](std::string s) -> std::string { return "(" + s + ")"; });

    std::vector<std::string> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(TransformTestSuite, MultiTransformTest) {
    std::vector<int> v = {2, 3, 4, 5};
    std::vector<int> expect = {14, 19, 26, 35};

    auto t = v | my_std::transform([](int x) { return x * x; }) | my_std::transform([](int x) { return x + 10; });

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(TransformTestSuite, ForwardListTest) {
    std::forward_list<int> v = {2, 3, 4, 5};
    std::vector<int> expect = {14, 19, 26, 35};

    auto t = v | my_std::transform([](int x) { return x * x; }) | my_std::transform([](int x) { return x + 10; });

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(TransformTestSuite, SetTest) {
    std::set<int> s = {2, 3, 4, 5};
    std::vector<int> expect = {14, 19, 26, 35};

    auto t = s | my_std::transform([](int x) { return x * x; }) | my_std::transform([](int x) { return x + 10; });

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(TransformTestSuite, ListTest) {
    std::list<int> l = {2, 3, 4, 5};
    std::vector<int> expect = {14, 19, 26, 35};

    auto t = l | my_std::transform([](int x) { return x * x; }) | my_std::transform([](int x) { return x + 10; });

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(ReverseTestSuite, ReverseTest) {
    std::vector<int> v = {1, 2, 4, 20};
    std::vector<int> expect = {20, 4, 2, 1};

    auto t = v | my_std::reverse();

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(ReverseTestSuite, DoubleReverseTest) {
    std::vector<int> v = {2, 3, 4, 5};
    std::vector<int> expect = v;

    auto t = v | my_std::reverse() | my_std::reverse();
    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(ReverseTestSuite, ListReverseTest) {
    std::list<int> l = {2, 3, 4, 5};
    std::vector<int> expect = {5, 4, 3, 2};

    auto t = l | my_std::reverse();

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(ReverseTestSuite, SetReverseTest) {
    std::set<int> s = {2, 3, 4, 5};
    std::vector<int> expect = {5, 4, 3, 2};

    auto t = s | my_std::reverse();

    std::vector<int> res;
    for (auto i : t) { res.push_back(i); }
    
    ASSERT_EQ(expect, res);
}

TEST(ReverseTestSuite, TransformAndReverseTest) {
    std::list<int> l = {1, 2, 3, 4};
    std::vector<int> expect = {16, 9, 4, 1};

    auto t1 = l | my_std::transform([](int x) { return x * x; }) | my_std::reverse();
    auto t2 = l | my_std::reverse() | my_std::transform([](int x) { return x * x; });

    std::vector<int> res1;
    for (auto i : t1) { res1.push_back(i); }

    std::vector<int> res2;
    for (auto i : t2) { res2.push_back(i); }
    
    ASSERT_EQ(expect, res2);
    ASSERT_EQ(expect, res1);
}

TEST(KeyTestSuite, KeyTest) {
    std::map<int, std::string> m = { {1, "one"}, {2, "two"}, {3, "hitler"} };
    auto k = m | my_std::key();

    std::vector<int> expect = {1, 2, 3};

    std::vector<int> res;
    for (auto i : k) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(KeyTestSuite, VectorOfPairsTest) {
    std::vector< std::pair<int, std::string> > v = { {1, "one"}, {2, "two"}, {3, "hitler"} };
    auto k = v | my_std::key();

    std::vector<int> expect = {1, 2, 3};

    std::vector<int> res;
    for (auto i : k) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(KeyTestSuite, KeyTransformReverseMapTest) {
    std::map<int, std::string> m = { {1, "one"}, {2, "two"}, {3, "hitler"} };
    auto k = m | my_std::key() | my_std::reverse() | my_std::transform([](int x) { return x * 10; });

    std::vector<int> expect = {30, 20, 10};

    std::vector<int> res;
    for (auto i : k) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(ValueTestSuite, ValueTest) {
    std::map<int, std::string> m = { {1, "never"}, {2, "gonna"}, {3, "give"}, {4, "you"}, {5, "up"}};
    auto k = m | my_std::value();

    std::string res;
    for (auto i : k) { res += (i + " "); }

    ASSERT_EQ(res, "never gonna give you up ");
}

TEST(ValueTestSuite, VectorOfPairsTest) {
    std::vector< std::pair<int, std::string> > v = { {1, "one"}, {2, "two"}, {3, "hitler"} };
    auto k = v | my_std::value();

    std::vector<std::string> expect = {"one", "two", "hitler"};

    std::vector<std::string> res;
    for (auto i : k) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(KeyTestSuite, ValueTransformReverseMapTest) {
    std::map<int, std::string> m = { {1, "one"}, {2, "two"}, {3, "hitler"} };
    auto k = m | my_std::value() | my_std::reverse() | my_std::transform([](std::string s) -> std::string { return "(" + s + ")"; });

    std::vector<std::string> expect = {"(hitler)", "(two)", "(one)"};

    std::vector<std::string> res;
    for (auto i : k) { res.push_back(i); }

    ASSERT_EQ(expect, res);
}

TEST(FilterTestSuite, FilterTest) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    auto f = v | my_std::filter([](int x) { return x % 2 == 0;});
    std::vector<int> expect = {2, 4, 6, 8};

    std::vector<int> res;
    for (auto i : f) {
        res.push_back(i);
    }
}

TEST(AllTestSuite, TransformReverseValueFilterStringsMegaTest) {
    std::map<int, std::string> m = { {1, "never"}, {2, "gonna"}, {3, "give"}, {4, "you"}, {5, "up"}};
    auto h = m  | my_std::value()
                | my_std::transform([](std::string s) {return "[" + s + "]"; }) 
                | my_std::reverse() 
                | my_std::filter([](std::string s) { return std::find(s.begin(), s.end(), 'e') != s.end(); });
    for (auto s : h) {
        std::cout << s << '\n';
    }
}
