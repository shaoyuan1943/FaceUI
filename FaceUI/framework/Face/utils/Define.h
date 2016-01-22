
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
#define CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw Face::FaceError(DESCRIPTION);}while(0)
#elif defined NDEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION)
#endif

#define CHECK_FAIL(DESCRIPTION) do{throw Face::FaceError(DESCRIPTION);}while(0)

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
						public: virtual void Get##funName(varType var){ varName = var; }

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

#endif