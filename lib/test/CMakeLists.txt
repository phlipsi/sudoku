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

ADD_EXECUTABLE(celltest celltest.cpp)

ADD_EXECUTABLE(fieldtest fieldtest.cpp)
TARGET_LINK_LIBRARIES(fieldtest sudoku)

#ADD_EXECUTABLE(dancingtest dancingtest.cpp)
#TARGET_LINK_LIBRARIES(dancingtest sudoku)

ADD_EXECUTABLE(techniquestest techniquestest.cpp)
TARGET_LINK_LIBRARIES(techniquestest sudoku)

ADD_EXECUTABLE(solvertest solvertest.cpp)
TARGET_LINK_LIBRARIES(solvertest sudoku)

ADD_EXECUTABLE(symmetrytest symmetrytest.cpp)
TARGET_LINK_LIBRARIES(symmetrytest sudoku)
