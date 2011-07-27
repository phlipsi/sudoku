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

ADD_EXECUTABLE(boolarraytest boolarraytest.cpp)
TARGET_LINK_LIBRARIES(boolarraytest sudoku)

ADD_EXECUTABLE(celltest celltest.cpp)

ADD_EXECUTABLE(fieldtest fieldtest.cpp)
TARGET_LINK_LIBRARIES(fieldtest sudoku)

#ADD_EXECUTABLE(dancingtest dancingtest.cpp)
#TARGET_LINK_LIBRARIES(dancingtest sudoku)

ADD_EXECUTABLE(techniquestest techniquestest.cpp)
TARGET_LINK_LIBRARIES(techniquestest sudoku)

ADD_EXECUTABLE(fullhousetest fullhousetest.cpp)
TARGET_LINK_LIBRARIES(fullhousetest sudoku)

ADD_EXECUTABLE(hiddensingletest hiddensingletest.cpp)
TARGET_LINK_LIBRARIES(hiddensingletest sudoku)

ADD_EXECUTABLE(lastinstancetest lastinstancetest.cpp)
TARGET_LINK_LIBRARIES(lastinstancetest sudoku)

ADD_EXECUTABLE(nakedpairtest nakedpairtest.cpp)
TARGET_LINK_LIBRARIES(nakedpairtest sudoku)

ADD_EXECUTABLE(nakedsingletest nakedsingletest.cpp)
TARGET_LINK_LIBRARIES(nakedsingletest sudoku)

ADD_EXECUTABLE(solvertest solvertest.cpp)
TARGET_LINK_LIBRARIES(solvertest sudoku)

ADD_EXECUTABLE(symmetrytest symmetrytest.cpp)
TARGET_LINK_LIBRARIES(symmetrytest sudoku)

ADD_EXECUTABLE(generatortest generatortest.cpp)
TARGET_LINK_LIBRARIES(generatortest sudoku)

ADD_TEST(boolarraytest boolarraytest)
ADD_TEST(celltest celltest)
ADD_TEST(fieldtest fieldtest)
ADD_TEST(symmetrytest symmetrytest)
ADD_TEST(fullhousetest fullhousetest)
ADD_TEST(hiddensingletest hiddensingletest)
ADD_TEST(lastinstancetest lastinstancetest)
ADD_TEST(nakedpairtest nakedpairtest)
ADD_TEST(nakedsingletest nakedsingletest)
