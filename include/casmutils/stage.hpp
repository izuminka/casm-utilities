#ifndef UTILS_STAGE_HH
#define UTILS_STAGE_HH

#include "casmutils/definitions.hpp"
#include "casmutils/structure.hpp"

namespace Simplicity
{
    //Find the next closest symmetrized structure
    Structure step_symmetrize(const Structure& low_sym_struc);
    Lattice step_symmetrize(const Lattice& low_sym_struc);

    //Find equivalent variants of a structure
    std::vector<Structure> find_structure_variants(const Structure& orig_struc);
    std::vector<Structure> find_structure_variants(const Structure& orig_struc, const SymGroup& target_group);

    //Get all variants inside a superstructure that can tile each variant
    //Also maximum boxiness? Diagonal transformation of prim/conventional cell
    std::vector<Structure> find_superduper_structure_variants(const Structure& orig_struc);
    
    std::vector<Coordinate> equivalent_sites_in_group(const Coordinate& start_coord, const SymGroup& enforced_group);

    //Symmetrize arbitrary scalar fields to enforce symmetry on the field
    ScalarField symmetrize_field(const ScalarField& original_field, const SymGroup& enforced_group);

    //Find point group of molecule
    //Already exists in new version
    
    
}
#endif
