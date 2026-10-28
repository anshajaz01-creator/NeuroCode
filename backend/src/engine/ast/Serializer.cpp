#include "engine/ast/Serializer.hpp"

namespace nc::ast {

nlohmann::json toJson(const Node& n) {
    nlohmann::json j;
    j["type"] = n.type;
    j["spelling"] = n.spelling;
    j["line"] = n.line;
    if (n.dtype)      j["dtype"] = *n.dtype;
    if (n.tokens)     j["tokens"] = *n.tokens;
    if (n.op)         j["op"] = *n.op;
    if (n.has_else)   j["has_else"] = *n.has_else;
    if (n.base_text)  j["base_text"] = *n.base_text;
    if (n.index_text) j["index_text"] = *n.index_text;
    j["children"] = nlohmann::json::array();
    for (const auto& c : n.children) j["children"].push_back(toJson(c));
    return j;
}

std::string toJsonString(const Node& n) { return toJson(n).dump(); }

} // namespace nc::ast
