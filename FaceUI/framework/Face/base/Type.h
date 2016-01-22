
#ifndef _FACE_TYPE_H_
#define _FACE_TYPE_H_

#if defined _WIN64 || __x86_64 || __LP64__
#define FACE_64
#endif

typedef signed __int8			fint8_t;
typedef unsigned __int8			fuint8_t;
typedef signed __int16			fint16_t;
typedef unsigned __int16		fuint16_t;
typedef signed __int32			fint32_t;
typedef unsigned __int32		fuint32_t;
typedef signed __int64			fint64_t;
typedef unsigned __int64		fuint64_t;

#ifdef FACE_64
typedef fint64_t				fint;
typedef fint64_t				fsint;
typedef fuint64_t				fuint;
#else
typedef fint32_t				fint;
typedef fint32_t				fsint;
typedef fuint32_t				fuint;
#endif

#ifdef FACE_64
#define INCRC(x)	(_InterlockedIncrement64(x))
#define DECRC(x)	(_InterlockedDecrement64(x))
#else
#define INCRC(x)	(_InterlockedIncrement((volatile long*)(x)))
#define DECRC(x)	(_InterlockedDecrement((volatile long*)(x)))
#endif

#ifdef FACE_64
#define ITOA_S		_i64toa_s
#define ITOW_S		_i64tow_s
#define I64TOA_S	_i64toa_s
#define I64TOW_S	_i64tow_s
#define UITOA_S		_ui64toa_s
#define UITOW_S		_ui64tow_s
#define UI64TOA_S	_ui64toa_s
#define UI64TOW_S	_ui64tow_s
#else
#define ITOA_S		_itoa_s
#define ITOW_S		_itow_s
#define I64TOA_S	_i64toa_s
#define I64TOW_S	_i64tow_s
#define UITOA_S		_ui64toa_s
#define UITOW_S		_ui64tow_s
#define UI64TOA_S	_ui64toa_s
#define UI64TOW_S	_ui64tow_s
#endif

#define UI_WNDSTYLE_CONTAINER  (0)
#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER  (0)
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)

#endif