#pragma once
#include <vector>
#include "Engine/Engine.h"
using namespace std;
#define N  20

struct DeletedInexes {
    int I;
    int K;
    DeletedInexes() { K = 0; I = 0; }
    DeletedInexes(int k, int i) { K = k; I = i; }
};

class MassSystem: public GameObject
{
   
public:
    MassSystem();
    ~MassSystem();
    virtual void update();
    virtual void draw();
private:
    bool findIndex(int k, int i);

    //std::vector<Vector3> positions_;
    Vector3 positions_[N][N];
    Vector3 velocity_[N][N];
    std::vector<DeletedInexes> deletedIndexes_;
    GLUquadric* quadric_;
};

