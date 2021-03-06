//
// Created by smart on 2020/10/14.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
//    0. 起始的空格
//    1. 符号位
//    2. 整数部分
//    3. 左侧有整数的小数点
//    4. 左侧无整数的小数点（根据前面的第二条额外规则，需要对左侧有无整数的两种小数点做区分）
//    5. 小数部分
//    6. 字符 e
//    7. 指数部分的符号位
//    8. 指数部分的整数部分
//    9. 末尾的空格
    unordered_map<int, unordered_map<char, int>> states {
            {
                0, {
                           {' ', 0},
                           {'s', 1},
                           {'d', 2},
                           {'.', 4}
                }
            },
            {
                1, {
                           {'d', 2},
                           {'.', 4},
                }
            },
            {
                2, {
                           {'d', 2},
                           {'.', 3},
                           {'e', 6},
                           {' ', 9}
                }
            },
            {
                3, {
                           {'d', 5},
                           {'e', 6},
                           {' ', 9}
                }
            },
            {
                4, {
                           {'d', 5}
                }
            },
            {
                5, {
                           {'d', 5},
                           {' ', 9}
                }
            },
            {
                6, {
                           {'s', 7},
                           {'d', 8}
                }
            },
            {
                7, {
                           {'d', 8}
                }
            },
            {
                8, {
                           {'d', 8},
                           {' ', 9}
                }
            },
            {
                9, {
                           {' ', 9}
                }
            }
    };

    char typeChar(char c) {
        if (c == ' ') {
            return ' ';
        } else if (c == '+' || c == '-') {
            return 's';
        } else if ('0' <= c && c <= '9') {
            return 'd';
        } else if (c == '.') {
            return '.';
        } else if (c == 'e' || c == 'E') {
            return 'e';
        } else {
            return '?';
        }
    }

public:
    bool isNumber(string s) {
        int state = 0;
        int res = 0;
        for (auto &&c : s) {
            auto type = typeChar(c);
            auto map = states[res];
            if (map.find(type) == map.end()) {
                // not found
                return false;
            }
            res = map[type];
        }
        return res == 2 || res == 5 || res == 8 || res == 9;
    }
};

TEST_CASE("offer_20", "[isNumber]") {
    auto s = Solution();

    REQUIRE(s.isNumber("+100"));
    REQUIRE(s.isNumber("5e2"));
    REQUIRE(s.isNumber("-123"));
    REQUIRE(s.isNumber("3.14125"));
    REQUIRE(s.isNumber("-1E-16"));
    REQUIRE(s.isNumber("01234"));

    REQUIRE(!s.isNumber("12e"));
    REQUIRE(!s.isNumber("1a3.14"));
    REQUIRE(!s.isNumber("1.2.3"));
    REQUIRE(!s.isNumber("+-5"));
    REQUIRE(!s.isNumber("12e+5.4"));
}
