add_library( ariane SHARED ariane.cpp )
target_link_libraries( ariane ${LIBGLADYS_LIBRARIES} )
install(TARGETS ariane DESTINATION ${CMAKE_INSTALL_LIBDIR})
install_pkg_config_file(libariane
    DESCRIPTION "eXploration module for Autonomous Robotic Embedded Systems"
    CFLAGS
    LIBS -lariane
    VERSION ${PACKAGE_VERSION}
    REQUIRES "gladys >= ${GLADYS_MIN_VERSION}")

add_executable( ariane_play offline_play.cpp )
target_link_libraries(ariane_play ariane ${GDALWRAP_LIBRARIES} )
install(TARGETS ariane_play DESTINATION ${CMAKE_INSTALL_BINDIR})

#add_executable( foo foo.cpp )
#target_link_libraries( foo ariane ${LIBGLADYS_LIBRARIES} ${GDALWRAP_LIBRARIES} )
#install(TARGETS foo DESTINATION ${CMAKE_INSTALL_BINDIR})

