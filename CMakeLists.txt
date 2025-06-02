# SPECIFY THE MINIMUM VERSION OF CMAKE REQUIRED
cmake_minimum_required(VERSION 2.8.12)

# SPECIFY YOUR PROJECT NAME
PROJECT(sampleCode)

# Enable C++11
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



# find opencv
find_package( OpenCV REQUIRED )
include_directories(include ${OpenCV_INCLUDE_DIRS})

# find FMT
find_package(fmt CONFIG REQUIRED)

# find boost
find_package(Boost REQUIRED COMPONENTS system filesystem)

# MACRO TO COMPILE CPP FILES
# Do Not Edit
MACRO(add_example name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
  TARGET_LINK_LIBRARIES(${name}  ${OpenCV_LIBS}  fmt::fmt )
ENDMACRO()


# COMPILE CPP FILES USING THIS LINE
######## EDIT THE FILE NAMES ########
add_example(sample)
add_example(math_op)
