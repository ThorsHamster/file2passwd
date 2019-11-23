set(GSL_LITE_INCLUDE_DIR include)
add_library(gsl INTERFACE)
target_include_directories(gsl INTERFACE ${GSL_LITE_INCLUDE_DIR})