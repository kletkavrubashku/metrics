#pragma once

#include <functional>
#include <memory>
#include <string>

#include "metrics/tagged.hpp"

namespace metrics {
namespace detail {

class processor_t;

}  // namespace detail
}  // namespace metrics

namespace metrics {

template<typename T>
class gauge;

template<typename T>
class counter;

class meter_t;

template<class Accumulate>
class timer;

namespace accumulator {
namespace sliding {

class window_t;

}  // namespace sliding
}  // namespace accumulator

using detail::processor_t;

class registry_t {
    std::unique_ptr<processor_t> processor;

public:
    registry_t();
    ~registry_t();

    /// Given a `metric` gauge, registers it under the given name.
    template<typename M>
    void
    listen(std::string name, typename M::function_type metric);

    /// Given a `metric` gauge, registers it under the given name with the given tags.
    template<typename M>
    void
    listen(std::string name, tagged_t::container_type tags, typename M::function_type metric);

    /// \where `T` must be either `std::uint64_t`, `std::int64_t` or `long double`.
    template<typename T>
    metrics::gauge<T>
    gauge(std::string name, tagged_t::container_type tags = tagged_t::container_type()) const;

    /// \where `T` must be either `std::uint64_t` or `std::int64_t`.
    template<typename T>
    counter<T>
    counter(const std::string& name) const;

    /// \where `T` must be either `std::uint64_t` or `std::int64_t`.
    template<typename T>
    metrics::counter<T>
    counter(std::string name, tagged_t::container_type tags) const;

    meter_t
    meter(const std::string& name) const;

    // TODO: Change default accumulator to `exponentially_decaying_t`.
    template<class Accumulate = accumulator::sliding::window_t>
    timer<Accumulate>
    timer(const std::string& name) const;
};

}  // namespace metrics
