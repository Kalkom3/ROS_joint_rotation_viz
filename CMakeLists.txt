cmake_minimum_required(VERSION 3.0.2)
project(wheels_rotation_plugin)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslint
  rqt_gui
  rqt_gui_cpp
  std_msgs
  message_generation
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()


catkin_python_setup()

roslint_cpp()

##generate_messages(DEPENDENCIES std_msgs)

catkin_package(

  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui_cpp std_msgs message_runtime

)


set (wheels_rotation_plugin_SRCS
  src/wheels_rotation_plugin/my_plugin.cpp
)

set(wheels_rotation_plugin_HDRS
  include/wheels_rotation_plugin/my_plugin.h
)

set(wheels_rotation_plugin_UIS
  resources/my_plugin.ui
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(wheels_rotation_plugin_MOCS ${wheels_rotation_plugin_HDRS})
  qt5_wrap_ui(wheels_rotation_plugin_UIS_H ${wheels_rotation_plugin_UIS})
else()
  qt4_wrap_cpp(wheels_rotation_plugin_MOCS ${wheels_rotation_plugin_HDRS})
  qt4_wrap_ui(wheels_rotation_plugin_UIS_H ${wheels_rotation_plugin_UIS})
endif()


include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
    ${wheels_rotation_plugin_SRCS}
    ${wheels_rotation_plugin_MOCS}
    ${wheels_rotation_plugin_UIS_H}
    )


target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(transmiter src/wheels_rotation_plugin/transmiter.cpp)
target_link_libraries(transmiter ${catkin_LIBRARIES})
##add_dependencies(transmiter wheels_rotation_plugin_generate_messages_cpp)


if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()
