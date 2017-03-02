#include "MassSystem.h"

const int kSlices = 32;
const int kStacks = 32;

MassSystem::MassSystem() {
    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){
            velocity_[k][i] = Vector3::zero_;
            positions_[k][i] = Vector3(k - 10.0f, i - 10.0f, 0.0f);
        }
    }
   // for (int k = 8; k <= 10; k++)
   //     for (int i = 8; i <= 10; i++)
     //       deletedIndexes_.push_back(DeletedInexes(k, i));

    quadric_ = gluNewQuadric();
}


MassSystem::~MassSystem() {
    delete quadric_;
}

bool MassSystem::findIndex(int k, int i) {
    for (int j = 0; j < deletedIndexes_.size(); j++) {
        if (k == deletedIndexes_[j].K && i == deletedIndexes_[j].I) return true;
    }
    return false;
}

void MassSystem::draw() {
    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){
            if (findIndex(k, i)) continue;
            glPushMatrix();
            glTranslatef(positions_[k][i].x, positions_[k][i].y, positions_[k][i].z);
            gluSphere(quadric_, 0.1f, kSlices, kStacks);
            glPopMatrix();
        }
    }
}

Vector3 CallcF(Vector3 xim1, Vector3 xi, Vector3 xip1, float ci, float cim1, float li, float lm1) {
    float g = 9.8f;
    float m = 0.01f;
    float prevLen = (xim1 - xi).length();
    Vector3 prevNorm = (xim1 - xi).normalized();
    float nextLen = (xip1 - xi).length();
    Vector3 nextNorm = (xip1 - xi).normalized();

    Vector3 nVel = prevNorm *cim1 * (prevLen - lm1);
    nVel = nVel + nextNorm * ci * (nextLen - li);
    nVel = nVel + Vector3(0.0f, 0.0f, -g*m);
    return nVel;
}

Vector3 CalcF(Vector3 xi, Vector3 xj, float lij, float cij) {
    float prevLen = (xj - xi).length();
    Vector3 prevNorm = (xj - xi).normalized();
    return prevNorm * cij * (prevLen - lij);// +Vector3(0.0f, 0.0f, -9.8f*0.01f);
}

void MassSystem::update() {

    if (TouchInput::instance()->getButton() != 0) return;

    if (TouchInput::instance()->getState() == TOUCH_DOWN) {
        positions_[10][10] = Vector3(0.0f, 0.0f, 7.0f);
    }

    Vector3 newPos[N][N];
    Vector3 newVel[N][N];

    float l = 1;
    float c = 10.0f;
    float dt = 0.016f;// Time::getDeltaTime();
    int k = 0;

    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){
            if ( k == N - 1 || i == N - 1) {//i == 0 || k == 0 ||
                newPos[k][i] = positions_[k][i];
                continue;
            }
       

            //newVel[i] = velocity_[i] + CallcF(positions_[i - 1], positions_[i], positions_[i + 1], C[i], C[i - 1], L[i], L[i - 1]) * dt;
            newVel[k][i] = velocity_[k][i]
                + (CalcF(positions_[k][i], positions_[k + 1][i], l, c)
                + CalcF(positions_[k][i], positions_[k][i + 1], l, c)
                + CalcF(positions_[k][i], positions_[k + 1][i + 1], l, c)
                + CalcF(positions_[k + 1][i], positions_[k][i + 1], l, c)

                + CalcF(positions_[k][i], positions_[k + 2][i], l, c)
                + CalcF(positions_[k][i], positions_[k][i + 2], l, c)

                + (k - 1 >= 0 ? CalcF(positions_[k][i], positions_[k - 1][i], l, c) : Vector3::zero_)
                + (i - 1 >= 0 ? CalcF(positions_[k][i], positions_[k][i - 1], l, c) : Vector3::zero_)
                + (k - 1 >= 0 && i - 1 >= 0 ? CalcF(positions_[k][i], positions_[k - 1][i - 1], l, c) : Vector3::zero_)
                + (k - 1 >= 0 ? CalcF(positions_[k - 1][i], positions_[k][i + 1], l, c) : Vector3::zero_)

                + (k + 2 <= N - 1 ? CalcF(positions_[k][i], positions_[k + 2][i], l, c) : Vector3::zero_)
                + (i + 2 <= N - 1 ? CalcF(positions_[k][i], positions_[k][i + 2], l, c) : Vector3::zero_)
                /*((!findIndex(k - 1, i) ? CalcF(positions_[k][i], positions_[k - 1][i-1], l, c) : Vector3::zero_)
                + (!findIndex(k + 1, i) ? CalcF(positions_[k][i], positions_[k + 1][i+1], l, c) : Vector3::zero_)
                + (!findIndex(k, i - 1) ? CalcF(positions_[k][i], positions_[k+1][i - 1], l, c) : Vector3::zero_)
                + (!findIndex(k, i - 1) ? CalcF(positions_[k][i], positions_[k-1][i + 1], l, c) : Vector3::zero_)

                + (!findIndex(k - 1, i) ? CalcF(positions_[k][i], positions_[k - 1][i], l, c) : Vector3::zero_)
                + (!findIndex(k + 1, i) ? CalcF(positions_[k][i], positions_[k + 1][i], l, c) : Vector3::zero_)
                + (!findIndex(k, i - 1) ? CalcF(positions_[k][i], positions_[k][i - 1], l, c) : Vector3::zero_)
                + (!findIndex(k, i - 1) ? CalcF(positions_[k][i], positions_[k][i + 1], l, c) : Vector3::zero_)*/
                )*dt;
               /*+ Vector3(0.0f, 0.0f, -9.8f*0.01f)) * dt -velocity_[k][i] * 0.1f;*/
            newPos[k][i] = positions_[k][i] + newVel[k][i] * dt;
        }
   }

   memcpy(&velocity_, &newVel, sizeof(Vector3) * N * N);
   memcpy(&positions_, &newPos, sizeof(Vector3) * N * N);

  
  // positions_[5][5].z = 5.0f;
 //  positions_[12][12].z = -5.0f;
}

