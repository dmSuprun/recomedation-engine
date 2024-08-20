#include "user.h"

std::ifstream& operator>>(std::ifstream& stream, user& obj){
    stream>>obj.Id;
    stream.ignore();
    getline(stream, obj.Name);
    return stream;
}

std::ofstream& operator<<(std::ofstream& stream, user& obj){
    stream<<obj.Id<<" "<<obj.Name;
    return stream;
}