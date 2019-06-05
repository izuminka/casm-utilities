#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "casmutils/stage.hpp"

namespace WrapPy
{
    void example(){return;}

PYBIND11_MODULE(_stage, m)
{
    using namespace pybind11;
    using namespace WrapPy;

    class_<SpecializedEnumeration::LayerSkewer>(m, "LayerSkewer")
        .def("is_primitive", &Rewrap::Structure::is_primitive)
        .def("primitive", &Rewrap::Structure::primitive)
    m.doc() = "This is only temporary, don't get too attached. Make it a real module.";

    m.def("example", WrapPy::example);
}
}
