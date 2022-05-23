#include "QuadTree.h"

QuadNode::QuadNode()
{
    this->parent = nullptr;
    this->initChildren();
}
QuadNode::QuadNode(Vector2 center, real halfSize, unsigned capacity)
{
    this->center = center;
    this->halfSize = halfSize;
    this->capacity = capacity;
    this->initChildren();
}
QuadNode::~QuadNode()
{
    if(!this->isLeaf())
    {
        for(int i=0;i<4;i++){
            printf("%d\n",i);
            delete this->children[i];
        }
    }
}
bool QuadNode::isLeaf()
{
    //If this doesn't have any children, then its a leaf
    return (children[0] == nullptr);
}
void QuadNode::insert(Collider2D* collider)
{
    /*
        An assumption is made that the collider is within the boundaries of this node, because we start insderting from node.
        If root node doesn't contain the object completely problems may arise
    */
   //First, check if the collider overlaps with this
   BoundingBox2D thisBox = this->getSectorBox();
   if(!thisBox.overlaps(&collider->bb))
   {
       //They aren't colliding, early out
       return;
   }
   if(this->isLeaf())
   {
       this->colliders.push_back(collider);
        unsigned quadrant = this->getQuadrant(collider->bb);
       //Check division
       if(this->colliders.size() > this->capacity && !(quadrant & 15)){  //If the object collides with all quadrant, don't divide
           printf("Divide %d\n", this->colliders.size());
           this->divide();
       }
   }else{
        this->addColliderToChildren(collider);
   }
}
void QuadNode::divide()
{
    children[QuadSectorOrientation::TOP_LEFT] = 
        new QuadNode(Vector2(this->center.x-halfSize, this->center.y+halfSize), halfSize/4.0f, this->capacity);
    children[QuadSectorOrientation::TOP_RIGHT] = 
        new QuadNode(Vector2(this->center.x+halfSize, this->center.y+halfSize), halfSize/4.0f, this->capacity);
    children[QuadSectorOrientation::BOT_LEFT] = 
        new QuadNode(Vector2(this->center.x-halfSize, this->center.y-halfSize), halfSize/4.0f, this->capacity);
    children[QuadSectorOrientation::BOT_RIGHT] = 
        new QuadNode(Vector2(this->center.x+halfSize, this->center.y-halfSize), halfSize/4.0f, this->capacity);
    
    for(unsigned i=0;i<this->colliders.size();i++)
    {
        this->addColliderToChildren(colliders.at(i));
    }
    this->colliders.clear();
}

unsigned QuadNode::getQuadrant(BoundingBox2D box)
{
    unsigned int flag = 0U;
    real boxWidth = box.getWidth();
    real boxHeight = box.getHeight();
    if(box.leftBot.x < this->center.x && box.leftBot.y+boxHeight > this->center.y)
    {
       flag |= 1U<<QuadSectorOrientation::TOP_LEFT;

    }
    if(box.leftBot.x + boxWidth > this->center.x && box.leftBot.y+boxHeight > this->center.y)
    {
        flag |= 1U<<QuadSectorOrientation::TOP_RIGHT;

    }
    if(box.leftBot.x < this->center.x && box.leftBot.y < this->center.y)
    {
        flag |= 1U<<QuadSectorOrientation::BOT_LEFT;

    }
    if(box.leftBot.x + boxWidth > this->center.x && box.leftBot.y < this->center.y)
    {
        flag |= 1U<<QuadSectorOrientation::BOT_RIGHT;
    }
    return flag;
}
void QuadNode::getCollisionPairs(vector<CollisionPair>* pairs)
{
    if(isLeaf() && this->colliders.size()>1){
        for(unsigned i=0;i<this->colliders.size();i++)
        {
            for(unsigned j=i+1;j<this->colliders.size();j++)
            {
                CollisionPair pair;
                pair.collider1 = this->colliders.at(i);
                pair.collider2 = this->colliders.at(j);
                pairs->push_back(pair);
            }   
        }
    }else if(!isLeaf())
    {
        for(int i=0;i<4;i++)
        {
            this->children[i]->getCollisionPairs(pairs);
        }
    }
}
void QuadNode::addColliderToChildren(Collider2D* collider)
{
    real boxWidth = collider->bb.getWidth();
    real boxHeight = collider->bb.getHeight();
    if(collider->bb.leftBot.x < this->center.x && collider->bb.leftBot.y+boxHeight > this->center.y)
    {
        this->children[QuadSectorOrientation::TOP_LEFT]->insert(collider);

    }
    if(collider->bb.leftBot.x + boxWidth > this->center.x && collider->bb.leftBot.y+boxHeight > this->center.y)
    {
        this->children[QuadSectorOrientation::TOP_RIGHT]->insert(collider);

    }
    if(collider->bb.leftBot.x < this->center.x && collider->bb.leftBot.y < this->center.y)
    {
        this->children[QuadSectorOrientation::BOT_LEFT]->insert(collider);

    }
    if(collider->bb.leftBot.x + boxWidth > this->center.x && collider->bb.leftBot.y < this->center.y)
    {
        this->children[QuadSectorOrientation::BOT_RIGHT]->insert(collider);
    }
}
void QuadNode::initChildren()
{
    this->children[QuadSectorOrientation::BOT_LEFT] = nullptr;
    this->children[QuadSectorOrientation::BOT_RIGHT] = nullptr;
    this->children[QuadSectorOrientation::TOP_LEFT] = nullptr;
    this->children[QuadSectorOrientation::TOP_RIGHT] = nullptr;
}
BoundingBox2D QuadNode::getSectorBox()
{
    BoundingBox2D box(Vector2(center.x-halfSize, center.y-halfSize),
    Vector2(center.x+halfSize, center.y+halfSize));
    return box;
}