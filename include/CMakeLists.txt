add_library(INCLUDE SHARED barnes_hut_tree.cpp body.cpp n_body_sim.cpp)

target_link_libraries(INCLUDE PUBLIC sfml-graphics sfml-window sfml-system)

target_include_directories(INCLUDE PUBLIC ${CMAKE_SOURCE_DIR}/include)
