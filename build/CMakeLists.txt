cmake_minimum_required (VERSION 2.6)

set(SRC_DIR  ${PROJECT_SOURCE_DIR}/../src)
set(FORM_DIR ${PROJECT_SOURCE_DIR}/../forms)

find_package(Qt4 REQUIRED)
find_package(PCL REQUIRED)
find_package(OpenCV 2.4.6.1 REQUIRED)

include(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${PCL_INCLUDE_DIRS})

add_definitions(${QT_DEFINITIONS})
add_definitions(${PCL_DEFINITIONS})
add_definitions(-Wall -O2 -ffast-math -ftree-vectorize -fomit-frame-pointer -pipe -mfpmath=sse -mmmx -msse -mtune=core2 -march=core2 -msse2 -msse3 -mssse3 -msse4)


set(MOC_HEADERS
    ${SRC_DIR}/OpenCvWidget.h
    ${SRC_DIR}/CalibrationViewWidget.h
    ${SRC_DIR}/sensors/ThermoCamThread.h
    ${SRC_DIR}/sensors/ISensor.h
    ${SRC_DIR}/MainWindow.h
    ${SRC_DIR}/ConfigDialog.h
    ${SRC_DIR}/IntrinsicCalibration.h
    ${SRC_DIR}/ImageContainerWidget.h
    )

set(FORMS
    ${FORM_DIR}/MainWindow.ui
    ${FORM_DIR}/ConfigDialog.ui
    ${FORM_DIR}/CalibrationViewWidget.ui
    ${FORM_DIR}/ImageContainerWidget.ui
    )

SET(GUI_RESOURCES ${PROJECT_SOURCE_DIR}/../resources/resources.qrc)

QT4_WRAP_CPP(HEADERS_MOC    ${MOC_HEADERS})
QT4_WRAP_UI(FORMS_MOC       ${FORMS})
QT4_ADD_RESOURCES(RESOURCES ${GUI_RESOURCES})

include_directories(${PROJECT_SOURCE_DIR}/build
                    ${SRC_DIR}
                    ${OpenCV_INCLUDE_DIRS}
                    )

link_directories(${OpenCV_LIBRARY_DIRS}
                 ${PCL_LIBRARY_DIRS}
                 ${PROJECT_SOURCE_DIR}/../lib
                 )

add_executable(optris-calibration-tool
               ${SRC_DIR}/main.cpp
               ${SRC_DIR}/OpenCvWidget.cpp
               ${SRC_DIR}/CalibrationViewWidget.cpp
               ${SRC_DIR}/MainWindow.cpp
               ${SRC_DIR}/sensors/ThermoCamThread.cpp
               ${SRC_DIR}/sensors/ReadFromFile.cpp
               ${SRC_DIR}/sensors/ThermoCam.cpp
               ${SRC_DIR}/sensors/Openni.cpp
               ${SRC_DIR}/sensors/CheckDevices.cpp
               ${SRC_DIR}/ConfigDialog.cpp
               ${SRC_DIR}/IntrinsicCalibration.cpp
               ${SRC_DIR}/ImageContainerWidget.cpp
               
               ${SRC_DIR}/sensors/RGBCamera.cpp
               ${HEADERS_MOC}
               ${FORMS_MOC}
               ${RESOURCES}
               )

target_link_libraries(optris-calibration-tool
                      ${QT_LIBRARIES}
                      ${OpenCV_LIBS}
                      ${PCL_LIBRARIES}
                      irimager 
                      irimageprocessing
                      udev
                      )
                      
