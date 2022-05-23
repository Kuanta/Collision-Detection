#pragma once
#include <algorithm>
#include "Vector.h"

using namespace std;

class BoundingVolume{
    public:
    virtual float getVolume() = 0;
    virtual bool overlaps(BoundingVolume* other) = 0;
    virtual BoundingVolume* getCombinedVolume(BoundingVolume* other) = 0;
};

class BoundingBox2D:public BoundingVolume{
    public:
    BoundingBox2D();
    BoundingBox2D(Vector2 leftBot, Vector2 rightTop);
    BoundingBox2D(Vector2 leftBot, real width, real height);
    BoundingBox2D(BoundingBox2D box1, BoundingBox2D box2); //Initialize from the given 2 bounding box
    //Variables
    Vector2 leftBot;
    Vector2 rightTop;

    //Methods
    float getVolume() override;
    virtual bool overlaps(BoundingVolume* vol) override;
    virtual BoundingVolume* getCombinedVolume(BoundingVolume* other) override;

    real getWidth();
    real getHeight();
};