set(NAME core)

set(HEADERS
  Faces.hpp
) # HEADERS    

set(SOURCES
  Faces.cpp
) # SOURCES

add_library(${NAME}
    ${HEADERS}
    ${SOURCES}
) # add_library

target_compile_features(${NAME} PRIVATE cxx_lambdas)

target_link_libraries(${NAME} ${LIB_LIST})


