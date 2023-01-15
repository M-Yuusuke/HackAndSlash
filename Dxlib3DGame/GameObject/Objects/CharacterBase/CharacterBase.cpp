#include "../GameObject/Objects/CharacterBase/CharacterBase.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
namespace Calculation
{
    CharacterBase::CharacterBase(ObjectTag tag):
        GameObjectBase(tag),
        dir({0,0,0}),
        aimDir({0,0,0}),
        velocity({0,0,0}),
        animControl(nullptr),
        animTypeID(0),
        rotateNow(false)
    {
    }

    CharacterBase::CharacterBase(ObjectTag tag, VECTOR pos) :
        GameObjectBase(tag,pos),
        dir({ 0,0,0 }),
        aimDir({ 0,0,0 }),
        velocity({ 0,0,0 }),
        animControl(nullptr),
        animTypeID(0),
        rotateNow(false)
    {
    }

    /// <summary>
    /// 回転処理
    /// </summary>
    void CharacterBase::Rotate()
    {
        if (rotateNow)
        {
            //回転が目標角度に十分近ければ回転モード終了
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                rotateNow = false;
            }
            else
            {
                //回転させる
                VECTOR interPolateDir;
                interPolateDir = RotateForAimVecYAxis(dir, aimDir, RotateVelocity);

                //回転が目標角度を超えていないか
                VECTOR cross1, cross2;
                cross1 = VCross(dir, aimDir);
                cross2 = VCross(interPolateDir, aimDir);

                //目標角度を超えたら終了
                if (cross1.y * cross2.y < 0)
                {
                    interPolateDir = aimDir;
                    rotateNow = false;
                }
                //目標ベクトルに10度だけ近づけた角度
                dir = interPolateDir;
            }
        }
        //向きに合わせてモデルを回転
        //mixamoのモデルはX軸が反対向きに出るのでまずベクトルを180度回転させる
        MATRIX RotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
        dir.y = 0;
        VECTOR NegativeVec = VTransform(dir, RotYMat);

        //モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, NegativeVec, { 0,1.0f,0 }, 0);
    }

    void CharacterBase::OnCollisionStage(const GameObjectBase* other)
    {
        int ColModel = other->GetCollisionModel();

        //ステージと自分の境界球との当たり判定
        MV1_COLL_RESULT_POLY_DIM colInfo;
        if (collisionFunction.CollisionPair(collisionSphere, ColModel, colInfo))
        {
            //当たっている場合は押し戻し量を計算
            VECTOR pushBackVec = collisionFunction.CalcSpherePushBackVecFormMesh(collisionSphere, colInfo);
            pos += pushBackVec;

            //コリジョン情報の解放
            MV1CollResultPolyDimTerminate(colInfo);
            CollisionUpdate();
        }

        ////ステージと足元線分当たり判定
        //MV1_COLL_RESULT_POLY colInfoLine;
        //if (collisionFunction.CollisionPair(collisionLine, ColModel, colInfoLine))
        //{
        //    //当たっている場合は足元を衝突点に合わせる
        //    pos = colInfoLine.HitPosition;
        //    CollisionUpdate();
        //}
    }
    
}