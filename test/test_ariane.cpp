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

BOOST_AUTO_TEST_SUITE( ariane )

BOOST_AUTO_TEST_CASE( test_ariane )
{
   BOOST_TEST_MESSAGE( "Test ToDo " << true );
   BOOST_CHECK_EQUAL( true , true );

}
BOOST_AUTO_TEST_SUITE_END();

