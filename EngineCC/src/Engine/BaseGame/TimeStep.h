#ifndef TIMESTEP_H
#define TIMESTEP_H
#define DLLEXPORT __declspec(dllexport)


namespace Graficos1
{
	class DLLEXPORT TimeStep
	{
	private:
		float deltaTime;
	public:
		TimeStep(float time = 0.0f) : deltaTime(time)
		{
		}
		operator float() const { return deltaTime; }
		float GetSeconds() const { return deltaTime; }
	};
}

#endif // TIMESTEP_H
