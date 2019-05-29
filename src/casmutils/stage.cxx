#include "include/casmutils/stage.hpp"
#include "casm/crystallography/Lattice.hh"
#include "casm/crystallography/Structure.hh"
#include "include/casmutils/structure.hpp"

void symmetrize(const Rewrap::Structure* struc_ptr, double tol)
{
    auto& sym_struc=*struc_ptr;
    // Use this to make sure you're getting a group size that makes sense later
    std::set<int> point_group_sizes{1, 2, 3, 4, 6, 8, 12, 16, 24, 48};

    // a) symmetrize the lattice vectors
    CASM::Lattice lat = sym_struc.lattice();
    lat.symmetrize(tol);
    // lat.set_tol(tol);
    CASM::SymGroup pg;
    // TODO: change interface within Rewrap for this call
    lat.generate_point_group(pg);

    // Your group size needs to be one of the values in the set at the top
    assert(point_group_sizes.find(pg.size()) != point_group_sizes.end());

    // Now the structure will have the symmetrized lattice
    sym_struc.set_lattice(lat, CASM::FRAC);

    sym_struc.generate_factor_group(tol);
    // b) find factor group with same tolerance
    sym_struc.fg_converge(tol); // TODO:  Is this for real necessary? Doesn't generate_factor_group do this?

    // Your group size needs to be one of the values in the set at the top
    assert(point_group_sizes.find(sym_struc.point_group().size()) != point_group_sizes.end());

    // c) symmetrize the basis sites
    sym_struc.symmetrize(sym_struc.factor_group());
    int biggest = struc.factor_group().size();
    assert(sym_struc.factor_group().is_group(tol) && (sym_struc.factor_group().size() >= biggest));

    return;
}

Rewrap::Structure symmetrize(const Rewrap::Structure& struc, double tol)
{
    auto mutable_struc=struc;
    symmetrize(&mutable_struc, tol);
    return mutable_struc;
}
