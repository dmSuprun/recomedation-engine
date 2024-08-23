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
    // get films that user liked
    vector<graphNode*> thisUserLikedFilms;

    vector<graphNode*> usersForRecomendation;
    vector<graphNode*> recomendation;

    graphWithRec.getAdjacentNodes(userId, thisUserLikedFilms);
    for(auto oneFilm:thisUserLikedFilms){
        vector<graphNode*> temp;
        graphWithRec.getAdjacentNodes(oneFilm->vertexId, temp);
        usersForRecomendation.insert(usersForRecomendation.end(),temp.begin(), temp.end());
    }

    for(auto oneUser:usersForRecomendation){
        vector<graphNode*> temp;
        graphWithRec.getAdjacentNodes(oneUser->vertexId, temp);
        recomendation.insert(recomendation.begin(),temp.begin(), temp.end());
    }

    int totalSize=recomendation.size();
    int numDel=0;
    for(int i=0;i<totalSize;i++){
        if(graphWithRec.checkAdjacent(userId, recomendation[i-numDel]->vertexId)){
            recomendation.erase(recomendation.begin()+i-numDel);
            numDel++;
        }

    }


    vectroWithAdjacent.clear();
    vectroWithAdjacent.insert(vectroWithAdjacent.begin(), recomendation.begin(), recomendation.end());


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
