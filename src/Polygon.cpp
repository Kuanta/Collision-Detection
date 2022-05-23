#include "Polygon.h"

Polygon2D::Polygon2D()
{

}
Polygon2D::Polygon2D(vector<Vector2> vertices)
{
    this->vertices.clear();
    this->normals.clear();
    this->vertices = vertices;
    this->initPolygon();
}
Polygon2D::Polygon2D(const Vector2 vertices[])
{
    this->vertices.clear();
    this->normals.clear();
    this->vertices = vector<Vector2>(vertices, vertices + sizeof(vertices)/sizeof(vertices[0]));
    this->initPolygon();
}
void Polygon2D::setVertices(vector<Vector2> vertices)
{
    this->vertices.clear();
    this->normals.clear();
    this->vertices = vertices;
    this->initPolygon();
}
void Polygon2D::initPolygon()
{
    if(this->vertices.size() < 3)
    {
        throw "Polygon must have at least 3 vertices";
    }else{
        float angle = -90.0f/180.0f*PI;
        for(unsigned int i=0;i<this->vertices.size();i++)
        {   
            int index1 = i;
            int index2 = i+1;

            //Calculate the normal
            if(index2 >= this->vertices.size())
            {
                //For last normal
                index2 = 0;
            }

            Vector2 diff = this->vertices.at(index2) - this->vertices.at(index1);
            float x = cos(angle)*diff.x - sin(angle)*diff.y;
            float y = sin(angle)*diff.x + cos(angle)*diff.y;
            Vector2 result(x,y);
            result.normalize();
            this->normals.push_back(result);
        }
    }
}
int Polygon2D::getVertexCount()
{
    return this->vertices.size();
}

void Polygon2D::debugPoints()
{
    for(int i=0;i<this->vertices.size();i++)
    {
        printf("%s\n", this->vertices.at(i).toString().c_str());
    }
}