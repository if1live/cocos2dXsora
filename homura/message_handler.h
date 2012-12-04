﻿// Ŭnicode please
//reference
//http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
#pragma once

#include <map>
#include <memory>
#include <typeinfo>
#include "sora/shared_ptr_include.h"
#include "game_message.h"

struct GameMessage;

class HandlerFunctionBase {
public:
	virtual ~HandlerFunctionBase() {}
	void Exec(const GameMessage *msg) { Call(msg); }
private:
	virtual void Call(const GameMessage *msg) = 0;
};

template<typename T, typename MsgT>
class MemberFunctionHandler : public HandlerFunctionBase {
public:
	typedef void (T::*MemberFunc)(MsgT*);
	MemberFunctionHandler(T *instance, MemberFunc mem_fun)
		: instance_(instance), func_(mem_fun) { }
	void Call(const GameMessage *msg)
	{
		const MsgT *tmp = static_cast<const MsgT*>(msg);
		MsgT *tmp2 = const_cast<MsgT*>(tmp);
		(instance_->*func_)(tmp2);
	}
private:
	T *instance_;
	MemberFunc func_;
};

class TypeInfo_ {
public:
	explicit TypeInfo_(const std::type_info &info) : typeinfo_(info) {}
	bool operator<(const TypeInfo_ &o) const {
		return typeinfo_.before(o.typeinfo_) != 0;
	}
	bool operator==(const TypeInfo_ &o) const {
		return (typeinfo_ == o.typeinfo_);
	}
	bool operator!=(const TypeInfo_ &o) const {
		return (typeinfo_ != o.typeinfo_);
	}
private:
	const std::type_info &typeinfo_;
};

class MessageHandler {
public:
    MessageHandler() {}
	~MessageHandler() {
		auto it = handler_list_.begin();
		auto endit = handler_list_.end();
		for( ; it != endit ; ++it) {
			delete(it->second);
		}
		handler_list_.clear();
	}
	void HandleMsg(const GameMessage *msg) {
		Handlers::iterator it = handler_list_.find(TypeInfo_(typeid(*msg)));
		if(it != handler_list_.end()) {
			it->second->Exec(msg);
		}
	}

	template<typename T, class MsgT>
	void RegisterMessageFunc(T *obj, void (T::*mem_fun)(MsgT*)) {
        TypeInfo_ code(typeid(MsgT));
		handler_list_[code] = new MemberFunctionHandler<T, MsgT>(obj, mem_fun);
	}
private:
	typedef std::map<TypeInfo_, HandlerFunctionBase*> Handlers;
	Handlers handler_list_;
};