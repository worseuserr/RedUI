#pragma once
#include "Object/UIObject.h"
#include "Object/Destroy.h"
#include "Object/Create.h"

namespace RedUI
{
	template <typename T>
	class	UIHandle
	{
		T		*OrgPtr;

	public:
		UIHandle()
		{
			OrgPtr = nullptr;
		}

		UIHandle(T *object)
		{
			OrgPtr = object;
		}

		~UIHandle()
		{
			Release();
		}

		void	Release()
		{
			if (OrgPtr != nullptr)
				OrgPtr->Destroy();
			OrgPtr = nullptr;
		}

		bool	Exists()
		{
			return (OrgPtr != nullptr);
		}

		T		*Get()
		{
			return (OrgPtr);
		}

		// Non-copyable.
		UIHandle(const UIHandle&) = delete;
		UIHandle&	operator=(const UIHandle&) = delete;

		// Movable.
		UIHandle(UIHandle&& other) noexcept
		{
			OrgPtr = other.OrgPtr;
		}

		UIHandle&	operator=(UIHandle&& other) noexcept
		{
			if (this != &other)
			{
				Release();
				OrgPtr = other.OrgPtr;
				other.OrgPtr = nullptr;
			}
			return (*this);
		}

		operator T*() const
		{
			return (OrgPtr);
		}

		T&			operator*()
		{
			return (*OrgPtr);
		}

		const T&	operator*() const
		{
			return (*OrgPtr);
		}

		T*			operator->()
		{
			return (OrgPtr);
		}

		const T*	operator->() const
		{
			return (OrgPtr);
		}
	};

	class	UIComponent : public Object::UIObject
	{
	public:
		using UIObject::UIObject;
	};

	// template <typename T>
	// class	UIComponentFactory
	// {
	// public:
	// 	template <typename... Args>
	// 	requires (std::constructible_from<T, Args...>)
	// 	static UIHandle<T>	Create(Object::UIObject *parent, Args&&... args)
	// 	{
	// 		return (UIHandle(Object::Create<T>(parent, std::forward<Args>(args)...)));
	// 	}
	// };

	#define UI_CREATE(Type) \
		template <typename... Args> \
		requires (std::constructible_from<Type, Args...>) \
		static UIHandle<Type>	Create(Object::UIObject *parent, Args&&... args) \
		{ \
			return (UIHandle(Object::Create<Type>(parent, std::forward<Args>(args)...))); \
		}
}
