#pragma once

class Tiles{
    protected:
    char label;
    public:
    Tiles(char label) : label{label} {}
    virtual ~Tiles() {}

    char getLabel() { return label; }

    virtual int positionEffect(int currentPosition) = 0;
};

class SnakeTile:public Tiles {
    private:
        int penalty;
    public:
        SnakeTile(int penalty) : Tiles('S'), penalty{penalty} {}
        int positionEffect(int currentPosition) override {
            return currentPosition - penalty;
        }
};

class LadderTile:public Tiles {
    private:
        int reward;
    public:
        LadderTile(int reward) : Tiles('L'), reward{reward} {}
        int positionEffect(int currentPosition) {
            return currentPosition + reward;
        }
};

class NormalTile:public Tiles {
    public:
        NormalTile() : Tiles('N') {}
        int positionEffect(int currentPosition) {
            return currentPosition;
        }
};