#ifndef UTILS_STAGE_HH
#define UTILS_STAGE_HH

#include "casmutils/definitions.hpp"
#include "casmutils/structure.hpp"

namespace Simplicity
{


    /**
     * TODO: info
     * A class to generate different stackings (or "skewings") of layered superstructures
     * Supports enumeration of either all stackings, or all distinct stackings
     */

class LayerSkewer
{
public:
    //TODO: better name?
    enum class STACKING_DIRECTION {A,B,C};
    
    LayerSkewer() = delete;

    /// Construct by providing primitive structure and superstructure (assumed to be layered)
    /// Optionally can specify the index of the out-of-layer lattice vector for each structure, called c (default is third)
    LayerSkewer(const Rewrap::Structure &prim_struc, const Rewrap::Structure &layered_struc, STACKING_DIRECTION stacking_direction);

    /// Generate all distinct skewed versions of superstructure 
    std::vector<Rewrap::Structure> distinct_skewed_strucs();

    /// Generate all possible skewed versions of superstructure, even if symmetrically equivalent
    std::vector<Rewrap::Structure> all_skewed_strucs();

private:
    Rewrap::Structure m_prim_struc;
    Rewrap::Structure m_super_struc;
    STACKING_DIRECTION m_stacking_direction;
    CASM::PrimGrid m_grid;

    /// Add candudate_struc to current_strucs if it is symmetrically distinct from each structure in current_strucs
    void _add_if_distinct(std::vector<Rewrap::Structure> &current_strucs, Rewrap::Structure &candidate_struc);

    /// Generate all skewed version of superstructure, or only symmetrically distinct ones
    std::vector<Rewrap::Structure> _skewed_strucs(const bool distinct_only); 

    /// Generate superstructure skewed by given unit cell
    Rewrap::Structure _skew_super_struc(const CASM::UnitCell &unit_cell);

    /// Check if given unit cell lies on layer surface of superstructure
    bool _on_layer_surface(const CASM::UnitCell &unit_cell); 

};

}

#endif
