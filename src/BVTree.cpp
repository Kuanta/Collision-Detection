#include "BVTree.h"

//Defines a binary tree that contains the bounding volumes available in the sceene. Use insertion method to construct the tree
BVNode::BVNode()
{
    this->parent = nullptr;
    this->body = nullptr;
    this->children[0] = nullptr;
    this->children[1] = nullptr;
}
BVNode::BVNode(BVNode* parent, BoundingBox2D volume, Collider2D* body)
{
    this->parent = parent;
    this->volume = volume;
    this->body = body;
}
BVNode::~BVNode()
{
    if(parent != nullptr)
    {
        BVNode* sibling;
        if(this->parent->children[0] == this)
        {
            sibling = parent->children[1];
        }else{
            sibling = parent->children[0];
        }

        parent->volume = sibling->volume;
        parent->body = sibling->body;
        parent->children[0] = sibling->children[0];
        parent->children[1] = sibling->children[1];

        sibling->parent = nullptr;
        sibling->body = nullptr;
        sibling->children[0] = nullptr;
        sibling->children[1] = nullptr;
        delete sibling;
        
        //Update Parent?
    }
    if(children[0] != nullptr)
    {
        children[0]->parent = nullptr;
        delete children[0];
    }
    if(children[1] != nullptr)
    {
        children[1]->parent = nullptr;
        delete children[1];
    }
}

//Methods
bool BVNode::isLeaf()
{
    return (this->body != nullptr);
}
unsigned int BVNode::getPotentialContacts(CollisionCandids* candids, unsigned limit)
{
    if(this->isLeaf() || limit == 0){
        return 0;
    }
    return children[0]->getPotentialContactsWith(children[1], candids, limit);
}
bool BVNode::overlaps(BVNode* other)
{
    return this->volume.overlaps(&(other->volume));
}
unsigned int BVNode::getPotentialContactsWith(BVNode* other, CollisionCandids* candids, unsigned limit)
{
    if(!overlaps(other) || limit == 0)
    {
        return 0;
    }

    if(isLeaf() && other->isLeaf())
    {
        //Add as collision candid
        candids->body[0] = this->body;
        candids->body[1] = other->body;
        return 1;
    }

    //Determine which node to ascend to. If other is a leaf ascend into this (this is not a leaf a.t.p.). Ascend to this also if the volume of this is larger than other
    if(other->isLeaf() || (!isLeaf() && this->volume.getVolume() >= other->volume.getVolume()))
    {
        unsigned count = children[0]->getPotentialContactsWith(other, candids, limit);
        if(limit>count)
        {
            return count + children[1]->getPotentialContactsWith(other, candids+count, limit-count);
        }else{
            return count;
        }
    }else{
        //Ascend into the other recursively
        unsigned count = getPotentialContactsWith(other->children[0], candids, limit);
        if(limit>count)
        {
            return count + getPotentialContactsWith(other->children[1], candids+count, limit-count);
        }else{
            return count;
        }
    }
}
void BVNode::insert(Collider2D* newCollider, BoundingBox2D newVolume)
{
    if(isLeaf())
    {
        children[0] = new BVNode(this, this->volume, this->body);
        children[1] = new BVNode(this, newVolume, newCollider); //Adding the new body to right
        this->body = nullptr; //This is no longer a leaf
        
        //Get the combined
        BoundingBox2D* combined = (BoundingBox2D*) children[0]->volume.getCombinedVolume(&(children[1]->volume));
        this->volume = *combined;
    }else{
        BoundingBox2D* growth0 = (BoundingBox2D*) children[0]->volume.getCombinedVolume(&newVolume);
        BoundingBox2D* growth1 = (BoundingBox2D*) children[1]->volume.getCombinedVolume(&newVolume); 
        if(growth0->getVolume() > growth1->getVolume())
        {
            //Add to children[0]
            children[0]->insert(newCollider, newVolume);
        }else{
            children[0]->insert(newCollider, newVolume);
        }
    }
}
