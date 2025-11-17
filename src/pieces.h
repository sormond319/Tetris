#ifndef PIECES
#define PIECES

class Pieces{
    public:
    int getBlockType(int piece, int rotation, int x, int y);
    int getXInitPos(int piece, int rotation);
    int getYInitPos(int piece, int rotation);
};

#endif