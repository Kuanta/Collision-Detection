#include "BoundingVolume.h"

BoundingBox2D::BoundingBox2D()
{
    this->leftBot = Vector2(0.0f,0.0f);
    this->leftBot = Vector2(1.0f,1.0f);
}
BoundingBox2D::BoundingBox2D(Vector2 leftBot, Vector2 rightTop)
{
    this->leftBot = leftBot;
    this->rightTop = rightTop;
}
BoundingBox2D::BoundingBox2D(Vector2 leftBot, real width, real height)
{
    this->leftBot = leftBot;
    this->rightTop = Vector2(width, height) + leftBot;
}
BoundingBox2D::BoundingBox2D(BoundingBox2D box1, BoundingBox2D box2)
{
    real xVals[] = {box1.leftBot.x, box1.rightTop.x, box2.leftBot.x, box2.rightTop.x};
    real yVals[] = {box1.leftBot.y, box1.rightTop.y, box2.leftBot.y, box2.rightTop.y};

    //Sort xVals and yVals
    real* minX = min_element(xVals, xVals+4);
    real* minY = min_element(yVals, yVals+4);
    real* maxX = max_element(xVals, xVals+4);
    real* maxY = max_element(yVals, yVals+4);

    this->leftBot = Vector2(*minX, *minY);
    this->rightTop = Vector2(*maxX, *maxY);
}
float BoundingBox2D::getVolume()
{
    return this->getHeight()*this->getWidth();
}
bool BoundingBox2D::overlaps(BoundingVolume* vol)
{
    BoundingBox2D* box2 = (BoundingBox2D*) vol; //Cast to bounding box
    real xVals[] = {this->leftBot.x, this->rightTop.x, box2->leftBot.x, box2->rightTop.x};
    real yVals[] = {this->leftBot.y, this->rightTop.y, box2->leftBot.y, box2->rightTop.y};

    //Sort xVals and yVals
    real* minX = min_element(xVals, xVals+4);
    real* minY = min_element(yVals, yVals+4);
    real* maxX = max_element(xVals, xVals+4);
    real* maxY = max_element(yVals, yVals+4);

    real xDist = *maxX - *minX;
    real yDist = *maxY - *minY;

    if((xDist <= this->getWidth() + box2->getWidth()) && (yDist <= this->getHeight() + box2->getHeight()))
    {
        //If the boxes overlap, xDist and yDist must be smaller than width1+widtb2 and height1+height2 respectively
        return true;
    }
    return false;
}
BoundingVolume* BoundingBox2D::getCombinedVolume(BoundingVolume* other)
{
    BoundingBox2D* box2 = (BoundingBox2D*) other;
    real xVals[] = {this->leftBot.x, this->rightTop.x, box2->leftBot.x, box2->rightTop.x};
    real yVals[] = {this->leftBot.y, this->rightTop.y, box2->leftBot.y, box2->rightTop.y};

    //Sort xVals and yVals
    real* minX = min_element(xVals, xVals+4);
    real* minY = min_element(yVals, yVals+4);
    real* maxX = max_element(xVals, xVals+4);
    real* maxY = max_element(yVals, yVals+4);

    BoundingBox2D combined = BoundingBox2D(Vector2(*minX, *minY), Vector2(*maxX, *maxY));
    return &combined;
}
//Bounding Box
real BoundingBox2D::getHeight()
{
    return abs(this->leftBot.y - this->rightTop.y);
}

real BoundingBox2D::getWidth()
{
    return abs(this->leftBot.x - this->rightTop.x);
}

