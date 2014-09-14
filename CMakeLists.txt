###| kii-dfu CMake Build System |###
#
# Jacob Alexander 2014
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###

cmake_minimum_required ( VERSION 2.8.9 )
set ( TARGET kii-dfu )
project ( ${TARGET} )

set ( CMAKE_AUTOMOC ON )
set ( CMAKE_INCLUDE_CURRENT_DIR ON )

add_definitions ( -ggdb )

find_package ( Qt5Widgets REQUIRED )

qt5_wrap_ui ( UI_HDRS
	mainwindow.ui
)

set ( SRCS
	main.cpp
	mainwindow.cpp
)

add_executable ( ${TARGET} ${SRCS} ${UI_HDRS} )

qt5_use_modules ( ${TARGET} Widgets )

