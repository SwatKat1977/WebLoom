//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_HTTPSTATUS_H_
#define CORE_HTTPSTATUS_H_
#include <string>

namespace webloom::core {

enum class HttpStatus {
    // 1xx Informational
    Continue           = 100,
    SwitchingProtocols = 101,
    Processing         = 102,

    // 2xx Success
    OK              = 200,
    Created         = 201,
    Accepted        = 202,
    NoContent       = 204,
    ResetContent    = 205,
    PartialContent  = 206,
    MultiStatus     = 207,
    AlreadyReported = 208,
    IMUsed          = 226,

    // 3xx Redirection
    MultipleChoices   = 300,
    MovedPermanently  = 301,
    Found             = 302,
    SeeOther          = 303,
    NotModified       = 304,
    UseProxy          = 305,
    TemporaryRedirect = 307,
    PermanentRedirect = 308,

    // 4xx Client Errors
    BadRequest                  = 400,
    Unauthorized                = 401,
    Payment_Required            = 402,
    Forbidden                   = 403,
    NotFound                    = 404,
    MethodNotAllowed            = 405,
    NotAcceptable               = 406,
    ProxyAuthenticationRequired = 407,
    RequestTimeout              = 408,
    Conflict                    = 409,
    Gone                        = 410,
    LengthRequired              = 411,
    PreconditionFailed          = 412,
    PayloadTooLarge             = 413,
    URITooLong                  = 414,
    UnsupportedMediaType        = 415,
    RangeNotSatisfiable         = 416,
    ExpectationFailed           = 417,
    IAmATeapot                  = 418,
    MisdirectedRequest          = 421,
    UnprocessableEntity         = 422,
    Locked                      = 423,
    FailedDependency            = 424,
    TooEarly                    = 425,
    Upgrade_Required            = 426,
    Precondition_Required       = 428,
    TooManyRequests             = 429,
    RequestHeaderFieldsTooLarge = 431,
    UnavailableForLegalReasons  = 451,

    // 5xx Server Errors
    InternalServerError           = 500,
    NotImplemented                = 501,
    BadGateway                    = 502,
    ServiceUnavailable            = 503,
    GatewayTimeout                = 504,
    HTTPVersionNotSupported       = 505,
    VariantAlsoNegotiates         = 506,
    InsufficientStorage           = 507,
    LoopDetected                  = 508,
    NotExtended                   = 510,
    NetworkAuthenticationRequired = 511
};

std::string HttpStatusString(HttpStatus status);

}   // namespace webloom::core

#endif  // CORE_HTTPSTATUS_H_
