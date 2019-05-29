#include "casmutils/stage.hpp"

int main()
{

    // JUST for testing
    Rewrap::fs::path test_prim_path("POSCAR_prim");
    Rewrap::fs::path test_super_path("POSCAR_super");
    Simplicity::LayerSkewer::STACKING_DIRECTION stack_direction = Simplicity::LayerSkewer::STACKING_DIRECTION::B;

    Rewrap::Structure test_prim(test_prim_path);
    Rewrap::Structure test_super(test_super_path);
   
    Simplicity::LayerSkewer test_skewer(test_prim, test_super, stack_direction);
    
    // all structures
    std::cout << "generating all skewed structures...";
    std::vector<Rewrap::Structure> all = test_skewer.all_skewed_strucs();
    for (int i=0; i < all.size(); i++)
    {    
        Simplicity::write_poscar(all[i], "all/POSCAR_"+std::to_string(i));
    }
    std::cout << "done." << std::endl;

    // distinct only
    std::cout << "generating distinct skewed structures...";
    std::vector<Rewrap::Structure> distinct = test_skewer.distinct_skewed_strucs();
    for (int i=0; i < distinct.size(); i++)
    {
        Simplicity::write_poscar(distinct[i], "distinct/POSCAR_"+std::to_string(i));
    }
    std::cout << "done." << std::endl;

    return 0;
}
