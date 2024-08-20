#ifndef RECENG_USER_H
#define RECENG_USER_H
#include <string>
#include <fstream>


struct user {
    int Id;
    std::string Name;
    friend std::ifstream& operator>>(std::ifstream& stream, user& obj);
    friend std::ofstream& operator<<(std::ofstream& stream, user& obj);

};


#endif //RECENG_USER_H
