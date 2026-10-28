#pragma once
// Shared API error codes. Body shape: {"error":{"code":"...","message":"..."}}
// Keep these in sync with the error codes section of docs/api-spec.md.

namespace nc {

enum class ErrorCode {
    InvalidJson,
    ValidationFailed,
    Unauthorized,
    NotFound,
    Conflict,
    PayloadTooLarge,
    NotImplemented,
    TooManyRequests,
    Busy,
    Internal,
};

struct ErrorInfo {
    int http;
    const char* code;
};

inline ErrorInfo describe(ErrorCode c) {
    switch (c) {
        case ErrorCode::InvalidJson:       return {400, "invalid_json"};
        case ErrorCode::ValidationFailed:  return {400, "validation_failed"};
        case ErrorCode::Unauthorized:      return {401, "unauthorized"};
        case ErrorCode::NotFound:          return {404, "not_found"};
        case ErrorCode::Conflict:          return {409, "conflict"};
        case ErrorCode::PayloadTooLarge:   return {413, "payload_too_large"};
        case ErrorCode::NotImplemented:    return {501, "not_implemented"};
        case ErrorCode::TooManyRequests:   return {429, "too_many_requests"};
        case ErrorCode::Busy:              return {503, "busy"};
        case ErrorCode::Internal:          return {500, "internal_error"};
    }
    return {500, "internal_error"};
}

}  // namespace nc
