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
    //void ariane::update( const gladys::weight_map& _wm ) {//{{{
        //TODO when ng is updatable
    //}//}}}

    gladys::path_t ariane::plan( const gladys::point_xy_t &start, const gladys::point_xy_t &goal ) const {//{{{
        gladys::detailed_path_t d_path ;
        gladys::path_t waypoints ;

        /* compute path */
        std::cerr << "[ariane] Computing path... " << std::endl ;
        try {
            d_path = ng.detailed_astar_search(start, goal) ;
        } catch (std::exception& e) {
            std::cerr << "[ariane] catch exception : " << e.what() << std::endl ;
            std::cerr << "[ariane] Fail to compute a valid path : please check your data." << std::endl ;
            return waypoints ;
        }

        /* compute waypoints (= a specific subset of the path) */
        std::cerr << "[ariane] path computed. Extracting waypoints..." << std::endl ;

        // when no path have been found
        if ( d_path.path.empty() )
            return waypoints ;

        unsigned int i = 0 ;
        gladys::point_xy_t last = d_path.path[i];
        double cost, dist, last_cost = d_path.costs[i]; // cost in the nav_graph (time)
        double v = ng.get_map().get_robot().get_velocity() ; // robot velocity

        i++;
        for ( ; i < d_path.path.size() ; i++ ) {
            cost = d_path.costs[i] - last_cost;         // cost since the last waypoint
            dist = gladys::distance( last, d_path.path[i] );    // euclidian distance

            if ( cost > max_step_length
            ||   cost * v  > ( 1 + curb_tolerance ) * dist )
            {
                //new waypoint
                last = d_path.path[i] ;
                last_cost = d_path.costs[i] ;
                waypoints.push_back( last );
            }
        }

        /* the end */
        std::cerr << "[ariane] Done." << std::endl ;

        return waypoints ;

    }//}}}

//}}} ariane class
} // namespace  ariane

