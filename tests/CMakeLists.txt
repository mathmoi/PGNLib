# enable c++11 for gcc
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# We set maximum warnings
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

include_directories(${PGNPARSER_SOURCE_DIR}/include ${UnitTest++_SOURCE_DIR}/UnitTest++)

add_executable(pgnparser-tests 
                  BitboardTests.cpp    PgnParserTests.cpp     PieceTests.cpp
                  ChessboardTests.cpp  PgnTagsTests.cpp       SANParserTests.cpp
                  mainTests.cpp        PgnTokenizerTests.cpp  UtilsTest.cpp)

target_link_libraries(pgnparser-tests UnitTest++)
target_link_libraries(pgnparser-tests pgn)

