# sudoku and libsudoku
#
# Copyright 2011 Philipp Wähnert <phil.wnrt@googlemail.com>
#
# sudoku and libsudoku are free software; you can redistribute them and/or modify
# them under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# These programs are distributed in the hope that they will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(sudoku)

#SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#MESSAGE(STATUS "${CMAKE_CXX_FLAGS_DEBUG}")
ADD_DEFINITIONS("-Wall -Wextra -pedantic")

SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED OFF)
FIND_PACKAGE(Boost 1.35.0)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
# MESSAGE(STATUS ${Boost_LIBRARIES})

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
INCLUDE(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

ENABLE_TESTING()

INCLUDE_DIRECTORIES(include)

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(src)

#INCLUDE_DIRECTORIES(include)

#ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(test)
