//
// Created by Dima on 16/08/2024.
//

#ifndef RECENG_FILM_H
#define RECENG_FILM_H
#include <string>
#include <fstream>


struct film {
    int Id;
    std::string filmName;
    std::string genre;

    friend std::ifstream& operator>>(std::ifstream& stream, film& obj);
    friend std::ofstream& operator<<(std::ofstream& stream, film& obj);

};



#endif //RECENG_FILM_H
