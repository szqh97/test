
#ifndef  _direct_H_
#define  _direct_H_

#include <iostream>
#include "builder.h"
/*
 * =======================================================================
 *        Class:  Director
 *  Description:  
 * =======================================================================
 */
class Director
{
    public:
        Director ();                   /* constructor */
        void construct(Builder* b);

    protected:

    private:

}; /* -----  end of class Director  ----- */

#endif   /* ----- #ifndef _direct_H_  ----- */
