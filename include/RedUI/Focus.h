#pragma once
#include <cstdint>

namespace RedUI
{
	enum class	Focus : uint16_t
	{
		None = 0,
		Cursor = 1 << 0,
		Interaction = 1 << 1,
		DisableInput = 1 << 2,
		All = 0xFFFF
	};

	constexpr Focus		operator|(Focus lhs, Focus rhs)
		{ return (static_cast<Focus>(static_cast<uint16_t>(lhs) | static_cast<uint16_t>(rhs))); }

	constexpr Focus		operator&(Focus lhs, Focus rhs)
		{ return (static_cast<Focus>(static_cast<uint16_t>(lhs) & static_cast<uint16_t>(rhs))); }

	constexpr Focus&	operator|=(Focus &lhs, const Focus rhs)
		{ return (lhs = lhs | rhs); }

	constexpr Focus&	operator&=(Focus &lhs, const Focus rhs)
		{ return (lhs = lhs & rhs); }

	class	FocusHandle
	{
		Focus	Flags;
		bool	Valid;

		void	RegisterFlags() const;
		void	UnregisterFlags() const;
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
	// Returns a FocusHandle object that unfocuses when .Release() is called or when it goes out of scope.
	FocusHandle	AcquireUIFocus(Focus flags = Focus::All);
}
