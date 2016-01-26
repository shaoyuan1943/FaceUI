#pragma once
#ifndef _MESSAGEMANAGER_H_
#define _MESSAGEMANAGER_H_

namespace Face
{
	class FACE_API MessageMgr : public Singleton<MessageMgr>
	{
	public:
		MessageMgr();
		virtual ~MessageMgr();

		virtual void Init();
		virtual void Destory();
	};
}
#endif