#include "casmutils/stage.hpp"
#include <casm/crystallography/Structure.hh>
//#include <casm/clex/ScelEnum.hh>
//#include <casm/crystallography/SupercellEnumerator.hh>
#include "casmutils/exceptions.hpp"
#include "casmutils/structure.hpp"
#include "casmutils/lattice.hpp"
//#include <casm/crystallography/Niggli.hh>
#include <casm/crystallography/PrimGrid.hh>

namespace Simplicity
{
    
LayerSkewer::LayerSkewer(const Rewrap::Structure &prim_struc, const Rewrap::Structure &layered_struc, STACKING_DIRECTION stacking_direction): m_prim_struc(prim_struc), m_super_struc(layered_struc), m_stacking_direction(stacking_direction), m_grid(m_prim_struc.lattice(), m_super_struc.lattice())
    {
    }

/*
Rewrap::Structure LayerSkewer::skew_super_struc(const int a_multiple, const int b_multiple)
    {
        // Get lattices
        Eigen::Matrix3d prim_lat_mat = prim_struc.lattice().lat_column_mat();
        Eigen::Matrix3d super_lat_mat = super_struc.lattice().lat_column_mat(); 

        // Update c lattice parameter
        int prim_a_vec_index = (prim_c_vec_index - 2) % 3;
        int prim_b_vec_index = (prim_c_vec_index - 1) % 3;
        super_lat_mat.col(super_c_vec_index) = super_lat_mat.col(super_c_vec_index) + a_multiple*prim_lat_mat.col(prim_a_vec_index) + b_multiple*prim_lat_mat.col(prim_b_vec_index);

        // Create new structure with the skewed lattice 
        Rewrap::Structure new_struc = super_struc;
        CASM::Lattice new_lat(super_lat_mat);
        new_struc.set_lattice(new_lat, CASM::CART);

        return new_struc;
    }
*/

std::vector<Rewrap::Structure> LayerSkewer::all_skewed_strucs()
    {   
        return _skewed_strucs(false);
    }

std::vector<Rewrap::Structure> LayerSkewer::distinct_skewed_strucs()
    {   
        return _skewed_strucs(true);
    }


std::vector<Rewrap::Structure> LayerSkewer::_skewed_strucs(const bool distinct_only)
    {
        // TODO
        // loop over prim grid and generate new structures

        Rewrap::Structure new_struc = m_super_struc;
        std::vector<Rewrap::Structure> skewed_strucs;

        if (distinct_only) {
            _add_if_distinct(skewed_strucs, new_struc);
        } else {
            skewed_strucs.emplace_back(new_struc);
        }
             
        return skewed_strucs;
    }

void LayerSkewer::_add_if_distinct(std::vector<Rewrap::Structure> &current_strucs, Rewrap::Structure &candidate_struc)
    {
        // TODO
        // get vector of scores from struc_score using candidate_struc as prim

        // check their weights
        
        // add if below threshold
        if (false) {
            current_strucs.emplace_back(candidate_struc);
        }

        return;
    }

}
