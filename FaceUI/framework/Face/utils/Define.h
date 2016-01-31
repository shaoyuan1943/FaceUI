
#ifndef _FACE_DEFINE_H_
#define _FACE_DEFINE_H_

// defines

// dll & lib setting macros
#if defined(FACE_EXPORTS)
	#if defined(_MSC_VER)
		#define FACE_API __declspec(dllexport)
	#else
		#define FACE_API 
	#endif
#else
	#if defined(_MSC_VER)
		#define FACE_API __declspec(dllimport)
	#else
		#define FACE_API 
	#endif
#endif

// errors macros
#if defined _DEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw Face::Error(DESCRIPTION);}while(0)
#elif defined NDEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION)
#endif

#define CHECK_FAIL(DESCRIPTION) do{throw Face::Error(DESCRIPTION);}while(0)

// block macros
#define SAFE_DELETE_ARRAY(array)	do						\
									{						\
										if(!array)			\
										{					\
											delete[] array; \
											array = nullptr;\
										}					\
									}while(0)

#define SAFE_DELETE(ptr)	do						\
							{						\
								if (!ptr)			\
								{					\
									delete ptr;		\
									ptr = nullptr;	\
								}					\
							}while (0)


// class macros
#define SYNTHESIZE_PRO(varType, varName, funName)\
						protected: varType varName;\
						public: virtual varType Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PRI(varType, varName, funName)\
						private: varType varName;\
						public: virtual varType Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PRO_CONST(varType, varName, funName)\
						protected: varType varName;\
						public: virtual const varType Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(const varType var){ varName = var; }

#define SYNTHESIZE_PRI_CONST(varType, varName, funName)\
						private: varType varName;\
						public: virtual const varType Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(const varType var){ varName = var; }

#define SYNTHESIZE_PRO_REF(varType, varName, funName)\
						protected: varType varName;\
						public: virtual varType& Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_PRI_REF(varType, varName, funName)\
						private: varType varName;\
						public: virtual varType& Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_PRO_CONST_REF(varType, varName, funName)\
						protected: varType varName;\
						public: virtual const varType& Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(const varType& var){ varName = var; }

#define SYNTHESIZE_PRI_CONST_REF(varType, varName, funName)\
						private: varType varName;\
						public: virtual const varType& Get##funName(void) const { return varName; }\
						public: virtual void Set##funName(const varType& var){ varName = var; }

#define SYNTHESIZE_PRI_CONST_REF_GET(varType, varName, funName)\
						private: varType varName;\
						public: virtual const varType& Get##funName(void) const { return varName; }\

#define SYNTHESIZE_PRI_CONST_REF_SET(varType, varName, funName)\
						private: varType varName;\
						public: virtual const varType& Set##funName(void) const { return varName; }\

#define OBJECT_CREATE(T)	static T* Create(){ return new T;}

namespace Face
{
	class Control;

	typedef enum EVENT_TYPE
	{
		EVENT_UNKNOW = 0,
		// 按键事件
		EVENT_KEYDOWN,
		EVENT_KEYUP,
		EVENT_CHAR,
		EVENT_SYSKEY,
		//

		// 鼠标事件
		EVENT_MOUSEMOVE,
		EVENT_MOUSELEAVE,
		EVENT_MOUSEENTER,
		EVENT_MOUSEHOVER,

		EVENT_BUTTONDOWN,
		EVENT_BUTTONUP,

		EVENT_RBUTTONDOWN,
		EVENT_RBUTTONUP,

		EVENT_DBLCLICK,
		EVENT_DBRCLICK,

		EVENT_SCROLLWHEEL,
		//

		EVENT_KILLFOCUS,
		EVENT_SETFOCUS,
		EVENT_WINDOWSIZE,
		EVENT_SETCURSOR,
		EVENT_TIMER,
		EVENT_NOTIFY,
		EVENT_COMMAND,
	} EVENT;

	typedef enum NOTIFY_TYPE
	{
		NOTIFY_UNKNOW = 10000,
		// 鼠标左键单击和双击
		NOTIFY_LCLICK,
		NOTIFY_DBLCLICK,

		// 鼠标右键单击和双击
		NOTIFY_RCLICK,
		NOTIFY_DBRCLICK,

	} NOTIFY;

	typedef struct tagTEvent
	{
		EVENT type;
		Control* pSender;
		DWORD dwTimestamp;
		POINT ptMouse;
		TCHAR boardKey;
		WORD keyState;
		WPARAM wParam;
		LPARAM lParam;
	} TEvent;

	typedef struct tagTNotify
	{
		NOTIFY type;
		Control* pSender;
		DWORD dwTimestamp;
		POINT ptMouse;
		WPARAM wParam;
		LPARAM lParam;
	} TNotify;
}

#endif