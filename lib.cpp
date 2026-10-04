#include "lib.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool DidSplit() {

    bool AllFine = true;

    std::vector<std::string> ips = {"1.2.3.4", "1.1.", ".1.2.3", "1..1"};
    std::vector<std::string> vec;

    for (int j = 0; j < 4; j++) {
        vec = split(ips[j], '.');
        int size = vec.size();
        for(int i = 0; i < size; i++) {
            if((vec[i]).find(".") != std::string::npos) {
                AllFine = false;
                break;
            }
        }
    }
    return AllFine;
}

bool DidSort() {
    
    bool AllFine = true;
    std::vector<std::string> e = {"10","10","10","10"};
    std::vector<std::string> d = {"9","9","9","9"};
    std::vector<std::string> a = {"8","8","8","8"};
    std::vector<std::string> b = {"7","7","7","7"};
    std::vector<std::string> c = {"6","6","6","6"};
    std::vector <std::vector <std::string> > vec = {a,b,c,d,e};

    auto comp4 = [](std::vector<std::string> a, std::vector<std::string> b)
        {
            std::vector<std::string> a2;
            std::vector<std::string> b2;
            for (int i = 0; i < 4;) {
                a2 = split(a.at(i), '.');
                b2 = split(b.at(i), '.');
                if (std::stoi(a2.at(0)) > std::stoi(b2.at(0))) {
                    return true;
                }
                else if (std::stoi(a2.at(0)) == std::stoi(b2.at(0))) {
                    i++;
                }
                else {
                    return false;
                }
            }
            return false;
        };
    
    std::sort(begin(vec), end(vec), comp4);
    
    if ((vec[0] != e) || (vec[1] != d) || (vec[2] != a) || (vec[3] != b)) {
        AllFine = false;
    }

    return AllFine;
}

bool DidSort2() {

    bool AllFine = true;
    std::vector<std::string> e = {"2","3","4","5"};
    std::vector<std::string> d = {"2","3","4","4"};
    std::vector<std::string> a = {"1","2","3","4"};
    std::vector<std::string> b = {"1","2","3","3"};
    std::vector<std::string> c = {"1","2","2","4"};
    std::vector <std::vector <std::string> > vec = {a,b,c,d,e};

    auto comp4 = [](std::vector<std::string> a, std::vector<std::string> b)
        {
            std::vector<std::string> a2;
            std::vector<std::string> b2;
            for (int i = 0; i < 4;) {
                a2 = split(a.at(i), '.');
                b2 = split(b.at(i), '.');
                if (std::stoi(a2.at(0)) > std::stoi(b2.at(0))) {
                    return true;
                }
                else if (std::stoi(a2.at(0)) == std::stoi(b2.at(0))) {
                    i++;
                }
                else {
                    return false;
                }
            }
            return false;
        };
    
    std::sort(begin(vec), end(vec), comp4);
    
    if ((vec[0] != e) || (vec[1] != d) || (vec[2] != a) || (vec[3] != b)) {
        AllFine = false;
    }

    return AllFine;
}