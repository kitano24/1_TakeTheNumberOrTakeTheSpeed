//---------------------------------------------------------------------------
//!	@file	SlashingEffect.cpp
//!	@brief	斬撃エフェクト
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
SlashingEffect::SlashingEffect()
{
	//! エフェクトのサイズを指定
	effectSize = 3.0f;

	//! エフェクトリソースを読み込む
	effectResourceHandle = LoadEffekseerEffect("data/effect/slashing.efk", effectSize);

	//! 再生中のエフェクトのハンドルを初期化する
	playingEffectHandle = -1;
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void SlashingEffect::Update()
{
	//! DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();

	// エフェクトを再生する。
	UpdateEffekseer3D();
}

//---------------------------------------------------------------------------
//! 描画処理
//---------------------------------------------------------------------------
void SlashingEffect::Draw()
{
	//! Effekseerにより再生中のエフェクトを描画する
	DrawEffekseer3D();
}

//---------------------------------------------------------------------------
//! @param（pos） 倒された敵の位置を設定
//---------------------------------------------------------------------------
void SlashingEffect::setEffectPos(const VECTOR& pos)
{
	float adjustPosY = 5.0f; //! Y座標の調整 

	//! エフェクトを再生
	playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

	//! エフェクトの位置を倒された敵の位置にする
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y + adjustPosY, pos.z);
}
