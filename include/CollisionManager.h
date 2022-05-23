#pragma once
#include <vector.h>
#include "Collider.h"
#include "BVTree.h"
#include "QuadTree.h"

using namespace std;

class CollisionManager
{
    public:
    CollisionManager();

    //Variables
    vector<Collider2D*> objects;

    //Method
    void update();
    void addObject(Collider2D* object);
    
};