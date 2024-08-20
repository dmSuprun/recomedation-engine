#include <iostream>
#include <fstream>
#include "user.h"
#include "film.h"
#include "graph.h"
#define numUsers 5
#define numFilms 15
using namespace std;

void getDataForEngine(user* users, film* films){
    ifstream usersFile("C:\\Users\\Dima\\CLionProjects\\recEng\\users.txt");
    ifstream filmsFile("C:\\Users\\Dima\\CLionProjects\\recEng\\films.txt");
    for(int i=0; i<numUsers; i++){
        usersFile>>users[i];
    }
    for(int i=0; i<numFilms; i++){
        filmsFile>>films[i];
    }
    usersFile.close();
    filmsFile.close();


}


void getRecomendationList(graph& graphWithRec,int userId, vector<graphNode*>& vectroWithAdjacent){
    vector<graphNode*> oneFilmRecomendation;
    vector<graphNode*> usersRecomendation;
    vector<graphNode*> recomendation;

    vectroWithAdjacent.clear();
    for(auto i:graphWithRec.adjacentList.at(userId)->adjacentNodes){
        vectroWithAdjacent.push_back(i); // всі фільми які користувач лайкнув
    }
    for(auto i : vectroWithAdjacent){
        graphWithRec.getAdjacentNodes(i->vertexId, oneFilmRecomendation);
        for(auto oneUser: oneFilmRecomendation){// список коритсувачів які лайкнули кіно
            graphWithRec.getAdjacentNodes(oneUser->vertexId, usersRecomendation);
            for(auto resFilm:usersRecomendation){
                if(!graphWithRec.checkAdjacent(userId, resFilm->vertexId) &&
                        find(recomendation.begin(), recomendation.end(),resFilm) == recomendation.end()){
                    recomendation.push_back(resFilm);
                }
            }


        }
    }
    vectroWithAdjacent.clear();
    for(auto i:recomendation){
        vectroWithAdjacent.push_back(i);
    }

}




void getRecomendation(int userId, int filmId,user* users, film* films, graph& graphWithRec){
    vector<graphNode*> recomendation;
    vector<graphNode*> temp;
    //get users with id



    user * thisUser;
    film* thisFilm;


    for(int i=0; i<numUsers; i++){
        if (users[i].Id == userId){
            thisUser =&users[i];
            break;

        };

    }
    for(int i=0; i<numFilms; i++){
        if (films[i].Id == filmId){
            thisFilm =&films[i];
            break;

        }
    }



    if (graphWithRec.checkExistenceInGraph(userId) && graphWithRec.checkExistenceInGraph(filmId)){
        graphWithRec.addEdge(userId, filmId);
        getRecomendationList(graphWithRec, userId, recomendation);


    } else if(!graphWithRec.checkExistenceInGraph(userId) && graphWithRec.checkExistenceInGraph(filmId)){
        graphWithRec.addNode(thisUser);
        graphWithRec.addEdge(userId, filmId);
        getRecomendationList(graphWithRec, userId, recomendation);



    }else if(graphWithRec.checkExistenceInGraph(userId) && !graphWithRec.checkExistenceInGraph(filmId)){
        graphWithRec.addNode(thisFilm);
        graphWithRec.addEdge(userId, filmId);
        getRecomendationList(graphWithRec, userId, recomendation);



    } else{
        graphWithRec.addNode(thisUser);
        graphWithRec.addNode(thisFilm);
        graphWithRec.addEdge(userId, filmId);
        getRecomendationList(graphWithRec, userId, temp);



    }
    cout<<"РЕКОМЕНДАЦІЇ:";
    for(auto i:recomendation){
        cout<<get<film*>(i->data)->filmName<<"; ";
    }
    cout<<endl;
}







int main() {


    user users[numUsers];
    film films[numFilms];
    graph graphWithRecomendation;
    getDataForEngine(users, films);

    int ctr, firstId, secondId;
    while (true){
        cout<<"Введіть номер команди (0 - стоп, 1 - поставити лайк):";
        cin>>ctr;
        if(!ctr){
            break;
        }
        cout<<"Введіть id користувача та id фільму:";
        cin>>firstId>>secondId;
        getRecomendation(firstId, secondId, users, films, graphWithRecomendation);







    }






    return 0;
}
