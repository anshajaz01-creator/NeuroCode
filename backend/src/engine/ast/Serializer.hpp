#pragma once
#include <string>

#include <nlohmann/json.hpp>

#include "engine/ast/Node.hpp"

namespace nc::ast {

// Same JSON that tools/extract_ast.py writes: optional fields are left out, not null.
nlohmann::json toJson(const Node& node);
std::string toJsonString(const Node& node);

} // namespace nc::ast
