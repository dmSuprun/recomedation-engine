//
// Created by Dima on 16/08/2024.
//

#include "film.h"
std::ifstream& operator>>(std::ifstream& stream, film& obj){
    stream>>obj.Id;
    stream.ignore();
    getline(stream, obj.filmName);
    getline(stream, obj.genre);
    return stream;
}


std::ofstream& operator<<(std::ofstream& stream, film& obj){
    stream<<obj.Id<<" "<< obj.filmName<<" ("<<obj.genre<<")";
    return stream;
}