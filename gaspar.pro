TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CXXFLAGS += -std=c++11

QMAKE_LIBS += -lboost_program_options -lgomp

SOURCES += main.cpp

HEADERS += \
    writerUtils.hpp \
    vtkStructuredPointsWriter.hpp \
    trilinear.hpp \
    structuredGrid.hpp \
    isoWriter.hpp \
    digitization.hpp \
    criticalPoints.hpp \
    vis/mouse.hpp \
    vis/material.hpp \
    vis/lighting.hpp \
    vis/keyboard.hpp \
    vis/interface.hpp \
    vis/common.hpp \
    io/writerUtils.hpp \
    io/vtkStructuredPointsWriter.hpp \
    io/nrrdWriter.hpp \
    io/isoWriter.hpp \
    gl/mouse.hpp \
    gl/material.hpp \
    gl/lighting.hpp \
    gl/keyboard.hpp \
    gl/interface.hpp \
    gl/common.hpp \
    gl/opengl.hpp \
    io/writer.h \
    cases.hpp

