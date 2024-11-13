include_directories(${CMAKE_CURRENT_SOURCE_DIR}/model ${CMAKE_CURRENT_SOURCE_DIR}/helper)

check_include_file_cxx(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif()

set(examples_as_tests_sources)
if(${ENABLE_EXAMPLES})
    set(examples_as_tests_sources
        #test/sagin-examples-test-suite.cc
        )
endif()

set(source_files
    model/sagin-node.cc
    model/aerial-node.cc
    model/space-node.cc
    model/ground-node.cc
    model/sagin-mac.cc
    model/sagin-phy.cc
    model/sagin-routing.cc
    model/node-address.cc
    helper/sagin-helper.cc
)

set(header_files
    model/sagin-node.h
    model/aerial-node.h
    model/space-node.h
    model/ground-node.h
    model/node-address.h
    model/sagin-mac.h
    model/sagin-phy.h
    model/sagin-routing.h
    helper/sagin-helper.h
)

build_lib(
    LIBNAME sagin
    SOURCE_FILES ${source_files}
    HEADER_FILES ${header_files}
    LIBRARIES_TO_LINK ${libcore} ${libmobility} ${libapplications}
    TEST_SOURCES test/sagin-test-suite.cc
                 ${examples_as_tests_sources}
)
