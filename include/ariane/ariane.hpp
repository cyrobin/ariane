/*
 * ariane.hpp
 *
 * TODO
 *
 * author:  Cyril Robin <cyril.robin@laas.fr>
 * created: 2013-10-03
 * license: BSD
 */
#ifndef ariane_HPP
#define ariane_HPP

#include <vector>

#include "gladys/weight_map.hpp"
#include "gladys/nav_graph.hpp"

namespace ariane {

/*{{{ ariane class
 ****************************************************************************/
/* ariane class */
class ariane{

private :
    /* internal data */
    //const gladys::weight_map& wm ;                    // the weight map (data)
    gladys::nav_graph ng ;                              // nav graph (from wm)

    /* internal parameters */

    /* hidden computing functions */

public:
    /** ariane constructor
     *
     * @param wm the weight_map (gladys)
     *
     */
    ariane( const gladys::weight_map& _wm ) ;

    /** plan a waypoints to the goal
     *
     * @param start : the starting position.
     * @param goal  : the goal position.
     *
     */
    gladys::points_t plan( const gladys::point_xy_t &start, const gladys::point_xy_t &goal );

    /* getters */
    std::array<double, 4> get_transform() const {//{{{
        //TODO take "North up" into account
        std::array<double, 4> transform;
        const gladys::weight_map& map = ng.get_map() ;

        transform[0] = map.get_scale_x() ;
        transform[1] = map.get_scale_y() ;
        transform[2] = map.get_utm_pose_x() ;
        transform[3] = map.get_utm_pose_y() ;

        return transform;
    }//}}}

};//}}}

} // namespace  ariane

#endif // ariane_HPP

