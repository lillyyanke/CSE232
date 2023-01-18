#include "GamePiece.hpp"
#include "GameState.hpp"
#include <string>
#include <iostream>
#include <algorithm>
using std::string;
/*
GamePiece::GamePiece(GamePiece &gp){
    player_ = gp.player_;
    type_ = gp.type_;
    //*game = gp.*game;
    game->addPlayer(player_, type_);
    ///*game = gp.GetGame();
    //gp.*game->addPlayer(player_, type_);
}
*/

GamePiece::GamePiece(const GamePiece& gp){
    this->player_ = gp.player_;
    this->type_ = gp.type_;
    
}

GamePiece::GamePiece(string player, string type, GameState *game){
    player_ = player;
    type_ = type;
    game->addPlayer(player, type);
}
/*
GamePiece& GamePiece::operator= (const GamePiece& gp){
    player_ = gp.player_;
    type_ = gp.type_;
    game = gp.game;
    return *this;
}
*/

//void GamePiece::addPlayer(string player, string type, GameState *game){
    //*game.addPlayer(player,type);
//}



int GamePiece::GetPower() {
    if (type_ == "Warrior"){
        power_ = 5;
        return power_;
    }
    else if (type_ == "Scout"){
        power_ = 1;
        return power_;
    }
    else{
        int power_ = game->countWizards(player_);
        return power_;
    }
}


int GamePiece::GetSpeed(){
    if (type_ == "Warrior"){
        speed_ = 2;
        return speed_;
    }
    else if (type_ == "Scout"){
        speed_ = 8;
        return speed_;
    }
    else{
        speed_ = 12 - (game->countWizardEnemies(player_));
        if (speed_ < 1){
            speed_ = 1;
            return speed_;
        }
        else{
            return speed_;
        }    
}
}