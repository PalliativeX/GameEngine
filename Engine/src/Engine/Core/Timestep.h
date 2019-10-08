#pragma once

namespace Engine
{

	class Timestep
	{
	public:
		Timestep(float Time = 0.f) : time(Time) {}

		operator float() const { return time; }

		float getSeconds() const { return time; }
		float getMilliseconds() const { return time * 1000; }

	private:
		float time;
	};
}