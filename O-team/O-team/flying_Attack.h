#pragma once
#include "flying_object.h"


//   �U��          �E���獶�ɔ��ł����i���j

//�U���̎��
enum Attack_Type
{
	SPEAR,      //���@�|
	IRON,       //�S�@��
	POISON,     //�Ł@�|�[�V����
};


class Flying_Attack : public Flying_object
{
public:
	//�R���X�g���N�^
	Flying_Attack(int type, int x = 1200, int y = 360, int speed = 0);

	//�f�X�g���N�^
	~Flying_Attack();

	void Update() override;    //�X�V
	void Draw() override;      //�`��

	// �U���ɂ��_���[�W�擾�i player��HP(�ϋv�l) �j
	int GetAttackDamage(const int hp);

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetW() const { return w; }
	int GetH() const { return h; }
	int GetType() const { return my_Type; }

private:
	int image = 0;          //�摜�p�ϐ�

	int my_Type;    //�������ǂ̃^�C�v�̍U����

	int damage = 0;
};

