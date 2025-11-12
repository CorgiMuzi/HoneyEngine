#pragma once

enum class EEngineStatus {
    Running,    // The engine should continue running
    Quit,       // A normal quit request was received
    Error       // A critical error occurred
};
