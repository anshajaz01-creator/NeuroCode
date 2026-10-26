#include "IEngine.hpp"
#include "EngineStub.hpp"

namespace nc {

// Week 2: return the real Engine here. Callers do not change.
std::unique_ptr<IEngine> makeEngine(IPredictor& predictor) {
    return std::make_unique<EngineStub>(predictor);
}

} // namespace nc