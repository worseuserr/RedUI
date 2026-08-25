#pragma once
#include <cstdint>

namespace RedUI
{
	class Focus
	{
		using			Type = uint16_t;
		friend class	Runtime;
		friend class	FocusHandle;

		// Reference count indexed by the order in the enum.
		static unsigned int		Refs[3];
		// Active state of each type.
		static Focus			State;
		Type					Value = 0;

		static void		Tick();

	public:
		enum	Value : uint16_t
		{
			None = 0,
			Cursor = 1 << 0,
			Interaction = 1 << 1,
			DisableInput = 1 << 2,
			All = 0xFFFF
		};

		Focus() = default;
		Focus(const uint16_t value) : Value(value) {}
		static bool	IsEnabled(Focus flag);

		Focus	operator|(const Focus rhs) const
			{ return (this->Value | rhs.Value); }

		Focus	operator&(const Focus rhs) const
			{ return (this->Value & rhs.Value); }

		Focus&	operator|=(const Focus rhs)
			{ return (*this = *this | rhs); }

		Focus&	operator&=(const Focus rhs)
			{ return (*this = *this & rhs); }

		bool	operator==(const Focus rhs) const
			{ return (this->Value == rhs.Value); }

		bool	operator!=(const Focus rhs) const
			{ return (this->Value != rhs.Value); }
	};

	class	FocusHandle
	{
		Focus	Flags;
		bool	Valid;

		void	RegisterFlags() const;
		void	UnregisterFlags() const;
		void	UpdateSingleState(int change, int index, Focus flag) const;
		void	UpdateFocusState(int change) const;

	public:
		FocusHandle(Focus flags, bool isValid);
		~FocusHandle();
		void		Release();
		explicit	operator bool() const;

		// Non-copyable.
		FocusHandle(const FocusHandle&) = delete;
		FocusHandle&	operator=(const FocusHandle&) = delete;
		// Movable.
		FocusHandle(FocusHandle&& other) noexcept;
		FocusHandle&	operator=(FocusHandle&& other) noexcept;
	};

	// Get focus in the game window. You can use this function to enable the mouse cursor, enable UI interaction, and/or disable ingame mouse inputs.
	// Returns a move-only FocusHandle object that unfocuses when .Release() is called or when it goes out of scope.
	//
	// It is recommended to also set the mouse position with RedUI::Input::SetMousePosition() when gaining focus.
	FocusHandle	AcquireUIFocus(Focus flags = Focus::All);
}
