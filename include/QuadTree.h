#pragma once
#include <vector>
#include "Vector.h"
#include "Collider.h"
#include "BoundingVolume.h"

using namespace std;

enum QuadSectorOrientation{
    BOT_LEFT, BOT_RIGHT, TOP_LEFT, TOP_RIGHT
};

struct CollisionPair{
    Collider2D* collider1;
    Collider2D* collider2;
};

class QuadNode{
    public:
    QuadNode();
    QuadNode(Vector2 center, real halfSize, unsigned capacity);
    ~QuadNode(); //Also delete the children
    //Variables
    Vector2 center;
    real halfSize;
    unsigned capacity;
    QuadNode* parent;
    QuadNode* children[4];
    vector<Collider2D*> colliders;


    //Methods
    bool isLeaf();
    void insert(Collider2D* collider);
    void divide();
    bool requiresDivision();
    unsigned getQuadrant(BoundingBox2D box); //Returns the quadrant of the given bounding volume
    void getCollisionPairs(vector<CollisionPair>* pairs);

    private:
    void addColliderToChildren(Collider2D* collider); //This adds the collider to the proper quadrants
    void initChildren(); //Initialize children to be nullptrs
    BoundingBox2D getSectorBox(); //Returns the bb for this sector. Can be used to check overlappings
};