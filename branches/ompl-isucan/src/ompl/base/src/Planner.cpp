/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2008, Willow Garage, Inc.
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Ioan Sucan */

#include "ompl/base/Planner.h"
#include "ompl/util/Exception.h"

ompl::base::Planner::Planner(const SpaceInformationPtr &si) : si_(si), type_(PLAN_UNKNOWN), setup_(false)
{
    if (!si_)
	throw Exception("Invalid space information instance");
}

ompl::base::PlannerType ompl::base::Planner::getType(void) const
{
    return type_;
}

const ompl::base::ProblemDefinitionPtr& ompl::base::Planner::getProblemDefinition(void) const
{
    return pdef_;
}

void ompl::base::Planner::setProblemDefinition(const ProblemDefinitionPtr &pdef)
{
    clear();
    pdef_ = pdef;
}

void ompl::base::Planner::setup(void)
{
    if (!si_->isSetup())
    {
	msg_.inform("Space information setup was not yet called. Calling now");
	si_->setup();
    }
    
    if (setup_)
	msg_.warn("Planner setup called multiple times");
    else
	setup_ = true;
}

bool ompl::base::Planner::isSetup(void) const
{
    return setup_;
}