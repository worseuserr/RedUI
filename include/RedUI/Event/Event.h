#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace RedUI::Event
{
	template	<typename TSender, typename TArgs>
	struct		Listener
	{
		unsigned long										ID;
		std::function<void(TSender *sender, TArgs args)>	Function;
	};

	template	<typename TSender, typename TArgs>
	class		Connection
	{
	public:
		unsigned long							ID;
		std::vector<Listener<TSender, TArgs>>	*Listeners;

		Connection(const unsigned long &id, std::vector<Listener<TSender, TArgs>> *listeners)
		{
			ID = id;
			Listeners = listeners;
		}

		void	Disconnect()
		{
			if (Listeners == nullptr)
				return ;
			std::erase_if(*Listeners,
				[this](Listener<TSender, TArgs> listener){ return (this->ID == listener.ID); });
		}
	};

	template	<typename TSender, typename TArgs>
	class		Event
	{
	protected:
		std::vector<Listener<TSender, TArgs>>	Listeners;

	public:
		Event() = default;
		void	Invoke(TSender *sender, const TArgs &args)
		{
			for (auto listener : Listeners)
			{
				listener.Function(sender, args);
			}
		}

		std::unique_ptr<Connection<TSender, TArgs>>	operator+=(std::function<void(TSender *sender, TArgs &args)> func)
		{
			static unsigned long	id = 0;

			Listeners.push_back(Listener<TSender, TArgs>{ .ID = id, .Function = func });
			id++;
			return (std::make_unique<Connection<TSender, TArgs>>(id, &Listeners));
		}
	};
}
