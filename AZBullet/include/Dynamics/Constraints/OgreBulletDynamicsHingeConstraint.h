/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This program is free software; you can redistribute it and/or modify it under
the terms of the GPL General Public License with runtime exception as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GPL General Public License with runtime exception for more details.

You should have received a copy of the GPL General Public License with runtime exception along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
-----------------------------------------------------------------------------
*/
#ifndef _OGREBULLETDYNAMICS_HingeConstraint_H
#define _OGREBULLETDYNAMICS_HingeConstraint_H

#include "OgreBulletDynamicsPreRequisites.h"

#include "OgreBulletDynamicsConstraint.h"


namespace OgreBulletDynamics
{
    // -------------------------------------------------------------------------
    // HingeConstraint  class
    class HingeConstraint : public TypedConstraint
    {
    public:
        HingeConstraint(RigidBody * rbA, 
                            RigidBody * rbB, 
                            const Ogre::Vector3& pivotInA,
                            const Ogre::Vector3& pivotInB, 
                            const Ogre::Vector3& axisInA, 
                            const Ogre::Vector3& axisInB);
        HingeConstraint(RigidBody * rbA, 
            const Ogre::Vector3& pivotInA, 
            const Ogre::Vector3&  axisInA);


        virtual ~HingeConstraint();

    };
}
#endif //_OGREBULLETDYNAMICS_HingeConstraint_H

