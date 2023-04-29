#
# This function adds a test.
#
function(add_lab_test test_name)
  set(test_source "${test_name}.cpp")
  set(test_exe "${test_name}")
  add_executable(${test_exe} ${test_source})
  target_include_directories(${test_exe} PUBLIC "${CMAKE_SOURCE_DIR}/include")
  target_include_directories(${test_exe} PUBLIC "${CMAKE_SOURCE_DIR}/external")
  add_test(${test_exe} ${test_exe})
endfunction()

