#ifndef CORE_H
#define CORE_H

#include "GameObject.h"
#include "Time.h"

#include <vector>
using namespace std;

class Core {
public:
    ~Core();
    static Core* instance();
    void draw();
    void update();

    void add(GameObject* go);
    void destroy(GameObject* go);
    void setResolution(int width, int height);

    const vector<GameObject*>& getElements();
    float getWidth();
    float getHeight();
private:
    Core();
    void destroyObjects();
    static Core* instance_;
    Time timer_;
    vector<GameObject*> activeObjects_;
    vector<GameObject*> objectsToDestroy_;
    int width_;
    int height_;
};

#endif
