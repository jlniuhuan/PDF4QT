#    Copyright (C) 2022 Jakub Melka
#
#    This file is part of PDF4QT.
#
#    PDF4QT is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    with the written consent of the copyright owner, any later version.
#
#    PDF4QT is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with PDF4QT.  If not, see <https://www.gnu.org/licenses/>.

add_library(DimensionsPlugin SHARED
    dimensionsplugin.cpp
    dimensiontool.cpp
    settingsdialog.cpp
    settingsdialog.ui
    icons.qrc
)

target_link_libraries(DimensionsPlugin PRIVATE Pdf4QtLib Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets)

set_target_properties(DimensionsPlugin PROPERTIES
                      VERSION ${PDF4QT_VERSION}
                      SOVERSION ${PDF4QT_VERSION}
                      LIBRARY_OUTPUT_DIRECTORY ${PDF4QT_PLUGINS_DIR}
                      RUNTIME_OUTPUT_DIRECTORY ${PDF4QT_PLUGINS_DIR})

install(TARGETS DimensionsPlugin RUNTIME DESTINATION bin/pdfplugins/)
