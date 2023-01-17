#include"DxLib.h"
#include "flying_Attack.h"

//�e�X�g�p color
int colors[3] = { 0x00ffff,0x00ff00,0xff00ff };

//�T�C�Y�@
struct Attack_Size
{
	int w;    //��
	int h;    //����
};

Attack_Size at_size[3] =
{
	{100,25},   //��
	{70,70},    //�S
	{44,44},    //�|�[�V����
};

//at_size[static_cast<int>(myType)].x

//�R���X�g���N�^
Flying_Attack::Flying_Attack(int type, int x, int y, int speed)
	:my_Type(type), Flying_object(x, y, at_size[type].w, at_size[type].h, speed)     //���N���X�̃R���X�g���N�^�Ăяo��
{
	//�R���X�g���N�^�Œl��n���Ȃ��ƃf�t�H���g�����ŉ�ʉE�[�����ł��܂�

	//�摜�ǂݍ���    ���E�S���E�Ł@�ő傫�����Ⴄ�̂ŋ����Ă�������
	switch (my_Type)
	{
	case Attack_Type::SPEAR:

		image = LoadGraph("images/spear.png");
		break;

	case Attack_Type::IRON:

		image = LoadGraph("images/iron2.png");
		break;

	case Attack_Type::POISON:

		image = LoadGraph("images/poison.png");
		break;

	default:
		break;
	}
}

//�f�X�g���N�^
Flying_Attack::~Flying_Attack()
{

}

//�X�V
void Flying_Attack::Update()
{
	//�E���獶��
	x -= speed;
}

//�`��
void Flying_Attack::Draw()
{
	//�摜�ϐ��ɉ����Ȃ��ꍇ�́@���@��`��
	if (image != 0)
	{
		//�摜�ŕ`��(���S���W)
		DrawRotaGraph(x, y, 1, 0, image, TRUE);
	}
	else
	{
		// �� ��`��   ���F���@�@�S�F�΁@�ŁF��
		DrawBox(x, y, x + w, y + h, colors[static_cast<int>(my_Type)], TRUE);
	}

	//�e�X�g
	DrawFormatString(0, 0, 0xffffff, "�C����");
}

// �U���ɂ��_���[�W�擾�i player��HP(�ϋv�l) �j
int Flying_Attack::GetAttackDamage(int hp)
{
	switch (my_Type)
	{
	case Attack_Type::SPEAR:

		return 10;     //10�_���[�W
		break;

	case Attack_Type::IRON:

		return static_cast<int>(hp * 0.5);  //50%�̊����_���[�W
		break;

	case Attack_Type::POISON:

		return 50;     //50�_���[�W
		break;

	default:
		break;
	}

	return 0;
}