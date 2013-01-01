﻿// Ŭnicode please
#include "stdafx.h"
#include "phy_component.h"
#include "sora/unit.h"
#include "game_object.h"

#if SR_USE_PCH == 0
#include "Box2D/Box2D.h"
#endif

using namespace std;
using namespace sora;

USING_NS_CC;

SinglePhyComponent *PhyComponent::SinglePhy(GameObject *obj, b2Body *body) {
    return new SinglePhyComponent(obj, body);
}

////////////////////////////////////////
SinglePhyComponent::SinglePhyComponent(GameObject *obj, b2Body *body)
: PhyComponent(obj),
body_(body) {
    body->SetUserData(reinterpret_cast<void*>(obj));
}

SinglePhyComponent::~SinglePhyComponent() {
    if(body_ != NULL) {
        b2World *world = body_->GetWorld();
        world->DestroyBody(body_);
        body_ = NULL;
    }
}

void SinglePhyComponent::Update(float dt) {
}

void SinglePhyComponent::InitMsgHandler() {
    RegisterMsgFunc(this, &SinglePhyComponent::OnMoveMessage);
    RegisterMsgFunc(this, &SinglePhyComponent::OnRequestPhyBodyInfoMessage);
    RegisterMsgFunc(this, &SinglePhyComponent::OnSetAngleMessage);
    RegisterMsgFunc(this, &SinglePhyComponent::OnSetPhyBodyInfoMessage);
}

void SinglePhyComponent::OnMoveMessage(MoveMessage *msg) {
    //msg에 들어오는 값은 px임.    
    b2Vec2 vec2 = body_->GetPosition();
    vec2.x += Unit::ToMeterFromUnit(msg->vec.x);
    vec2.y += Unit::ToMeterFromUnit(msg->vec.y);

    //경계 체크
    CCSize win_size = CCDirector::sharedDirector()->getWinSize();
    if(vec2.x > Unit::ToMeterFromUnit(win_size.width) || vec2.x < 0 
        || vec2.y > Unit::ToMeterFromUnit(win_size.height) || vec2.y < 0) {
        OutOfBoundMessage out_msg = OutOfBoundMessage::Create(body_->GetPosition(), vec2);
        obj()->OnMessage(&out_msg);
        //처리는 알아서 하게 해야지
        //return;
    }

    body_->SetTransform(vec2, body_->GetAngle());
    //body_->SetAwake(true);
}

void SinglePhyComponent::OnSetAngleMessage( SetAngleMessage *msg ) {
    body_->SetTransform(body_->GetPosition(), msg->angle);
}

void SinglePhyComponent::OnRequestPhyBodyInfoMessage(RequestPhyBodyInfoMessage *msg) {
    msg->phy_body_info->angle_rad = body_->GetAngle();

    b2Vec2 body_pos = body_->GetPosition();
    msg->phy_body_info->x = body_pos.x;
    msg->phy_body_info->y = body_pos.y;
    
    msg->is_ret = true;
}


void SinglePhyComponent::OnSetPhyBodyInfoMessage(SetPhyBodyInfoMessage *msg) {
    body_->SetTransform(b2Vec2(msg->info->x, msg->info->y), msg->info->angle_rad);
}


void SinglePhyComponent::set_main_body(b2Body *body) {
    //remove prev
    if(body_ != NULL) {
        b2World *world = body_->GetWorld();
        world->DestroyBody(body_);
        body_ = NULL;
    }

    body_ = body;
    body_->SetUserData(obj());
}
