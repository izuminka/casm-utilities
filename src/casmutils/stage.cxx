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
    
LayerSkewer::LayerSkewer(Rewrap::Structure prim_struc, Rewrap::Structure super_struc, const int prim_c_vec_index, const int super_c_vec_index): prim_struc(prim_struc), super_struc(super_struc), prim_c_vec_index(prim_c_vec_index), super_c_vec_index(super_c_vec_index)
    {
        skewed_strucs.push_back(super_struc); // not sure the superstructure should be added initially        
    }

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

void LayerSkewer::generate_skewed_strucs(const bool distinct_only)
    {
        // TODO
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
        // TODO
        // get vector of scores from struc_score using candidate_struc as prim

        // check their weights
        
        // add if below threshold
        if (false) {
            skewed_strucs.push_back(candidate_struc);
        }

        return;
    }


}
