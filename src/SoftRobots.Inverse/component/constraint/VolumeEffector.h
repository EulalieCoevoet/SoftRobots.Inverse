/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
*                       Plugin SoftRobots.Inverse                             *
*                                                                             *
* This plugin is distributed under the GNU AGPL v3 (Affero General            *
* Public License) license.                                                    *
*                                                                             *
* Authors: Christian Duriez, Eulalie Coevoet, Yinoussa Adagolodjo             *
*                                                                             *
* (c) 2023 INRIA                                                              *
*                                                                             *
* Contact information: https://project.inria.fr/softrobot/contact/            *
******************************************************************************/
#pragma once

#include <SoftRobots.Inverse/component/behavior/Effector.h>
#include <SoftRobots/component/constraint/model/SurfacePressureModel.h>


namespace softrobotsinverse::constraint
{

using softrobotsinverse::behavior::Effector;
using sofa::helper::ReadAccessor;
using sofa::core::VecCoordId;
using sofa::core::ConstraintParams;


/**
 * Description can be found at:
 * https://softrobotscomponents.readthedocs.io
*/
template< class DataTypes >
class VolumeEffector : public Effector<DataTypes> , public softrobots::constraint::SurfacePressureModel<DataTypes>
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(VolumeEffector,DataTypes), SOFA_TEMPLATE(Effector,DataTypes));

    typedef typename DataTypes::Coord Coord;
    typedef typename Coord::value_type Real;
    typedef typename sofa::core::behavior::MechanicalState<DataTypes> MechanicalState;


public:

    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_volumeGrowth;

    VolumeEffector(MechanicalState* object=nullptr);
    ~VolumeEffector() override;

    ////////////////////////// Inherited from BaseObject ////////////////////
    void init() override;
    /////////////////////////////////////////////////////////////////////////

    //////////////// Inherited from SoftRobotsConstraint ///////////////
    void getConstraintViolation(const ConstraintParams* cParams,
                                sofa::linearalgebra::BaseVector *resV,
                                const sofa::linearalgebra::BaseVector *Jdx) override;
    /////////////////////////////////////////////////////////////////////////

    ////////////////////////// Inherited attributes ////////////////////////////
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_constraintIndex ;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_cavityVolume ;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::m_state ;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_initialCavityVolume ;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::getCavityVolume;

    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_eqPressure;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_eqVolumeGrowth;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_minPressure;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_maxPressure;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_maxPressureVariation;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_minVolumeGrowth;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_maxVolumeGrowth;
    using softrobots::constraint::SurfacePressureModel<DataTypes>::d_maxVolumeGrowthVariation;

    using Effector<DataTypes>::getTarget;
    ////////////////////////////////////////////////////////////////////////////


    /////////////// Inherited from BaseSoftRobotsConstraint ////////////////
    virtual void storeResults(sofa::type::vector<double> &delta) override;
    ///////////////////////////////////////////////////////////////////////////

protected:

    sofa::Data<Real> d_desiredVolume;

};

#if !defined(SOFTROBOTS_INVERSE_VOLUMEEFFECTOR_CPP)
extern template class SOFA_SOFTROBOTS_INVERSE_API VolumeEffector<sofa::defaulttype::Vec3Types>;
#endif

} // namespace


