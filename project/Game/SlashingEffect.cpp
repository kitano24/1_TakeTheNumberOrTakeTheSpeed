//---------------------------------------------------------------------------
//!	@file	SlashingEffect.cpp
//!	@brief	�a���G�t�F�N�g
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
SlashingEffect::SlashingEffect()
{
	//! �G�t�F�N�g�̃T�C�Y���w��
	effectSize = 3.0f;

	//! �G�t�F�N�g���\�[�X��ǂݍ���
	effectResourceHandle = LoadEffekseerEffect("data/effect/slashing.efk", effectSize);

	//! �Đ����̃G�t�F�N�g�̃n���h��������������
	playingEffectHandle = -1;
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void SlashingEffect::Update()
{
	//! DX���C�u�����̃J������Effekseer�̃J�����𓯊�����
	Effekseer_Sync3DSetting();

	// �G�t�F�N�g���Đ�����B
	UpdateEffekseer3D();
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void SlashingEffect::Draw()
{
	//! Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��
	DrawEffekseer3D();
}

//---------------------------------------------------------------------------
//! @param�ipos�j �|���ꂽ�G�̈ʒu��ݒ�
//---------------------------------------------------------------------------
void SlashingEffect::setEffectPos(const VECTOR& pos)
{
	float adjustPosY = 5.0f; //! Y���W�̒��� 

	//! �G�t�F�N�g���Đ�
	playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

	//! �G�t�F�N�g�̈ʒu��|���ꂽ�G�̈ʒu�ɂ���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y + adjustPosY, pos.z);
}
