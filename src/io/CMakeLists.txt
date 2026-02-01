set(NAME io)

set(HEADERS
  AppLoader.hpp
  AppSaver.hpp
  StrException.hpp
  Loader.hpp
  LoaderWrl.hpp
  LoaderStl.hpp
  Saver.hpp
  SaverWrl.hpp
  SaverStl.hpp
  Tokenizer.hpp
  TokenizerFile.hpp
  TokenizerString.hpp
) # HEADERS    

set(SOURCES
  AppLoader.cpp
  AppSaver.cpp
  LoaderWrl.cpp
  LoaderStl.cpp
  SaverWrl.cpp
  SaverStl.cpp
  Tokenizer.cpp
  TokenizerFile.cpp
  TokenizerString.cpp
) # SOURCES

add_library(${NAME}
    ${HEADERS}
    ${SOURCES}
) # add_library

target_compile_features(${NAME} PRIVATE cxx_lambdas)

target_link_libraries(${NAME} ${LIB_LIST})

