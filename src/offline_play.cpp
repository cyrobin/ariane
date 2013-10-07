/*
 * offline_play.cpp
 *
 * Test the ariane module.
 *
 * author:  Cyril Robin <cyril.robin@laas.fr>
 * created: 2013-10-03
 * license: BSD
 */
#include <sstream>

#include "ariane/ariane.hpp"
#include "gdalwrap/gdal.hpp"
#include "gladys/nav_graph.hpp"

int main (int argc, char ** argv ) { 

    if (argc < 9) {
        std::cerr<<"usage: " << argv[0] << "region.tif robot.json max_step_length curb_tolerance xS yS xG yG" << std::endl;
        return EXIT_FAILURE;
    }


    // create a frontier exploration module from the map
    // (Create the weight_map, assumed to be good; cf other unit test)
    gladys::weight_map wm( argv[1], argv[2]) ;
    double a,b;
    sscanf(argv[3],"%lf",&a);
    sscanf(argv[4],"%lf",&b);
    ariane::ariane ariadne ( wm, a, b) ;

    // testing  path planning
    sscanf(argv[5],"%lf",&a);
    sscanf(argv[6],"%lf",&b);
    gladys::point_xy_t s { a, b };
    sscanf(argv[7],"%lf",&a);
    sscanf(argv[8],"%lf",&b);
    gladys::point_xy_t g { a, b };
    gladys::path_t path = ariadne.plan( s, g ) ;

   //Check the number of  waypoints
    std::cerr << "Waypoints (" << path.size() << " are : " + gladys::to_string(path) << std::endl;
   //BOOST_TEST_MESSAGE( "Path: " + gladys::to_string(path) );
   //BOOST_CHECK_EQUAL( path.size() , 4 );

   return EXIT_SUCCESS;
}

