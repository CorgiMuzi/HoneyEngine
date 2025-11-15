#pragma once

namespace HoneyEngine
{
	class ManagerBase {
	public:
		ManagerBase() = default;
		virtual ~ManagerBase() = default;

		ManagerBase(const ManagerBase&) = delete;
		ManagerBase& operator=(const ManagerBase&) = delete;

		// Common interfaces for manager classes
		virtual bool init() { return true; }
		virtual void update() {}
		virtual void term() {}
	};
}