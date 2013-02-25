/**
 * @file Renderable.hpp
 * @author Gruppe 2
 */

#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

/**
 * @brief Interface class for all objects that support rendering.
 */
class Renderable
{
public:

    /**
     * @brief   Renders the object.
     */
    virtual void render() = 0;
};

#endif /* Renderble.hpp */
