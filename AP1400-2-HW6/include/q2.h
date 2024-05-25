#ifndef Q2_H
#define Q2_H
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
namespace q2 {
    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline std::vector<Patient> read_file(std::string filename) {
        //std::ifstream file("lung_cancer.csv");
        std::ifstream file(filename);
        std::string str;
        std::vector<Patient> v;
        std::getline(file, str);
        std::getline(file, str);
        while (std::getline(file, str)) {
            std::stringstream ss(str);
            Patient p;
            std::string str1, str2, str3, str4, str5, str6;
            int count = 0;
            for (size_t i = 0; i < str.size(); i++) {
                if (str[i] == ' ') {
                    continue;
                }
                if (str[i] == ',') {
                    count++;
                    continue;
                }
                else if (count == 0) {
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
                else if (count == 5) {
                    str6 += str[i];
                }
            }
            p.name = str1 + " " + str2;
            std::stringstream ss3(str3);
            std::stringstream ss4(str4);
            std::stringstream ss5(str5);
            std::stringstream ss6(str6);
            ss3 >> p.age;
            ss4 >> p.smokes;
            ss5 >> p.area_q;
            ss6 >> p.alkhol;

            v.push_back(p);
        }
        return v;
    }

    inline void sort(std::vector<Patient>& v) {
        std::sort(v.begin(), v.end(), [](Patient a, Patient b) {
            int x1 = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
            int x2 = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;
            return x1 > x2;
        });
    }
}

#endif //Q2_H