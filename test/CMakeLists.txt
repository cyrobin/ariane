macro(add_ariane_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ariane ${GDALWRAP_LIBRARIES} )
    add_test(${name} ${name})
endmacro()

add_ariane_test(test_ariane)
