#pragma once
// Stand-in for T1's real training pipeline, so the Training page and the live loss chart
// can be built against real endpoints today. Simulates epochs with a falling loss.
// Writes no files, so nothing shows up in GET /models.

#include "common/Types.hpp"

namespace nc {

TrainFn makeStubTrainFn();

}  // namespace nc
