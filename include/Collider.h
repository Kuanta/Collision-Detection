#pragma once
#include "Polygon.h"
#include "BoundingVolume.h"

class Collider2D
{   
    public:
    //Variables
    Vector2 position;
    real rotation;
    Polygon2D polygon;
    BoundingBox2D bb;

    //Methods
    Collider2D(vector<Vector2> vertices);
    Collider2D(Polygon2D poly);
    void rotate(real angle);
    void translate(Vector2 translate);
    void updateBoundingBox();
    void centeralize(); //Sets the polygon to the centers
    void setHandler(void (*handler)(Collider2D*, Collider2D*));
    void (*handler)(Collider2D*, Collider2D*);
};

bool checkCollision(Collider2D coll1, Collider2D coll2);




