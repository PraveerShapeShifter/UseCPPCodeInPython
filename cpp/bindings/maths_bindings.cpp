#include <pybind11/pybind11.h>

#include "Maths.h"

namespace py = pybind11;

PYBIND11_MODULE(maths, m) {
    m.doc() = "Math helpers from the ShapeShifter C++ core";

    m.def("add_Numbers", &add_Numbers, "Add two numbers");
    m.def("multiply_Numbers", &multiply_Numbers, "Multiply two numbers");
    m.def("subtract_Numbers", &subtract_Numbers, "Subtract the second number from the first");
}
