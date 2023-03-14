find_package(SFML 2.5 REQUIRED graphics window system)

#
# This function adds an executable.
#
function(add_exe example_name)
  set(example_source "${example_name}.cpp")
  set(example_exe "${example_name}")
  add_executable(${example_exe} ${example_source})
  target_include_directories(${example_exe} PUBLIC "${CMAKE_SOURCE_DIR}/include")
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${example_exe} sfml-graphics sfml-window sfml-system)
endfunction()



add_exe(main)
