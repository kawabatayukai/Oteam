#pragma once
#include "flying_object.h"


//   �h��          �E���獶�ɔ��ł����i���j

//�h��̎��
enum class Armor_Type
{
	Type1,
	Type2,
	Type3,
};

//Test


class Flying_Armor : public Flying_object
{
public:
	//�R���X�g���N�^
	Flying_Armor(Armor_Type type,int durability = 10, int x = 1200, int y = 360, int speed = 1);

	//�f�X�g���N�^
	~Flying_Armor();

	void Update() override;    //�X�V
	void Draw() override;      //�`��

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetW() const { return w; }
	int GetH() const { return h; }

	int GetHP() const { return durability; }
	
private:
	int image = 0;    //�摜�p�ϐ�

	int durability;   //�ϋv�l

	Armor_Type myType;//�����̖h��^�C�v
};
