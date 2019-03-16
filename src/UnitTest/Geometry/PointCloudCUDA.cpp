// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "TestUtility/UnitTest.h"
#include "Open3D/Geometry/PointCloud.h"
#include "Open3D/Geometry/Image.h"
#include "Open3D/Geometry/RGBDImage.h"
#include "Open3D/Camera/PinholeCameraIntrinsic.h"

#include <algorithm>

using namespace Eigen;
using namespace open3d;
using namespace std;
using namespace unit_test;

#ifdef OPEN3D_USE_CUDA

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(PointCloudCUDA, ComputePointCloudMeanAndCovarianceCUDA) {
    int size = 1 << 24;
    geometry::PointCloud pc;

    Vector3d vmin(-1.0, -1.0, -1.0);
    Vector3d vmax(+1.0, +1.0, +1.0);

    pc.points_.resize(size);
    Rand(pc.points_, vmin, vmax, 0);

    pc.use_cuda = false;
    auto outputCPU = geometry::ComputePointCloudMeanAndCovariance(pc);

    pc.use_cuda = true;
    auto outputGPU = geometry::ComputePointCloudMeanAndCovariance(pc);

    Vector3d meanCPU = get<0>(outputCPU);
    Matrix3d covarianceCPU = get<1>(outputCPU);

    Vector3d meanGPU = get<0>(outputGPU);
    Matrix3d covarianceGPU = get<1>(outputGPU);

    ExpectEQ(meanCPU, meanGPU);
    ExpectEQ(covarianceCPU, covarianceGPU);
}

#endif