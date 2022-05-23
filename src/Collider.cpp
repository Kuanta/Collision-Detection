#include "Collider.h"

//Collider2D
Collider2D::Collider2D(vector<Vector2> vertices)
{
    Polygon2D poly(vertices);
    this->polygon = poly;
    this->updateBoundingBox();
    this->position = Vector2(0,0);
    this->rotation = 0;
    this->handler = nullptr;
}
Collider2D::Collider2D(Polygon2D poly)
{
    this->polygon = poly;
    this->updateBoundingBox();
    this->position = Vector2(0,0);
    this->rotation = 0;
    this->handler = nullptr;
}
void Collider2D::translate(Vector2 position)
{
    this->position = this->position + position;
    for(int i=0; i<this->polygon.getVertexCount(); i++)
    {
        this->polygon.vertices.at(i) = this->polygon.vertices.at(i) + position;
    }

    //Translate bounding box
    this->bb.leftBot.x += position.x;
    this->bb.rightTop.x += position.x;
    this->bb.leftBot.y += position.y;
    this->bb.rightTop.y += position.y;
}
void Collider2D::rotate(real angle)
{
    //Bounding box will be affected from the rotation
    real maxX, maxY, minY, minX;
    maxX = this->polygon.vertices.at(0).x;
    minX = maxX;
    maxY = this->polygon.vertices.at(0).y;
    minY = maxY;

    this->rotation = this->rotation + angle;
    for(int i=0; i<this->polygon.getVertexCount(); i++)
    {
        Vector2 vertex = this->polygon.vertices.at(i) - this->position;
        vertex.rotate(angle);
        vertex = vertex + this->position;
        this->polygon.vertices.at(i) = vertex;

        //X coord
        if(vertex.x > maxX)
        {
            maxX = vertex.x;
        }
        if(vertex.x < minX)
        {
            minX = vertex.x;
        }

        //Y coord
        if(vertex.y > maxY)
        {  
            maxY = vertex.y;
        }
        if(vertex.y < minY)
        {
            minY = vertex.y;
        }   
    }

    //Rotate bounding box
}
void Collider2D::updateBoundingBox()
{
    real maxX, maxY, minY, minX;
    maxX = this->polygon.vertices.at(0).x;
    minX = maxX;
    maxY = this->polygon.vertices.at(0).y;
    minY = maxY;

    for(int i=0; i<this->polygon.getVertexCount(); i++)
    {
        Vector2 vertex = this->polygon.vertices.at(i);
        //X coord
        if(vertex.x > maxX)
        {
            maxX = vertex.x;
        }
        if(vertex.x < minX)
        {
            minX = vertex.x;
        }

        //Y coord
        if(vertex.y > maxY)
        {  
            maxY = vertex.y;
        }
        if(vertex.y < minY)
        {
            minY = vertex.y;
        }   
    }
    this->bb.leftBot = Vector2(minX, minY);
    this->bb.rightTop = Vector2(maxX, maxY);
}

void Collider2D::centeralize()
{
    Vector2 center = this->bb.leftBot + this->bb.rightTop;
    center = center/2.0f;
    this->translate(center*(-1));
    this->position = Vector2(0,0);
}

void Collider2D::setHandler(void (*handler)(Collider2D*, Collider2D*))
{
    this->handler = handler;
}

bool checkCollision(Collider2D coll1, Collider2D coll2)
{
    //Seperating-axis algorithm
    
    Polygon2D poly1 = coll1.polygon; Polygon2D poly2 = coll2.polygon;
    //Select the vertex with fewer vertex count 
    Polygon2D* poly_p;
    if(poly1.getVertexCount() < poly2.getVertexCount())
    {
        poly_p = &poly1;
    }else{
        poly_p = &poly2;
    }
    bool collision = true;
    for(int i=0;i<(*poly_p).getVertexCount();i++)
    {
        Vector2 normal = (*poly_p).normals.at(i);
        Vector2 min1(INFINITY, INFINITY);
        Vector2 min2(INFINITY, INFINITY);
        Vector2 max1(-INFINITY, -INFINITY);
        Vector2 max2(-INFINITY, -INFINITY);
        //Project the points of coll1
        for(int j=0;j<poly1.getVertexCount();j++)
        {
            Vector2 projected = poly1.vertices.at(j).projectOn(normal);
            min1.x = min(min1.x, projected.x);
            min1.y = min(min1.y, projected.y);
            max1.x = max(max1.x, projected.x);
            max1.y = max(max1.y, projected.y);
        }

        //Project the points of coll2
        for(int j=0;j<poly2.getVertexCount();j++)
        {
            Vector2 projected = poly2.vertices.at(j).projectOn(normal);
            min2.x = min(min2.x, projected.x);
            min2.y = min(min2.y, projected.y);
            max2.x = max(max2.x, projected.x);
            max2.y = max(max2.y, projected.y);
        }

        //If there is a gap between the projected, than
        real distance1 = (max1-min1).magnitude();
        real distance2 = (max2-min2).magnitude();
        real distance = max((max2-min1).magnitude(), (max1-min2).magnitude());
        if(distance > distance1 + distance2)
        {
            return false;
        }
    }
    return collision;
}