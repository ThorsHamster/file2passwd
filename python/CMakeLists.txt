set_property(SOURCE pyfile2passwd.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE pyfile2passwd.i PROPERTY SWIG_MODULE_NAME pyfile2passwd)
swig_add_library(pyfile2passwd
	TYPE SHARED
	LANGUAGE python
	OUTPUT_DIR ${CMAKE_BINARY_DIR}/python/${PROJECT_NAME}/pyfile2passwd
	SOURCES	pyfile2passwd.i)

target_include_directories(pyfile2passwd
	PRIVATE
	../include
	${PYTHON_INCLUDE_DIRS}
	)
set_property(TARGET pyfile2passwd PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

# note: macOS is APPLE and also UNIX !
if(APPLE)
	set_target_properties(pyfile2passwd PROPERTIES
		SUFFIX ".so"
		INSTALL_RPATH	"@loader_path;@loader_path/../../${PROJECT_NAME}/.libs"
		)
	set_property(TARGET pyFoo APPEND PROPERTY
		LINK_FLAGS "-flat_namespace -undefined suppress"
		)
elseif(UNIX)
	set_target_properties(pyfile2passwd PROPERTIES
    INSTALL_RPATH	"$ORIGIN:$ORIGIN/../../${PROJECT_NAME}/.libs"
		)
endif()

target_link_libraries(pyfile2passwd
	PRIVATE
	f2p_lib
	${PYTHON_LIBRARIES}
	)