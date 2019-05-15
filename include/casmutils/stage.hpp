#ifndef UTILS_STAGE_HH
#define UTILS_STAGE_HH

#include "casmutils/definitions.hpp"
#include "casmutils/structure.hpp"

namespace Simplicity
{


    /**
     * TODO: info
     */

class LayerSkewer
{
public:
    //TODO: better name?
    enum class STACKING_DIRECTION {A,B,C};
    
    LayerSkewer() = delete;

    /// Construct by providing primitive structure and superstructure (assumed to be layered)
    /// Optionally can specify the index of the out-of-layer lattice vector for each structure, called c (default is third)
    LayerSkewer(const Rewrap::Structure &prim_struc, const Rewrap::Structure &layered_struc, STACKING_DIRECTION stack_vec);

    /// Generate all distinct skewed versions of superstructure
    //TODO: Think of making this std::set and coming up with clever comparator
    std::vector<Rewrap::Structure> distinct_skewed_strucs();

    /// Generate all possible skewed versions of superstructure, even if symmetrically equivalent
    std::vector<Rewrap::Structure> all_skewed_strucs();

private:
    Rewrap::Structure m_prim_struc;
    Rewrap::Structure m_super_struc;
    STACKING_DIRECTION m_stacking_direction;
    CASM::PrimGrid m_grid;


    /// Add a new struc to skewed_strucs only if it is distinct
    void _add_if_distinct(Rewrap::Structure candidate_struc);

    /// Skew the superstructure by multiples of the in-layer lattice vectors of the prim, called a and b
    /// a and b are defined in a cyclic manner based on the index of c (i.e. 0->a,1->b,2->c or 0->c,1->a,2->b or 0->b,1->c,2->a)
    //TODO: This has to be UCC (no rewrap available... if you're lazy just leave private)
    Rewrap::Structure _skew_super_struc(const int a_multiple, const int b_multiple);
};

}

#endif
