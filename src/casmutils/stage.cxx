#include "casmutils/stage.hpp"
#include <casm/crystallography/Structure.hh>
//#include <casm/clex/ScelEnum.hh>
//#include <casm/crystallography/SupercellEnumerator.hh>
#include "casmutils/exceptions.hpp"
#include "casmutils/structure.hpp"
#include "casmutils/lattice.hpp"
//#include <casm/crystallography/Niggli.hh>

namespace Simplicity
{
    
LayerSkewer::LayerSkewer(Rewrap::Structure prim_struc, Rewrap::Structure super_struc, const int prim_stacking_vec_index, const int super_stacking_vec_index): prim_struc(prim_struc), super_struc(super_struc), prim_stacking_vec_index(prim_stacking_vec_index), super_stacking_vec_index(super_stacking_vec_index)
    {
        skewed_strucs.push_back(super_struc);        
    }

Rewrap::Structure LayerSkewer::skew_super_struc(const int a_multiple, const int b_multiple)
    {
        return super_struc;
    }

void LayerSkewer::generate_skewed_strucs(const bool distinct_only)
    {
        // loop over prim grid and generate new structures using skew_super_struc
        
        Rewrap::Structure new_struc = skew_super_struc(0,0);

        if (distinct_only) {
            add_if_distinct(new_struc);
        } else {
            skewed_strucs.push_back(new_struc);
        }
 
        return;
    }

std::vector<Rewrap::Structure> LayerSkewer::get_skewed_strucs()
    {
        return skewed_strucs;
    }

void LayerSkewer::add_if_distinct(Rewrap::Structure candidate_struc)
    {
        // get vector of scores from struc_score using candidate_struc as prim

        // check their weights
        
        // add if below threshold
        if (false) {
            skewed_strucs.push_back(candidate_struc);
        }

        return;
    }


}
