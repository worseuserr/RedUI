#pragma once

#include <math.h>
#include <numbers>

#include "Time/Time.h"

namespace RedUI
{
	enum class	Easing
	{
		Linear,
		Constant, // Instant set at the end of the animation, can be used to delay a change.
		SineIn,
		SineOut,
		SineInOut,
		QuadIn,
		QuadOut,
		QuadInOut,
		BackIn,
		BackOut,
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
		virtual T	Ease(float t)
		{
			static constexpr float	BackOvershoot = 1.5f;
			static constexpr float	OvershootAdd = BackOvershoot + 1.0f;
			static constexpr float	OvershootMult = BackOvershoot * 1.525f;

			// Big credit to https://easings.net/ for all these.
			switch (EasingMethod)
			{
				case Easing::Linear:
					// t = t;
					break ;
				case Easing::Constant:
					return (t == 1.0f ? EndValue : StartValue);
				case Easing::SineIn:
					t = (1.0f - cos((t * std::numbers::pi) / 2.0f));
					break ;
				case Easing::SineOut:
					t = (sin((t * std::numbers::pi) / 2.0f));
					break ;
				case Easing::SineInOut:
					t = (-(cos(std::numbers::pi * t) - 1.0f) / 2.0f);
					break ;
				case Easing::QuadIn:
					t = (t * t);
					break ;
				case Easing::QuadOut:
					t = (1 - (1 - t) * (1 - t));
					break ;
				case Easing::QuadInOut:
					t = (t < 0.5f ? 2.0f * t * t : 1.0f - pow(-2.0f * t + 2.0f, 2.0f) / 2.0f);
					break ;
				case Easing::BackIn:
					t = (BackOvershoot * t * t * t - OvershootAdd * t * t);
					break ;
				case Easing::BackOut:
					t = (1.0f + OvershootAdd * pow(t - 1.0f, 3.0f) + BackOvershoot * pow(t - 1.0f, 2.0f));
					break ;
				case Easing::BackInOut:
					t = (t < 0.5f
					  ? (pow(2.0f * t, 2.0f) * ((OvershootMult + 1.0f) * 2.0f * t - OvershootMult)) / 2.0f
					  : (pow(2.0f * t - 2.0f, 2.0f) * ((OvershootMult + 1.0f) * (t * 2.0f - 2.0f) + OvershootMult) + 2.0f) / 2.0f);
					break ;
				default:
					return (EndValue);
			}
			return (StartValue + (EndValue - StartValue) * t);
		}
	};

	using AnimationOwner = std::unique_ptr<IAnimation>;
}
