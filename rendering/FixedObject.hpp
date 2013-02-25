/**
 * @file FixedObject.hpp
 * @author Gruppe 2
 */

#ifndef FIXEDOBJECT_HPP_
#define FIXEDOBJECT_HPP_

#include "Renderable.hpp"

/**
 * @brief   Interface stub to mark object that cannot be moved.
 */
class FixedObject : public Renderable
{
    public:
        FixedObject() {}
};

#endif /* FixedObject.hpp */
