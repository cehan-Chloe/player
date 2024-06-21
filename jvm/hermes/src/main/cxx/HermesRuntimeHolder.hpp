#pragma once

#include <iostream>
#include <hermes/hermes.h>

#define LOG(level) std::cout

namespace intuit::playerui {

static void hermesFatalHandler(const std::string& reason) {
    LOG(ERROR) << "Hermes Fatal: " << reason << "\n";
    // TODO: Reconnect to Android logger
    // __android_log_assert(nullptr, "Hermes", "%s", reason.c_str());
}

struct HermesRuntimeException : std::runtime_error {
    explicit HermesRuntimeException(const char* msg) : std::runtime_error(msg) {}
};

// TODO: The Holder nomenclature is typically used to hold a reference to Java objects
// Executor - TODO: It's possible we want to extend jsi::Runtime and delegate through a runtime instance
class HermesRuntimeHolder {
public:
    HermesRuntimeHolder();
    explicit HermesRuntimeHolder(hermes::vm::RuntimeConfig &config);

    facebook::jsi::Value execute(const std::string& script, const std::string& sourceURL = "unknown.js") const;

    void release() {
        if (runtime_) {
            std::cout << "Releasing" << std::endl;
            runtime_.reset();
        }
    }

    // NOTE: We would have to do this if we don't support a release API - we could, and maybe should, just delete *this*
    void assertNotReleased() const {
        if (!runtime_) {
            throw HermesRuntimeException("Runtime released!");
        }
    };

    operator facebook::jsi::Runtime&() const { return get_runtime(); }

    facebook::jsi::Runtime& get_runtime() const {
        assertNotReleased();
        return *runtime_;
    }

    hermes::vm::RuntimeConfig& get_config() const noexcept {
        return *config_;
    }

private:
    HermesRuntimeHolder(
        hermes::vm::RuntimeConfig &config,
        std::unique_ptr<facebook::hermes::HermesRuntime> runtime
    ) : config_(std::make_unique<hermes::vm::RuntimeConfig>(config)), runtime_(std::move(runtime)) {
        std::cout << "Primary constructor\nConfig: " << &get_config() << "\nRuntime: " << get_runtime().description() << std::endl;

        facebook::hermes::HermesRuntime::setFatalHandler(hermesFatalHandler);
    }

    std::unique_ptr<hermes::vm::RuntimeConfig> config_;
    std::unique_ptr<facebook::hermes::HermesRuntime> runtime_;
};

}
