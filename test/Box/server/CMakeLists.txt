cmake_minimum_required (VERSION 2.8.7)
#include(ExternalProject)

project(Box-Server)

INCLUDE($ENV{HOME}/.config.cmake)

#include_directories(../../nebula/src ../../glutpp/src ../../galaxy/src ../../math/src)
#link_directories(../../nebula ../../glutpp ../../galaxy ../../math)

link_exe()

#SET(CPACK_GENERATOR "DEB")
#SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Charles Rymal") #required
#SET(CPACK_PACKAGE_VERSION_MAJOR "0")
#SET(CPACK_PACKAGE_VERSION_MINOR "1")
#SET(CPACK_PACKAGE_VERSION_PATCH "1") 

#INCLUDE(CPack)


