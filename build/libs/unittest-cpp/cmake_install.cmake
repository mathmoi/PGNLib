# Install script for directory: /home/mathmoi/pgnparser/libs/unittest-cpp

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/mathmoi/pgnparser/build/libs/unittest-cpp/libUnitTest++.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/AssertException.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/CheckMacros.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/Checks.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/CompositeTestReporter.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/Config.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/CurrentTest.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/DeferredTestReporter.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/DeferredTestResult.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/ExceptionMacros.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/ExecuteTest.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/HelperMacros.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/MemoryOutStream.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/ReportAssert.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/ReportAssertImpl.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/Test.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestDetails.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestList.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestMacros.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestReporter.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestReporterStdout.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestResults.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestRunner.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TestSuite.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TimeConstraint.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/TimeHelpers.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/UnitTest++.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/UnitTestPP.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/XmlTestReporter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Posix" TYPE FILE FILES
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/Posix/SignalTranslator.h"
    "/home/mathmoi/pgnparser/libs/unittest-cpp/UnitTest++/Posix/TimeHelpers.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

