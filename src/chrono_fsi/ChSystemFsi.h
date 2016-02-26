// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Author: Arman Pazouki
// =============================================================================
//
// Class for performing handling fsi system.
// =============================================================================

#ifndef CH_SYSTEMFSI_H_
#define CH_SYSTEMFSI_H_

#include "chrono_fsi/ChFsiDataManager.cuh"
#include "chrono_fsi/ChFluidDynamics.cuh"
#include "chrono_fsi/ChFsiInterface.h"
#include "chrono_fsi/ChBce.cuh"

#include "chrono_parallel/physics/ChSystemParallel.h"
#include "chrono_vehicle/wheeled_vehicle/utils/ChWheeledVehicleAssembly.h"


namespace chrono {
namespace fsi {

class CH_FSI_API ChSystemFsi : public ChFsiGeneral{

public:
	ChSystemFsi();
	~ChSystemFsi();

	void DoStepDynamics_FSI();
	void DoStepDynamics_ChronoRK2(); 
	void CopyDeviceDataToHalfStep();
	void SetHaveVehicle(bool other_haveVehicle);

private:
	int DoStepChronoSystem(Real dT,
		double mTime);

	ChFsiDataManager* fsiData;
	// map fsi to chrono bodies
	std::vector<ChSharedPtr<ChBody> > fsiBodeisPtr;
	ChFluidDynamics* fluidDynamics;
	ChFsiInterface* fsiInterface;
	ChBce* bceWorker;

	chrono::ChSystemParallelDVI * mphysicalSystem;
	chrono::vehicle::ChWheeledVehicleAssembly* mVehicle;

	SimParams* paramsH;
	NumberOfObjects* numObjectsH;

	double mTime;
	bool haveVehicle;
};
} // end namespace fsi
} // end namespace chrono
#endif