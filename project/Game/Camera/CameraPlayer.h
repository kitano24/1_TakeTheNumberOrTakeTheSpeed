#pragma once
class CameraPlayer : public Camera
{
public:
    //! コンストラクタ
    CameraPlayer();

    //! デストラクタ
    virtual ~CameraPlayer() = default;

    void Initialize();
    void Move(class Player* player);
    void ImGui();

    //! 更新
    virtual void Update() override;

    //! 描画
    virtual void Draw() override;

    //-------------------------------------------------------------
    //!	@name	ゲッター
    //-------------------------------------------------------------

    //@{
    VECTOR getPos();
    VECTOR getRot() { return rot; }
    //@}

private:
   
    float rotSpeed;    //!< 回転のスピード
    float adjustmentY; //!< Y座標の調整
    bool isImGui;      //!< imguiの起動フラグ
    VECTOR rot;        //!< カメラの回転

#define DISTANCE_ADJUSTMENT 35 //<! 距離の調整
};
