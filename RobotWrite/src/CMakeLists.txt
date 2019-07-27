cmake_minimum_required(VERSION 3.1)

project (main CXX)

add_executable(main main.cpp MainWindow.cpp)
target_link_libraries(main ${OpenCV_LIBS} ${TORCH_LIBRARIES} ${Qt5Core_LIBRARIES}
        ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES}
        ${Qt5Network_LIBRARIES} ${QT_LIBRARIES} ${FREENECT_INCLUDE_DIRS} ${FREENECT_LIBRARIES})