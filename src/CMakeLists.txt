cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        src main.cpp
        Newton.cpp Newton.h
        Point.cpp Point.h
        Function.h Function.cpp
        AbstractMethods.cpp AbstractMethods.h
        NewtonDirectionDescent.cpp NewtonDirectionDescent.h
        OptimisationNewton.cpp OptimisationNewton.h
        PowellMethod.cpp PowellMethod.h
        BFGSMethod.cpp BFGSMethod.h)