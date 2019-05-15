#include "casmutils/stage.hpp"
#include <casm/crystallography/Structure.hh>
#include <casm/clex/ScelEnum.hh>
#include <casm/crystallography/SupercellEnumerator.hh>
#include "casmutils/exceptions.hpp"
#include "casmutils/structure.hpp"
#include "casmutils/lattice.hpp"
#include <casm/crystallography/Niggli.hh>

namespace Simplicity
{
    
LayerSkewer::LayerSkewer(Rewrap::Structure prim_struc, Rewrap::Structure super_struc, const int prim_stacking_vec_index, const int super_stacking_vec_index): prim_struc(prim_struc), super_struc(super_struc), prim_stacking_vec_index(prim_stacking_vec_index), super_stacking_vec_index(super_stacking_vec_index)
    {
        skewed_strucs.push_back(super_struc);        
    }

void LayerSkewer::skew_super_struc(const int a_multiple, const int b_multiple)
    {
        return;
    }

void LayerSkewer::generate_skewed_strucs(const bool distinct_only)
    {
        return;
    }
    
}
