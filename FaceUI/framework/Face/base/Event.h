
#ifndef _FACE_EVENT_H_
#define _FACE_EVENT_H_

#pragma once

namespace Face
{
	template<typename T>
	class FaceEvent
	{
	};
 
	class FaceEventHandler : public FaceObject
	{
	public:
		virtual bool IsAttached() = 0;
	};

	template<typename ...TArgs>
	class FaceEvent<void(TArgs...)> : public FaceObject, private FaceNotCopyable
	{
	protected:
		class EventHandlerImpl : public FaceEventHandler
		{
		public:
			bool attached;
			FaceFunc<void(TArgs...)> function;

			EventHandlerImpl(const FaceFunc<void(TArgs...)>& _function)
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
		Ptr<FaceEventHandler> Add(const FaceFunc<void(TArgs...)>& function)
		{
			Ptr<EventHandlerImpl> handler = new EventHandlerImpl(function);
			handlers.push_back(handler);
			return handler;
		}
	
		Ptr<FaceEventHandler> Add(void(*function)(TArgs...))
		{
			return Add(FaceFunc<void(TArgs...)>(function));
		}
 
		template<typename C>
		Ptr<FaceEventHandler> Add(C* sender, void(C::*function)(TArgs...))
		{
			return Add(FaceFunc<void(TArgs...)>(sender, function));
		}
		
		bool Remove(Ptr<FaceEventHandler> handler)
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
