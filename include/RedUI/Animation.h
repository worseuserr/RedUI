#pragma once

#include "Time/Time.h"

namespace RedUI
{
	enum class	Easing
	{
		Linear,
		Constant, // Instant set at the end of the animation, can be used to delay a change.
		SineOut,
		SineIn,
		SineInOut,
		QuadOut,
		QuadIn,
		QuadInOut,
		BackOut,
		BackIn,
		BackInOut,
	};

	class	IAnimation
	{
	public:
		virtual			~IAnimation() = default;
		virtual bool	Update() = 0;
	};

	// Class to hold animation data and methods. T is the type of the member that is being animated.
	template <typename T>
	class	Animation : public IAnimation
	{
	protected:
		T					*Member;
		T					StartValue;
		T					EndValue;
		Easing				EasingMethod;
		Time::Milliseconds	CreationTime;
		Time::Milliseconds	Duration;

	public:
		Animation(T *member, const Time::Milliseconds duration, T startValue, T endValue, const Easing easing = Easing::Linear)
		{
			if (member == nullptr)
				return ;
			Member = member;
			StartValue = startValue;
			EndValue = endValue;
			CreationTime = Time::MsSinceEpoch();
			Duration = duration;
			EasingMethod = easing;
			*Member = startValue;
		}
		virtual T	Ease(const float t)
		{
			if (EasingMethod == Easing::Linear)
				return (StartValue + (EndValue - StartValue) * t);
			if (EasingMethod == Easing::Constant)
				return (t == 1.0f ? EndValue : StartValue);
			return (EndValue);
		}
		// Returns true if animation finished, otherwise false.
		bool		Update() override
		{
			float	progress;

			progress = static_cast<float>(Time::MsSinceEpoch() - CreationTime) / Duration;
			if (progress > 1.0f)
				progress = 1.0f;
			*Member = Ease(progress);
			return (progress == 1.0f);
		}
	};

	using AnimationOwner = std::unique_ptr<IAnimation>;
}
