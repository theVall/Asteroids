/**
 * glNormal.h
 *
 *  @date 02.01.2012
 *  @author Thomas Wiemann
 */

#ifndef GLNORMAL_H_
#define GLNORMAL_H_

#include "glVector.hpp"

template<typename T>
class glNormal : public glVector<T>
{
public:

    glNormal(const glVector<T> &v );
    glNormal(T x, T y, T z);

    virtual ~glNormal();

    /**
     * @brief   Normalize a glVector
     */
    void normalize();
};

#include "glNormal.tcc"

#endif /* GLNORMAL_H_ */
