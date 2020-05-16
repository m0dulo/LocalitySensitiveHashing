//
// Created by m0dulo on 2020/5/16/0016.
//

#ifndef LSH_UTLIS_H
#define LSH_UTLIS_H

#include "iostream"

using namespace std;
class LyxUtlis {
public:
    template<class T>
    static void _print(T arg) {
        cout << arg << " ";
    }

    template<class... Args>
    static void log(Args... args) {
        int arr[] = { (_print(args), 0)... };
        cout << endl;
    }

    static void split(const std::string& s, std::vector<std::string>& tokens,
               const std::string& delimiter = " ") {
        tokens.clear();
        std::string::size_type last_pos = s.find_first_not_of(delimiter, 0);
        std::string::size_type pos = s.find_first_of(delimiter, last_pos);
        while (std::string::npos != pos || std::string::npos != last_pos) {
            tokens.push_back(s.substr(last_pos, pos - last_pos));
            last_pos = s.find_first_not_of(delimiter, pos);
            pos = s.find_first_of(delimiter, last_pos);
        }
    }
};


#endif //LSH_UTLIS_H
