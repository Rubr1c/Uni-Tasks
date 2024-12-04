# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-src"
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-build"
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix"
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix/tmp"
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix/src/libxlsxwriter-populate-stamp"
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix/src"
  "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix/src/libxlsxwriter-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix/src/libxlsxwriter-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/aliza/source/repos/Uni-Tasks/Uni-Tasks/cmake-build-debug/_deps/libxlsxwriter-subbuild/libxlsxwriter-populate-prefix/src/libxlsxwriter-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
