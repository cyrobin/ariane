/*
 * ariane.hpp
 *
 * TODO
 *
 * author:  Cyril Robin <cyril.robin@laas.fr>
 * created: 2013-10-03
 * license: BSD
 */

#include <ostream>
#include <exception>
#include <limits>       // for numeric_limits::infinity

#include "ariane/ariane.hpp"

namespace ariane {

/*{{{ ariane class
 ****************************************************************************/
    /* constructor */
    ariane::ariane( const gladys::weight_map& _wm ) : ng ( _wm)//{{{
    {
    }//}}}

    /* computing functions */

    gladys::points_t ariane::plan( const gladys::point_xy_t &start, const gladys::point_xy_t &goal ){//{{{
        gladys::points_t path ;
        gladys::points_t waypoints ;

        /* compute path */
        std::cerr << "[ariane] Computing path... " << std::endl ;
        try {
            //TODO
        } catch (std::exception& e) {
            std::cerr << "[ariane] catch exception : " << e.what() << std::endl ;
            std::cerr << "[ariane] Fail to compute a valid path : please check your data." << std::endl ;
            return waypoints ;
        }

        /* compute waypoints (= a specific subset of the path) */
        std::cerr << "[ariane] path computed. Extracting waypoints..." << std::endl ;

        //TODO

        /* the end */
        std::cerr << "[ariane] Done." << std::endl ;

        return waypoints ;

    }//}}}

//}}} ariane class
} // namespace  ariane

