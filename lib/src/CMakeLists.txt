# libsudoku
#
# Copyright 2011 Philipp Wähnert <phil.wnrt@googlemail.com>
#
# libsudoku is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.

SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED OFF)
FIND_PACKAGE(Boost 1.40.0)# REQUIRED filesystem system)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
# MESSAGE(STATUS ${Boost_LIBRARIES})

ADD_LIBRARY(sudoku STATIC positions.cpp field.cpp sudoku.cpp action.cpp common_actions.cpp nakedsingle.cpp backtracking.cpp hiddensingle.cpp proceeding.cpp solver.cpp) #dancingsolver.cpp dancinglinks.cpp)
TARGET_LINK_LIBRARIES(sudoku ${Boost_LIBRARIES})
 
