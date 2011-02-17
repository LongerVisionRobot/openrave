// Copyright (C) 2006-2008 Carnegie Mellon University (rdiankov@cs.cmu.edu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "plugindefs.h"
#include "ikbase.h"
#include <rave/plugin.h>

#include "ikfastproblem.h"

namespace barrettwam {
#include "ik_barrettwam.h"
}
namespace pa10 {
#include "ik_pa10.h"
}
namespace puma {
#include "ik_puma.h"
}
namespace pr2_head {
#include "ik_pr2_head.h"
}
namespace pr2_head_torso {
#include "ik_pr2_head_torso.h"
}
namespace pr2_leftarm {
#include "ik_pr2_leftarm.h"
}
namespace pr2_leftarm_torso {
#include "ik_pr2_leftarm_torso.h"
}
namespace pr2_rightarm {
#include "ik_pr2_rightarm.h"
}
namespace pr2_rightarm_torso {
#include "ik_pr2_rightarm_torso.h"
}
namespace schunk_lwa3 {
#include "ik_schunk_lwa3.h"
}
namespace katana5d {
#include "ik_katana5d.h"
}

// register for typeof (MSVC only)
#ifdef RAVE_REGISTER_BOOST
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(barrettwam::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pa10::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(puma::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pr2_head::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pr2_head_torso::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pr2_leftarm::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pr2_leftarm_torso::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pr2_rightarm::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(pr2_rightarm_torso::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(schunk_lwa3::IKSolution)
BOOST_TYPEOF_REGISTER_TYPE(katana5d::IKSolution)
#endif

#include "ikfastproblem.h"

InterfaceBasePtr CreateInterfaceValidated(InterfaceType type, const std::string& interfacename, std::istream& sinput, EnvironmentBasePtr penv)
{
    dReal freeinc = 0.04f;
    switch(type) {
    case PT_InverseKinematicsSolver: {
        if( interfacename == "ikfast" ) {
            string ikfastname;
            sinput >> ikfastname;
            if( !!sinput ) {
                sinput >> freeinc;
                // look at all the ikfast problem solvers
                IkSolverBasePtr psolver = IKFastProblem::CreateIkSolver(ikfastname, freeinc, penv);
                if( !!psolver ) {
                    return psolver;
                }
            }
        }
        else {
            sinput >> freeinc;
            if( interfacename == "wam7ikfast" ) {
                vector<int> vfree(barrettwam::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = barrettwam::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<barrettwam::IKReal,barrettwam::IKSolution>(barrettwam::ik,vfree,freeinc,barrettwam::getNumJoints(),(IkParameterization::Type)barrettwam::getIKType(), boost::shared_ptr<void>(), barrettwam::getKinematicsHash(), penv));
            }
            else if( interfacename == "pa10ikfast" ) {
                vector<int> vfree(pa10::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pa10::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pa10::IKReal,pa10::IKSolution>(pa10::ik,vfree,freeinc,pa10::getNumJoints(),(IkParameterization::Type)pa10::getIKType(), boost::shared_ptr<void>(), pa10::getKinematicsHash(), penv));
            }
            else if( interfacename == "pumaikfast" ) {
                vector<int> vfree(puma::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = puma::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<puma::IKReal,puma::IKSolution>(puma::ik,vfree,freeinc,puma::getNumJoints(),(IkParameterization::Type)puma::getIKType(), boost::shared_ptr<void>(), puma::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_pr2_head" ) {
                vector<int> vfree(pr2_head::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pr2_head::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pr2_head::IKReal,pr2_head::IKSolution>(pr2_head::ik,vfree,freeinc,pr2_head::getNumJoints(),(IkParameterization::Type)pr2_head::getIKType(), boost::shared_ptr<void>(), pr2_head::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_pr2_head_torso" ) {
                vector<int> vfree(pr2_head_torso::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pr2_head_torso::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pr2_head_torso::IKReal,pr2_head_torso::IKSolution>(pr2_head_torso::ik,vfree,freeinc,pr2_head_torso::getNumJoints(),(IkParameterization::Type)pr2_head_torso::getIKType(), boost::shared_ptr<void>(), pr2_head_torso::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_pr2_rightarm" ) {
                vector<int> vfree(pr2_rightarm::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pr2_rightarm::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pr2_rightarm::IKReal,pr2_rightarm::IKSolution>(pr2_rightarm::ik,vfree,freeinc,pr2_rightarm::getNumJoints(),(IkParameterization::Type)pr2_rightarm::getIKType(), boost::shared_ptr<void>(), pr2_rightarm::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_pr2_rightarm_torso" ) {
                vector<int> vfree(pr2_rightarm_torso::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pr2_rightarm_torso::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pr2_rightarm_torso::IKReal,pr2_rightarm_torso::IKSolution>(pr2_rightarm_torso::ik,vfree,freeinc,pr2_rightarm_torso::getNumJoints(),(IkParameterization::Type)pr2_rightarm_torso::getIKType(), boost::shared_ptr<void>(), pr2_rightarm_torso::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_pr2_leftarm" ) {
                vector<int> vfree(pr2_leftarm::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pr2_leftarm::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pr2_leftarm::IKReal,pr2_leftarm::IKSolution>(pr2_leftarm::ik,vfree,freeinc,pr2_leftarm::getNumJoints(),(IkParameterization::Type)pr2_leftarm::getIKType(), boost::shared_ptr<void>(), pr2_leftarm::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_pr2_leftarm_torso" ) {
                vector<int> vfree(pr2_leftarm_torso::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = pr2_leftarm_torso::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<pr2_leftarm_torso::IKReal,pr2_leftarm_torso::IKSolution>(pr2_leftarm_torso::ik,vfree,freeinc,pr2_leftarm_torso::getNumJoints(),(IkParameterization::Type)pr2_leftarm_torso::getIKType(), boost::shared_ptr<void>(), pr2_leftarm_torso::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_schunk_lwa3" ) {
                vector<int> vfree(schunk_lwa3::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = schunk_lwa3::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<schunk_lwa3::IKReal,schunk_lwa3::IKSolution>(schunk_lwa3::ik,vfree,freeinc,schunk_lwa3::getNumJoints(),(IkParameterization::Type)schunk_lwa3::getIKType(), boost::shared_ptr<void>(), schunk_lwa3::getKinematicsHash(), penv));
            }
            else if( interfacename == "ikfast_katana5d" ) {
                vector<int> vfree(katana5d::getNumFreeParameters());
                for(size_t i = 0; i < vfree.size(); ++i) {
                    vfree[i] = katana5d::getFreeParameters()[i];
                }
                return InterfaceBasePtr(new IkFastSolver<katana5d::IKReal,katana5d::IKSolution>(katana5d::ik,vfree,freeinc,katana5d::getNumJoints(),(IkParameterization::Type)katana5d::getIKType(), boost::shared_ptr<void>(), katana5d::getKinematicsHash(), penv));
            }
        }
        break;
    }        
    case PT_ProblemInstance:
        if( interfacename == "ikfast")
            return InterfaceBasePtr(new IKFastProblem(penv));
        break;
    default:
        break;
    }

    return InterfaceBasePtr();
}

void GetPluginAttributesValidated(PLUGININFO& info)
{
    info.interfacenames[PT_ProblemInstance].push_back("ikfast");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("wam7ikfast");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("pa10ikfast");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("pumaikfast");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_pr2_head");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_pr2_head_torso");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_pr2_rightarm");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_pr2_rightarm_torso");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_pr2_leftarm");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_pr2_leftarm_torso");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_schunk_lwa3");
    info.interfacenames[PT_InverseKinematicsSolver].push_back("ikfast_katana5d");
}

OPENRAVE_PLUGIN_API void DestroyPlugin()
{
    delete IKFastProblem::GetLibraries();
    IKFastProblem::GetLibraries() = NULL;
}
