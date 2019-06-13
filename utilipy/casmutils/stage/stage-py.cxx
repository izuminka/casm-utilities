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

    //TODO: Make this not a class, just standalone functions (use WrapPy or redefine them in python)

    m.doc() = "The skewer class takes a supercell and will skew the c vector to create new orderings.";

    class_<SpecializedEnumeration::LayerSkewer>layerskewer(m, "LayerSkewer");

        layerskewer.def(init<const Rewrap::Structure,const Rewrap::Structure,SpecializedEnumeration::LayerSkewer::STACKING_DIRECTION>())
        .def("distinct_skewed_strucs", &SpecializedEnumeration::LayerSkewer::distinct_skewed_strucs)
        .def("all_skewed_strucs", &SpecializedEnumeration::LayerSkewer::all_skewed_strucs);

    /* std::vector<Rewrap::Structure> distinct_skewed_strucs() const; */
    /// Generate all possible skewed versions of superstructure, even if symmetrically equivalent
    /* std::vector<Rewrap::Structure> all_skewed_strucs() const; */

    enum_<SpecializedEnumeration::LayerSkewer::STACKING_DIRECTION>(layerskewer, "STACKING_DIRECTION")
    .value("A", SpecializedEnumeration::LayerSkewer::STACKING_DIRECTION::A)
    .value("B", SpecializedEnumeration::LayerSkewer::STACKING_DIRECTION::B)
    .value("C", SpecializedEnumeration::LayerSkewer::STACKING_DIRECTION::C)
    .export_values();
}
}
