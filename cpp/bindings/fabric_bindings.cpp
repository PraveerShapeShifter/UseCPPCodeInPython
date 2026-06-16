#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Fabric.h"
#include "FabricWrapper.h"
#include "cstring_caster.h"

namespace py = pybind11;

PYBIND11_MODULE(fabric, m) {
    m.doc() = "Fabric domain functions from the ShapeShifter C++ core";

    py::class_<SizeRatio>(m, "SizeRatio")
        .def_readwrite("name", &SizeRatio::name)
        .def_readwrite("quantity", &SizeRatio::quantity);

    py::class_<FabricDetails>(m, "FabricDetails")
        .def_readwrite("name", &FabricDetails::name)
        .def_readwrite("type", &FabricDetails::type)
        .def_readwrite("sizeRatios", &FabricDetails::sizeRatios)
        .def_readwrite("width", &FabricDetails::width)
        .def_readwrite("length", &FabricDetails::length)
        .def("to_dict", [](const FabricDetails& f) {
            py::list ratios;
            for (const auto& s : f.sizeRatios) {
                py::dict r;
                r["name"] = s.name;
                r["quantity"] = s.quantity;
                ratios.append(r);
            }
            py::dict d;
            d["name"] = f.name;
            d["type"] = f.type;
            d["sizeRatios"] = ratios;
            d["width"] = f.width;
            d["length"] = f.length;
            return d;
        }, "Plain-dict form, ready for flask.jsonify");

    py::class_<Fabric>(m, "Fabric")
        .def(py::init<>())
        .def(py::init<FabricDetails>(), py::arg("details"))
        .def("getDetails", &Fabric::getDetails, py::return_value_policy::reference_internal,
             "Return this fabric's details")
        // CString return type converts automatically via cstring_caster.h
        .def("getName", &Fabric::getName, "Return the project name");

    m.def("getFabricDetails", &getFabricDetails, "Return the fabric details");
    // CString return type converts automatically via cstring_caster.h
    m.def("getMyName", &getMyName, "Return the project name");
}
