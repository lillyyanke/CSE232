#pragma once
#include <iostream>
#include <string>
using std::string;

class GameState;

class GamePiece {
    private:
        string player_;
        string type_;
        int power_ = 0;
        int speed_ = 0;
        GameState *game;

    public:
        GamePiece(string, string, GameState*);
        //GamePiece(GamePiece &);

        string GetPlayer() const { return player_; }
        string GetType() const { return type_; }
        //GameState GetGame() const { return *game; }

        //void addPlayer(string, string, GameState*);

        int GetPower();

        int GetSpeed();

};