#pragma once
#include "Object/UIObject.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Object/Create.h"

namespace RedUI
{
	// RAII handle for created UI objects.
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
			other.OrgPtr = nullptr;
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

	// Adds the UIComponent::Create function to a component type.
	// This is required when defining a custom component, in order to make component instantiation easy.
	//
	// See the custom component creation guide (or the source code of an existing component) for usage.
	#define UI_CREATE(Type, TypeName) \
		/* Instantiates a UI component internally and returns a RAII handle to it. */ \
		template <typename... Args> \
		requires (std::constructible_from<Type, Args...>) \
		static RedUI::UIHandle<Type>	Create(RedUI::Object::UIObject *parent, Args&&... args) \
		{ \
			return (RedUI::UIHandle(RedUI::Object::Create<Type>(parent, std::forward<Args>(args)...))); \
		} \
		inline std::string Name() const override { return (std::string(TypeName)); }
		//
}
