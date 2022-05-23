#include "Collider.h"
#include "BoundingVolume.h"

struct CollisionCandids{
    Collider2D* body[2];
};

class BVNode
{
    public:
    //Defines a binary tree that contains the bounding volumes available in the sceene. Use insertion method to construct the tree
    BVNode();
    BVNode(BVNode* parent, BoundingBox2D volume, Collider2D* body);
    ~BVNode();
    //Variables
    BVNode* parent;
    BVNode* children[2];
    BoundingBox2D volume;
    Collider2D* body;

    //Methods
    bool isLeaf();
    unsigned int getPotentialContacts(CollisionCandids* candids, unsigned limit);
    bool overlaps(BVNode* other);
    unsigned int getPotentialContactsWith(BVNode* other, CollisionCandids* candids, unsigned limit);
    void insert(Collider2D* newCollider, BoundingBox2D newVolume);
};