#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "transformobject.hpp"
#include "structs.hpp"
#include <map>

class PhysicObject : public TransformObject {
    friend class PhysicServer;
    enum SHAPE_TYPE:uint8_t { SHAPE_TYPE_RECTANGLE , SHAPE_TYPE_CIRCLE };

    struct RectangleShape{
        Vector2 extents;
        RectangleShape(){extents=Vector2();}
    };
    struct CircleShape{
        float radius;
        CircleShape(){radius=0;}
    };
    union CollisionShape {
        RectangleShape rect;
        CircleShape circle;
        CollisionShape(){};
    };


    private:
        uint8_t                         shape_type;
        CollisionShape                  shape;
        Vector2                         shape_offset;
        std::map< int,PhysicObject*>    colliding_bodies;
        void                            enteredTree() final;
        void                            exitedTree() final ;
    protected:
    public:
        int                 mask;
        Vector2             velocity;
        bool                onlyTrigger;
        
        PhysicObject();
        ~PhysicObject();

        int                         getMaskBit(uint8_t bit_0_7 ){return mask|bit_0_7 ;}
        void                        setMaskBit(uint8_t bit_0_7 , bool val);

        std::map<int,PhysicObject*> getCollidingBodies(){return colliding_bodies;};
        Vector2                     getShapeOffset(){return shape_offset;}
        void                        setShapeOffset( const Vector2& offset ){shape_offset = offset;};
        void                        setShapeRectangle( const Vector2& extents ){shape_type=SHAPE_TYPE_RECTANGLE;shape.rect.extents = extents;}
        void                        setShapeCircle( const float& radius ){shape_type=SHAPE_TYPE_CIRCLE;shape.circle.radius=radius;};
        bool                        checkIfCollidesWith( PhysicObject* other );

        virtual void                _collidesWith( PhysicObject* other ){};
};


#endif