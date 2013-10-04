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
    ariane::ariane( const gladys::weight_map& _wm, //{{{
                    double _max_step_length, double _curb_tolerance ) :
        ng ( _wm)
    {
        max_step_length = _max_step_length ;
        curb_tolerance = _curb_tolerance ;
    }//}}}

    /* computing functions */
    void ariane::update( const gladys::weight_map& _wm ) {//{{
        //TODO when ng is updatable
    }//}}}

    gladys::path_t ariane::plan( const gladys::point_xy_t &start, const gladys::point_xy_t &goal ) const {//{{{
        gladys::path_t path ;
        gladys::path_t waypoints ;

        /* compute path */
        std::cerr << "[ariane] Computing path... " << std::endl ;
        try {
            path = ng.astar_search(start, goal) ;
        } catch (std::exception& e) {
            std::cerr << "[ariane] catch exception : " << e.what() << std::endl ;
            std::cerr << "[ariane] Fail to compute a valid path : please check your data." << std::endl ;
            return waypoints ;
        }

        /* compute waypoints (= a specific subset of the path) */
        std::cerr << "[ariane] path computed. Extracting waypoints..." << std::endl ;

        //TODO
        waypoints = path ;

        /* the end */
        std::cerr << "[ariane] Done." << std::endl ;

        return waypoints ;

    }//}}}

//}}} ariane class
} // namespace  ariane

