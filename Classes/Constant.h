//
//  Constant.h
//  BugsKiller
//
//  Created by 张长浩 on 2018/5/5.
//

#ifndef Constant_h
#define Constant_h

//非指针类型成员变量
#define PropertyBuilderByName(type, name, access_permission)\
access_permission:\
type m##name;\
public:\
inline void setM##name(type name) {\
m##name = name;\
}\
inline type getM##name() {\
return m##name;\
}\

//指针型成员变量
#define PointerPropertyBuilderByName(type, name, access_permission)\
access_permission:\
type* m##name;\
public:\
inline void setM##name(type* name){\
m##name = name;\
}\
inline type* getM##name(){\
return m##name;\
}\

#endif /* Constant_h */
