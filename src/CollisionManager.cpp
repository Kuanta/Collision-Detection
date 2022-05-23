#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
    
}

void CollisionManager::update()
{
    //Broadphase
    //Create Quad
    QuadNode* root = new QuadNode(Vector2(25,25), 25, 2);  //(center), halfSize, capacity
    for(unsigned i=0;i<this->objects.size();i++)
    {
        root->insert(objects.at(i));
    }
    vector<CollisionPair> pairs;
    root->getCollisionPairs(&pairs);

    //Narrow-phase
    //Test collision pairs
    for(unsigned i=0;i<pairs.size();i++)
    {
        if(checkCollision(*(pairs.at(i).collider1), *(pairs.at(i).collider2)))
        {
            //Fire handlers for each colliders
            if(pairs.at(i).collider1->handler != nullptr)
            {
                pairs.at(i).collider1->handler(pairs.at(i).collider1, pairs.at(i).collider2);
            }

            if(pairs.at(i).collider2->handler != nullptr)
            {
                pairs.at(i).collider2->handler(pairs.at(i).collider1, pairs.at(i).collider2);
            }
        }
        
    }
    
    delete root;
}
void CollisionManager::addObject(Collider2D* collider)
{
    this->objects.push_back(collider);
}