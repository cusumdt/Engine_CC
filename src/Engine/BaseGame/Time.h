#ifndef TIME_H
#define TIME_H
#define DLLEXPORT __declspec(dllexport)

namespace Engine
{
	class DLLEXPORT Time
	{
	private:
		float deltaTime;
	public:
		Time(float time = 0.0f) : deltaTime(time)
		{
		}

		operator float() const { return deltaTime; }
		float DeltaTime() const { return deltaTime; }
	};
}

#endif // TIME_H
