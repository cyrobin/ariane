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
        gladys::path_t path ;
        gladys::path_t waypoints ;

        const gdalwrap::gdal& map = ng.get_map().get_map() ;

        gladys::point_xy_t utm_start = map.point_custom2utm( start[0], start[1] );
        gladys::point_xy_t utm_goal  = map.point_custom2utm(  goal[0],  goal[1] );

        std::cerr << "[ariane] start is " << gladys::to_string(start) << " (utm : " << gladys::to_string(utm_start) << ")" << std::endl ;
        std::cerr << "[ariane] goal is " << gladys::to_string(goal) << " (utm : " << gladys::to_string(utm_goal) << ")" << std::endl ;

        /* compute path */
        std::cerr << "[ariane] Computing path... " << std::endl ;
        try {
            path = ng.astar_search(utm_start, utm_goal) ;
        } catch (std::exception& e) {
            std::cerr << "[ariane] catch exception : " << e.what() << std::endl ;
            std::cerr << "[ariane] Fail to compute a valid path : please check your data." << std::endl ;
            return waypoints ;
        }

        /* compute waypoints (= a specific subset of the path) */
        std::cerr << "[ariane] path computed (size = " << path.size() << "). Extracting waypoints..." << std::endl ;
        //std::cerr << "[ariane] current path (" << path.size() << ") is: " + gladys::to_string(path) << std::endl ;

        // when no path have been found
        if ( path.empty() )
            return waypoints ;

        unsigned int i = 0 ;
        double cumul_dist = 0, dist;
        gladys::point_xy_t curr = path[i];
        gladys::point_xy_t last = curr;

        i++;
        for ( ; i < path.size() ; i++ ) {
            dist        = gladys::distance( last, path[i] );    // euclidian distance
            cumul_dist += gladys::distance( curr, path[i] );    // euclidian distance
            curr = path[i] ;

            if ( cumul_dist > max_step_length || cumul_dist > ( 1 + curb_tolerance ) * dist )
            {
                //new waypoint
                last = curr ;
                cumul_dist = 0 ;
                waypoints.push_back( map.point_utm2custom( last[0], last[1] ));
            }
        }

        // always add the last point
        waypoints.push_back( map.point_utm2custom( curr[0], curr[1] ));

        /* the end */
        std::cerr << "[ariane] Done." << std::endl ;

        return waypoints ;

    }//}}}

//}}} ariane class
} // namespace  ariane

