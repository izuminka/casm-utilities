#ifndef UTILS_STAGE_HH
#define UTILS_STAGE_HH

#include "casmutils/definitions.hpp"
#include "casmutils/structure.hpp"

namespace Simplicity
{

class LayerSkewer
{
public:
    
    LayerSkewer() = delete;

    /// Construct by providing primitive structure and superstructure (assumed to be layered)
    /// Optionally can specify the index of the out-of-layer lattice vector for each structure, called c (default is third)
    LayerSkewer(Rewrap::Structure prim_struc, Rewrap::Structure super_struc, const int prim_c_vec_index=2, const int super_c_vec_index=2);

    /// Skew the superstructure by multiples of the in-layer lattice vectors of the prim, called a and b
    /// a and b are defined in a cyclic manner based on the index of c (i.e. 0->a,1->b,2->c or 0->c,1->a,2->b or 0->b,1->c,2->a)
    Rewrap::Structure skew_super_struc(const int a_multiple, const int b_multiple);

    /// Generate all skewed versions of superstructure
    /// Only distinct ones by default
    void generate_skewed_strucs(const bool distinct_only=true);

    /// Return a vector of your skewed structures
    std::vector<Rewrap::Structure> get_skewed_strucs();

private:
    Rewrap::Structure prim_struc;
    Rewrap::Structure super_struc;
    const int prim_c_vec_index;
    const int super_c_vec_index;
    std::vector<Rewrap::Structure> skewed_strucs;

    /// Add a new struc to skewed_strucs only if it is distinct
    void add_if_distinct(Rewrap::Structure candidate_struc);

};

}

#endif
