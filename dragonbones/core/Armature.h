﻿#ifndef __CORE_ARMATURE_H__
#define __CORE_ARMATURE_H__

#include "../DragonBones.h"
#include "../objects/ArmatureData.h"
#include "../animation/IAnimatable.h"
#include "../animation/Animation.h"
#include "../events/IEventDispatcher.h"
#include "Slot.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class Object;
class Bone;
class Slot;
class Animation;
class AnimationState;

class Armature : public IAnimatable
{
    friend class Object;
    friend class Bone;
    friend class Slot;
    
    friend class Animation;
    friend class AnimationState;
    
public:
    static IEventDispatcher *soundEventDispatcher;
    
private:
    static bool sortBone(const std::pair<int, Bone*> &a, const std::pair<int, Bone*> &b);
    static bool sortSlot(const Slot *a, const Slot *b);
    
public:
    String name;
    
    void *userData;
    
protected:
    bool _needUpdate;
    bool _slotsZOrderChanged;
    bool _delayDispose;
    bool _lockDispose;
    
    std::vector<Bone*> _boneList;
    std::vector<Slot*> _slotList;
    std::vector<EventData*> _eventDataList;
    
    ArmatureData *_armatureData;
    Animation *_animation;
    IEventDispatcher *_eventDispatcher;
    void *_display;
    
public:
    virtual const std::vector<Bone*>& getBones() const;
    virtual const std::vector<Slot*>& getSlots() const;
    
    virtual const ArmatureData* getArmatureData() const;
    virtual Animation* getAnimation() const;
    virtual void* getDisplay() const;
    virtual IEventDispatcher* getEventDispatcher() const;
    
public:
    Armature(ArmatureData *armatureData, Animation *animation, IEventDispatcher *eventDispatcher, void *display);
    virtual ~Armature();
    virtual void dispose();
    
public:
    virtual Bone* getBone(const String &boneName) const;
    virtual Bone* getBoneByDisplay(const void *display) const;
    virtual void addBone(Bone *bone);
    virtual void addBone(Bone *bone, const String &parentBoneName);
    virtual void removeBone(Bone *bone);
    virtual Bone* removeBone(const String &boneName);
    
    virtual Slot* getSlot(const String &slotName) const;
    virtual Slot* getSlotByDisplay(const void *display) const;
    virtual void addSlot(Slot *slot, const String &parentBoneName);
    virtual void removeSlot(Slot *slot);
    virtual Slot* removeSlot(const String &slotName);
    virtual void sortSlotsByZOrder();
    
    virtual void invalidUpdate();
    virtual void invalidUpdate(const String &boneName);
    
    virtual void advanceTime(float passedTime) override;
    
protected:
    virtual void addObject(Object *object);
    virtual void removeObject(Object *object);
    virtual void sortBones();
    
    virtual void arriveAtFrame(Frame *frame, AnimationState *animationState, bool isCross);
    
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(Armature);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // __CORE_ARMATURE_H__