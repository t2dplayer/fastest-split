#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <sstream>
#include <string_view>

using std::cout;
using Vector = std::vector<std::string_view>;
using Lambda = std::function<Vector(std::string_view, char)>;

Vector split_01(const std::string_view str,
                char delimiter) {
    Vector result;
    result.reserve(str.size());
    int start = 0, end = 0;
    for (const auto& c: str) {
        if (c != delimiter) {
            ++end;continue;
        }
        result.push_back(str.substr(start, end - start));
        start = ++end;
    }
    if (start <= str.size()) {
        result.push_back(str.substr(start, end - start));
    }
    return result;
}

Vector split_02(const std::string_view str,
                char delimiter) {
    Vector result;
    int start = 0, end = 0;
    int totalDelimiter = 0;
    for (const auto& c: str) {
        if (c == totalDelimiter) ++totalDelimiter;
    }
    result.reserve(totalDelimiter);
    for (const auto& c: str) {
        if (c != delimiter) {
            ++end;continue;
        }
        result.push_back(str.substr(start, end - start));
        start = ++end;
    }
    if (start <= str.size()) {
        result.push_back(str.substr(start, end - start));
    }
    return result;
}

//#include <iterator>
//Vector split_03(const std::string_view& str, char delimiter)
//{
//    Vector result;
//    result.reserve(str.size());
//    std::istringstream iss(str);
//    std::copy(std::istream_iterator<std::string>(iss),
//         std::istream_iterator<std::string>(),
//         std::back_inserter(result));
//    return result;
//}

//Vector split_04(const std::string_view& str,
//              char delim = ' ')
//{
//    Vector cont;
//    cont.reserve(str.size());
//    std::stringstream ss(str);
//    std::string token;
//    while (std::getline(ss, token, delim)) {
//        cont.push_back(token);
//    }
//    return cont;
//}

#include <algorithm>
#include <iterator>

Vector split_05(const std::string_view& str,
              char delim = ' ')
{
    Vector cont;
    cont.reserve(str.size());
    std::size_t current, previous = 0;
    current = str.find(delim);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
    return cont;
}


Vector split_06(const std::string_view& str,
                char delims = ' ')
{
    Vector cont;
    cont.reserve(str.size());
    std::size_t current, previous = 0;
    current = str.find_first_of(delims);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delims, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
    return cont;
}

//typedef void(*split_fn)(const char *, size_t, void *);

//void split(const char *str, char sep, split_fn fun, void *data)
//{
//    unsigned int start = 0, stop;
//    for (stop = 0; str[stop]; stop++) {
//        if (str[stop] == sep) {
//            fun(str + start, stop - start, data);
//            start = stop + 1;
//        }
//    }
//    fun(str + start, stop - start, data);
//}

//template <class Container>
//void add_to_container(const char *str, size_t len, void *data)
//{
//    Container *cont = static_cast<Container*>(data);
//    cont->push_back(std::string(str, len));
//}

//Vector split_07(const std::string_view& str,
//                char delim = ' ')
//{
//    Vector cont;
//    cont.reserve(str.size());
//    split(str.c_str(), delim, static_cast<split_fn>(add_to_container<Vector>), &cont);
//    return cont;
//}

std::ostream& operator<<(std::ostream& os, const Vector& c) {
   os << "[";
    for (size_t i = 0; i < c.size(); ++i) {
        os << c[i];
        if (i < c.size() - 1) {
            os << ", ";
        }
    }
   os << "]";
   return os;
}

void measure(Lambda f) {
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 1E5; ++i) {
        f("gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat gather field wheat gather faield wheat", ' ');
    }
    auto end_time = std::chrono::steady_clock::now() - start;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time);
    cout << elapsed.count()/1000. << " seconds\n";
}

Vector split_08(const std::string_view str,
             char d = ' ') {
    Vector result;
    result.reserve(str.size());
    size_t start = 0, end = 0;
    end = str.find(d);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(d, start);
    }
    result.push_back(str.substr(start, end - start));
    return result;
}

int main() {

    measure(split_01);//1.777
    measure(split_02);//2.119
//    measure(split_03);//5.143
//    measure(split_04);//3.032
    measure(split_05);//1.894
    measure(split_08);//1.920
    measure(split_06);//1.808
//    measure(split_07);//1.920

    const std::string input = ":gather:field:wheat:";
    cout << split_01(input, ':') << '\n';
    cout << split_05(input, ':') << '\n';
    cout << split_08(input, ':') << '\n';

    return 0;
}
