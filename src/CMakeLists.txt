add_library( ariane SHARED ariane.cpp )
target_link_libraries( ariane ${LIBGLADYS_LIBRARIES} ${GDAL_LIBRARIES} )
install(TARGETS ariane DESTINATION ${CMAKE_INSTALL_LIBDIR})
install_pkg_config_file(libariane
    DESCRIPTION "eXploration module for Autonomous Robotic Embedded Systems"
    CFLAGS
    LIBS -lariane
    VERSION ${PACKAGE_VERSION}
    REQUIRES "gladys >= ${GLADYS_MIN_VERSION}")

#add_executable( foo foo.cpp )
#target_link_libraries( foo ariane ${LIBGLADYS_LIBRARIES} ${GDAL_LIBRARIES} )
#install(TARGETS foo DESTINATION ${CMAKE_INSTALL_BINDIR})

