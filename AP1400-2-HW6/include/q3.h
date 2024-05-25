#ifndef Q3_H
#define Q3_H
#include<queue>
#include<string>
#include<fstream>
#include<sstream>
namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
        friend bool operator<(Flight f1, Flight f2) {
            int x1 = f1.duration + f1.connection_times + 3 * f1.price;
            int x2 = f2.duration + f2.connection_times + 3 * f2.price;
            return x1 > x2;
        }
    };
    inline std::priority_queue<Flight> gather_flights(std::string filename) {
        std::ifstream in(filename);
        std::string str;
        std::priority_queue<Flight> q;
        while (std::getline(in, str)) {
            int count = 0;
            Flight f;
            std::string str1, str2, str3, str4, str5;
            for (size_t i = 17; i < str.size(); i++) {
                if (str[i] == ' ') {
                    continue;
                }
                if (str[i] == '-') {
                    count++;
                    continue;
                }
                if (count == 0) {
                    str1 += str[i];
                }
                else if (count == 1) {
                    str2 += str[i];
                }
                else if (count == 2) {
                    str3 += str[i];
                }
                else if (count == 3) {
                    str4 += str[i];
                }
                else if (count == 4) {
                    str5 += str[i];
                }
            }
            f.flight_number = str1;

            // duration
            std::string hour, minute;
            int count1 = 0;
            for (size_t i = 9; i < str2.size() - 1; i++) {
                if (str2[i] == 'h') {
                    count1++;
                    continue;
                }
                if (str2[i] >= '0' && str2[i] <= '9') {
                    if (count1 == 0) {
                        hour += str2[i];
                    }
                    else if (count1 == 1) {
                        minute += str2[i];
                    }
                }
            }
            std::stringstream ss1(hour);
            std::stringstream ss2(minute);
            int h = 0, m = 0;
            ss1 >> h;
            ss2 >> m;
            f.duration = h * 60 + m;

            // connections
            std::string connections_str;
            for (size_t i = 12; i < str3.size(); i++) {
                if (str3[i] >= '0' && str3[i] <= '9') {
                    connections_str += str3[i];
                }
            }
            std::stringstream ss3(connections_str);
            ss3 >> f.connections;

            // connection_times
            int count2 = 0;
            std::string hour1, minute1;
            size_t ans = 0; 
            for (size_t i = 17; i < str4.size(); i++) {
                if (str4[i] == ',' || i == str4.size() - 1) {
                    std::stringstream ss4(hour1);
                    std::stringstream ss5(minute1);
                    int h1 = 0, m1 = 0;
                    ss4 >> h1;
                    ss5 >> m1;
                    ans += h1 * 60 + m1;
                    hour1 = "";
                    minute1 = "";
                    count2 = 0;
                    continue;
                }
                if (str4[i] == 'h') {
                    count2++;
                    continue;
                }
                if (str4[i] >= '0' && str4[i] <= '9') {
                    if (count2 == 0) {
                        hour1 += str4[i];
                    }
                    else if (count2 == 1) {
                        minute1 += str4[i];
                    }

                }
            }
            f.connection_times = ans;

            // price
            std::string str6;
            for (size_t i = 6; i < str5.size(); i++) {
                if (str5[i] >= '0' && str5[i] <= '9') {
                    str6 += str5[i];
                }
            }
            std::stringstream ss6(str6);
            ss6 >> f.price;

            q.push(f);
        }
        return q;
    }
}


#endif //Q3_H