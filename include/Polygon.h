/*
Polygon2D and Polygon3D
Define polygon vertices in counterclockwise-manner
*/
#pragma once
#include <vector>
#include <math.h>
#include "Vector.h"

# define PI 3.14159265358979323846



class Polygon2D
{
    public:
        //Variables
        vector<Vector2> vertices;
        vector<Vector2> normals;
        
        //Methods
        Polygon2D();
        Polygon2D(vector<Vector2> vertices);
        Polygon2D(const Vector2 vertices[]);
        void setVertices(vector<Vector2> vertices);
        int getVertexCount();
        void debugPoints(); //Prints the points to the console;

    private:
        void initPolygon(); //Calculates normals
};

