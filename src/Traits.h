#ifndef TRAITS_H
#define TRAITS_H

namespace vc{
    /*
        This class doesn't do any work, but it does allow different class to use the same data type (i.e double)
        There must be a Traits<T> class implemented for every tensor class or it won't compile.
    */
    template<typename T, typename Enable = void> class Traits;

}

#endif
