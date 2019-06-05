#include "casmutils/stage.hpp"
#include "casmutils/exceptions.hpp"
#include "casmutils/lattice.hpp"
#include "casmutils/structure.hpp"
#include <casm/crystallography/PrimGrid.hh>
#include <casm/crystallography/Structure.hh>

namespace Simplicity
{

LayerSkewer::LayerSkewer(const Rewrap::Structure& prim_struc,
                         const Rewrap::Structure& layered_struc,
                         STACKING_DIRECTION stacking_direction)
    : m_prim_struc(prim_struc),
      m_super_struc(layered_struc),
      m_stacking_direction(stacking_direction),
      m_grid(m_prim_struc.lattice(), m_super_struc.lattice())
{
}

std::vector<Rewrap::Structure> LayerSkewer::all_skewed_strucs() { return _skewed_strucs(false); }

std::vector<Rewrap::Structure> LayerSkewer::distinct_skewed_strucs() { return _skewed_strucs(true); }

std::vector<Rewrap::Structure> LayerSkewer::_skewed_strucs(bool distinct_only)
{
    std::vector<Rewrap::Structure> skewed_strucs;

    // loop over unit cells in prim grid
    for (int i = 0; i < m_grid.size(); i++)
    {
        const CASM::UnitCell unit_cell = m_grid.unitcell(i);

        // check if on layer surface
        if (_on_layer_surface(unit_cell))
        {
            // skew it
            Rewrap::Structure new_struc = _skew_super_struc(unit_cell);
            if (distinct_only)
            {
                _add_if_distinct(skewed_strucs, new_struc);
            }
            else
            {
                skewed_strucs.emplace_back(new_struc);
            }
        }
    }

    return skewed_strucs;
}

void LayerSkewer::_add_if_distinct(std::vector<Rewrap::Structure>& current_strucs, Rewrap::Structure& candidate_struc)
{
    // get structure scores
    std::vector<std::pair<double, double>> score_vec = structure_score(candidate_struc, current_strucs);

    // check structure scores
    bool candidate_is_distinct = true;
    for (const auto& score : score_vec)
    {
        if (fmax(score.first, score.second) < CASM::TOL)
        {
            candidate_is_distinct = false;
            break;
        }
    }

    // add if distinct
    if (candidate_is_distinct)
    {
        current_strucs.emplace_back(candidate_struc);
    }

    return;
}

Rewrap::Structure LayerSkewer::_skew_super_struc(const CASM::UnitCell& unit_cell)
{
    // get lattices
    Eigen::Matrix3d prim_lat_mat = m_prim_struc.lattice().lat_column_mat();
    Eigen::Matrix3d super_lat_mat = m_super_struc.lattice().lat_column_mat();

    // get new lattice vector
    int stacking_direction_index = static_cast<int>(m_stacking_direction);
    Eigen::Vector3d new_lat_vec = prim_lat_mat * unit_cell.cast<double>();

    // create new structure with the skewed lattice
    CASM::Structure new_struc(m_super_struc);
    super_lat_mat.col(stacking_direction_index) = super_lat_mat.col(stacking_direction_index) + new_lat_vec;
    CASM::Lattice new_lat(super_lat_mat);
    new_struc.set_lattice(new_lat, CASM::CART);
    return Rewrap::Structure(new_struc);
}

bool LayerSkewer::_on_layer_surface(const CASM::UnitCell& unit_cell)
{
    // get lattice vector corresponding to unit cell
    int stacking_direction_index = static_cast<int>(m_stacking_direction);
    Eigen::Matrix3d prim_lat_mat = m_prim_struc.lattice().lat_column_mat();
    Eigen::Vector3d new_lat_vec = prim_lat_mat * unit_cell.cast<double>();

    // check if it has a component along stacking direction
    CASM::Coordinate d(new_lat_vec, m_super_struc.lattice(), CASM::CART);
    Eigen::Vector3d d_frac = d.frac();
    return (d_frac[stacking_direction_index] < CASM::TOL);
}

} // namespace Simplicity

