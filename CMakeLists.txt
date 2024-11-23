cmake_minimum_required(VERSION 3.15)

# Название проекта и версия
project(sneaky_face)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути до Qt и OpenCV
set(Qt5_DIR "C:/Qt/Qt5.12.8/5.12.8/msvc2017_64/lib/cmake/Qt5")
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

# Включение функций автоматической обработки Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Подключение Qt
find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)

# Подключение OpenCV
find_package(OpenCV REQUIRED)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/videowindow.cpp
    src/mainwindow.ui
)

set(HEADERS
    src/mainwindow.h
    src/videowindow.h
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Линковка библиотек
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    ${OpenCV_LIBS}
)

# Включение директорий
target_include_directories(${PROJECT_NAME}
    PRIVATE ${OpenCV_INCLUDE_DIRS}
)
