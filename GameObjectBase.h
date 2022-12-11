#pragma once
#include "DxLib.h"
#include "ObjectTag.h"
#include "CollisionType.h"
#include "LineSegment.h"
#include "Capsule.h"
#include "Sphere.h"

namespace Calculation
{
    /**�Q�[���I�u�W�F�N�g�̊��N���X*/
    class GameObjectBase
    {
    public:
        //�R���X�g���N�^
        GameObjectBase(ObjectTag tag);
        GameObjectBase(ObjectTag tag, VECTOR pos);
        //�f�X�g���N�^
        virtual ~GameObjectBase();

        virtual void Initialize() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() {}

        const VECTOR& GetPos()const { return Pos; }
        void SetPos(const VECTOR vec) { Pos = vec; }

        bool IsVisible()const { return Visible; }
        void SetVisible(bool visible) { Visible = visible; }

        bool IsAlive() const { return Alive; }
        void SetAlive(bool alive) { Alive = alive; }

        ObjectTag GetTag()const { return Tag; }

        //�����蔻��֘A
        //���̃I�u�W�F�N�g�ƂԂ������Ƃ��̃��A�N�V����
        virtual void OnCollisionEnter(const GameObjectBase* other) {}
        //���̃I�u�W�F�N�g�Ƃ̓����蔻��
        virtual void Collsion(GameObjectBase* other) {}

        //���̃I�u�W�F�N�g�������Ă��铖���蔻��̎�ނ��擾
        CollisionType GetCollisionType() const { return collisionType; }
        //�����蔻��line��ԋp
        LineSegment GetCollisionLine() const { return collisionLine; }
        //�����蔻�苅��ԋp
        Sphere GetCollisionSphere() const { return collisionSphere; }
        //�����蔻��J�v�Z����ԋp
        Capsule GetCollisionCapsule() const { return collisionCapsule; }
        //�����蔻�胂�f����ԋp
        int GetCollisionModel() const { return CollisionModel; }

    protected:
        //�����蔻��ʒu�̍X�V
        void CollisionUpdate();
        //�����蔻��̕`��
        void DrawCollider();

        ObjectTag Tag;
        VECTOR Pos;
        int ModelHandle;
        bool Visible;
        bool Alive;

        //�����蔻��֘A
        CollisionType collisionType;
        LineSegment collisionLine;
        Sphere collisionSphere;
        Capsule collisionCapsule;
        int CollisionModel;
    };
}


