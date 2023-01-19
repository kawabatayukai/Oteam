#include"DxLib.h"
#include "flying_Armor.h"


//�R���X�g���N�^
Flying_Armor::Flying_Armor(Armor_Type type, int durability, int x, int y, int speed)
	:durability(durability), Flying_object(x, y, 45, 45, speed)      //���N���X�̃R���X�g���N�^�Ăяo��
{
	//�R���X�g���N�^�Œl��n���Ȃ��ƃf�t�H���g�����ŉ�ʉE�[�����ł��܂�

	//�摜�ǂݍ���
	image = LoadGraph("images/GameMain/huku.png");
}

//�f�X�g���N�^
Flying_Armor::~Flying_Armor()
{

}

//�X�V
void Flying_Armor::Update()
{
	//�E���獶��
	x -= speed;
}

//�`��
void Flying_Armor::Draw()
{
	//�摜�ϐ��ɉ����Ȃ��ꍇ�́@���@��`��
	if (image != 0)
	{
		//�摜�ŕ`��(���S���W)
		DrawRotaGraph(x, y, 1, 0, image, TRUE);
	}
	else
	{
		// �� ��`��
		DrawBox(x, y, x + w, y + h, 0xffffff, TRUE);
	}
}
