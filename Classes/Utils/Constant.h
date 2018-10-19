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
type _##name;\
public:\
inline void set##name(type name) {\
_##name = name;\
}\
inline type get##name() {\
return _##name;\
}\

//指针型成员变量
#define PointerPropertyBuilderByName(type, name, access_permission)\
access_permission:\
type* _##name;\
public:\
inline void set##name(type* name){\
_##name = name;\
}\
inline type* get##name(){\
return _##name;\
}\

#define WinSize Director::getInstance()->getVisibleSize()

#endif /* Constant_h */
