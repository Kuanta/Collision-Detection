#include <iostream>
#include "BoundingVolume.h"
#include "Collider.h"
#include "Vector.h"
#include "Polygon.h"
#include "QuadTree.h"
#include "CollisionManager.h"

using namespace std;

void collisionHandler(Collider2D* collider, Collider2D* other);
Collider2D createSquare(Vector2 position, real size);
Collider2D createRectangle(Vector2 position, real width, real height);
int main()
{
    //Create the collision manager. Its construction doesn't require any arguments
    CollisionManager colMan;

    //Create some colliders
    Collider2D box1 = createSquare(Vector2(5,5), 5);
    Collider2D box2 = createSquare(Vector2(25,5), 5);
    Collider2D box3 = createSquare(Vector2(15,15), 10);

    //Add thecolliders to the manager
    colMan.addObject(&box1);
    colMan.addObject(&box2);
    colMan.addObject(&box3);

    //Set handler for desired colliders. Handler functions must return void and take two Collider2D* arguments. First argument is the collider itself and second is the collided one
    box1.setHandler(collisionHandler);

    //This should be done in the main loop  
    colMan.update();

    return 0;
}

void collisionHandler(Collider2D* collider, Collider2D* other)
{
    printf("%p collided with %p\n", collider, other);
}

Collider2D createSquare(Vector2 position, real size)
{
    static const Vector2 _vertices[] = {
        Vector2(0.0f, 0.0f), Vector2(size, 0.0f), Vector2(size, size), Vector2(0.0f, size) 
    };
    vector<Vector2> vertices(_vertices, _vertices + sizeof(_vertices)/sizeof(_vertices[0]));
    Polygon2D poly(vertices);
    return Collider2D(poly);
}

Collider2D createRectangle(Vector2 position, real width, real height)
{
     static const Vector2 _vertices[] = {
        Vector2(0.0f, 0.0f), Vector2(width, 0.0f), Vector2(width, height), Vector2(0.0f, height) 
    };
    vector<Vector2> vertices(_vertices, _vertices + sizeof(_vertices)/sizeof(_vertices[0]));
    Polygon2D poly(vertices);
    Collider2D collider(poly);
    collider.translate(position);
    collider.centeralize();
    return Collider2D(poly);
}
