/*
 * test_ariane.cpp
 *
 * Test the ariane module.
 *
 * author:  Cyril Robin <cyril.robin@laas.fr>
 * created: 2013-10-03
 * license: BSD
 */
#define BOOST_TEST_MODULE const_string test
#include <boost/test/included/unit_test.hpp>

#include <sstream>

#include "ariane/ariane.hpp"
#include "gdalwrap/gdal.hpp"
#include "gladys/nav_graph.hpp"


BOOST_AUTO_TEST_SUITE( ariane )

BOOST_AUTO_TEST_CASE( test_ariane )
{
    std::string region_path = "/tmp/test_map.tif";
    std::string weight_path = "/tmp/test_wm.tif";
    std::string robotm_path = "/tmp/robot.json";

    // create a robot model (JSON configuration file)
    std::ofstream robot_cfg(robotm_path);
    robot_cfg<<"{\"robot\":{\"mass\":1.0,\"radius\":1.0,\"velocity\":2.0}}";
    robot_cfg.close();

    /* create a region map (GeoTiff image)
     *
     *  U = unknown
     *  F = flat
     *  O = obstacle
     *  S = start (flat ; initial position)
     *  G = goal (flat)
     *
     *       1 2 3 4 5 6 7 8 9
     *
     *  1    F F F S F F F F F
     *  2    F F F F F F F F F
     *  3    F F F F F F F F F
     *  4    O O O O O O O F F
     *  5    G F F F F F 0 F F
     *  6    F F F F F F 0 F F
     *  7    F F F F F F F F F
     *  8    F F F F F F F F F
     *  9    F F F F F F F F F
     *
     */
    gdalwrap::gdal region;
    region.set_size(4, 9, 9);
    region.bands[1].assign(9*9, 1);
    region.names = {"NO_3D_CLASS", "FLAT", "OBSTACLE", "ROUGH"};
    for ( int i=0 ; i < 7 ; i++ ) {
        region.bands[1][i+3*9] = 0.2 ;
        region.bands[2][i+3*9] = 0.8 ;
    }
    for ( int j=3 ; j < 7 ; j++ ) {
        region.bands[1][7+j*9] = 0.2 ;
        region.bands[2][7+j*9] = 0.8 ;
    }

    region.save(region_path);

    // create a frontier exploration module from the map
    // (Create the weight_map, assumed to be good; cf other unit test)
    gladys::weight_map wm( region_path, robotm_path ) ;
    ariane ariadne ( wm, 6.0, 0.1) ;

    // testing  path planning
    gladys::point_xy_t s {4,1};
    gladys::point_xy_t g {1,5};
    gladys::path_t path = ariadne.plan( s, g ) ;

   //Check the number of  waypoints
   BOOST_TEST_MESSAGE( "Path: " + gladys::to_string(path) );
   BOOST_CHECK_EQUAL( path.size() , 4 );

}


BOOST_AUTO_TEST_SUITE_END();
