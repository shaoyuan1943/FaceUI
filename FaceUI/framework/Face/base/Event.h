
#ifndef _FACE_EVENT_H_
#define _FACE_EVENT_H_

#pragma once

namespace Face
{
	template<typename T>
	class Event
	{
	};
 
	class EventHandler : public Object
	{
	public:
		virtual bool IsAttached() = 0;
	};

	template<typename ...TArgs>
	class Event<void(TArgs...)> : public Object, private NotCopyable
	{
	protected:
		class EventHandlerImpl : public EventHandler
		{
		public:
			bool attached;
			Func<void(TArgs...)> function;

			EventHandlerImpl(const Func<void(TArgs...)>& _function)
				:attached(true)
				, function(_function)
			{
			}
 
			bool IsAttached()override
			{
				return attached;
			}
		};
		
		std::list<Face::Ptr<EventHandlerImpl>> handlers;
	public:
		Ptr<EventHandler> Add(const Func<void(TArgs...)>& function)
		{
			Ptr<EventHandlerImpl> handler = new EventHandlerImpl(function);
			handlers.push_back(handler);
			return handler;
		}
	
		Ptr<EventHandler> Add(void(*function)(TArgs...))
		{
			return Add(Func<void(TArgs...)>(function));
		}
 
		template<typename C>
		Ptr<EventHandler> Add(C* sender, void(C::*function)(TArgs...))
		{
			return Add(Func<void(TArgs...)>(sender, function));
		}
		
		bool Remove(Ptr<EventHandler> handler)
		{
			Ptr<EventHandlerImpl> impl = handler.Cast<EventHandlerImpl>();
			if (!impl) 
				return false;
			
			auto iter = std::find(handlers.begin(), handlers.end(), impl);
			if (iter != handlers.end())
			{
				impl->attached = false;
				handlers.remove((*iter));
			}
			
			return true;
		}
 
		void operator()(TArgs ...args)const
		{
			for (auto iter = handlers.begin(); iter != handlers.end(); iter++)
			{
				(*iter)->function(ForwardValue<TArgs>(args)...);
			}
		}
	};
}

#endif
