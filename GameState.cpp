#include "GameState.hpp"
#include <string>
#include<map>
#include <iterator>
using std::string;
using std::multimap;
using std::pair;


//void GameState::team(string player, string type){
    //team1_.insert(pair<string,string>(player,type));
   //addPlayer(player,type);
//}

//void GameState::team2(string player,string type){
    //team2_.insert(pair<string,string>(player,type));
    //addPlayer("team2_",player,type);
//}




void GameState::addPlayer(string player, string type){
    teams_.insert(pair<string,string>(player,type));
    //if (team == "team1_"){
        //team1_.insert(pair<string,string>(player,type));
    //}
    //else{
        //team2_.insert(pair<string,string>(player,type));
    //}
    //team.insert(pair<string,string>(player,type);
}

int GameState::countWizardEnemies(string player){
    int count = 0;
    multimap<string, string>::iterator itr;
    for (itr = teams_.begin(); itr != teams_.end(); itr++){
        if (itr->first != player){
            if (itr->second == "Wizard"){
                count++;
            }
            //count++;
        }
    }
    return count;
}

int GameState::countWizards(string player){
    int count = 0;
    multimap<string, string>::iterator itr;
    for (itr = teams_.begin(); itr != teams_.end(); itr++){
        if (itr->first == player){
            if (itr->second == "Wizard"){
                count++;
            }
            //count++;
        }
    }
    return count;
}


int GameState::NumPieces(){
    int count = 0;
    multimap<string, string>::iterator itr;
    for (itr = teams_.begin(); itr != teams_.end(); itr++){
        count++; 
    }
    return count;
}

int GameState::NumPieces(const string & player){
    int count = 0;
    multimap<string, string>::iterator itr;
    for (itr = teams_.begin(); itr != teams_.end(); itr++){
        if (itr->first == player){
            count++;
        }
    }
    return count;
}

int GameState::NumePieces(const string &player, const string &type){
    int count = 0;
    multimap<string, string>::iterator itr;
    for (itr = teams_.begin(); itr != teams_.end(); itr++){
        if ((itr->first == player)&&(itr->second ==type)){
            count++;
        }
    }
    return count;
}